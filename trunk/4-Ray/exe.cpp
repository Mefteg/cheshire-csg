#include <math.h>   
#include <stdlib.h> 
#include <stdio.h>  

#include "ray.h"
#include "sphere.h"


#define X (512/2) // Width
#define Y (384/2) // Height
#define S 100     // Samples
#define D 5       // Recursion depth

//! \brief Easy coded random function
inline double Random() { return (rand()%10000)/9999.0;}

//!< Scene defined as an array of spheres (radius, position, emission, color, material) 
Sphere spheres[] = {
  Sphere(1e5, Vector( 1e5+1,40.8,81.6), Vector(0.0,0.0,0.0),Vector(.75,.25,.25),0),//Left red
  Sphere(1e5, Vector(-1e5+99,40.8,81.6),Vector(0.0,0.0,0.0),Vector(.25,.25,.75),0),//Right blue
  Sphere(1e5, Vector(50,40.8, 1e5),     Vector(0.0,0.0,0.0),Vector(.75,.75,.75),0),//Back 
  Sphere(1e5, Vector(50,40.8,-1e5+170), Vector(0.0,0.0,0.0),Vector(0.0,0.0,0.0),0),//Front 
  Sphere(1e5, Vector(50, 1e5, 81.6),    Vector(0.0,0.0,0.0),Vector(.75,.75,.75),0),//Botom white
  Sphere(1e5, Vector(50,-1e5+81.6,81.6),Vector(0.0,0.0,0.0),Vector(.75,.75,.75),0),//Top white
  Sphere(16.5,Vector(27,16.5,47),       Vector(0.0,0.0,0.0),Vector(1,1,1)*.999, 1),//Mirror 
  Sphere(16.5,Vector(73,16.5,78),       Vector(0.0,0.0,0.0),Vector(1,1,1)*.999, 2),//Glass 
  Sphere(600, Vector(50,681.6-.27,81.6),Vector(12,12,12),  Vector(0.0,0.0,0.0), 0) //Light 
}; 

/*!
\brief Clamp value to unity.
*/
inline double clamp(double x){ return x<0 ? 0 : x>1 ? 1 : x; } 

/*!
\brief Convert to int and apply a gamma power of 2.2.
*/
inline int toInt(double x){ return int(pow(clamp(x),1/2.2)*255+.5); } 

/*!
\brief Compute the intersection between the ray and the scene.
*/
inline bool IntersectScene(const Ray &r, double &t, int &id)
{ 
  bool k=false;
  for (int i=0;i<9;i++) 
  {
    double d;
    if(spheres[i].Intersect(r,d)) 
    { 
      if (k==false) { t=d; id=i;} 
      else { if (d<t) {t=d; id=i;} } 
      k=true;
    }
  }
  return k; 
} 
#define M_PI 3.141592654

/*!
\brief Compute the radiance of a given ray.
\param r The ray.
\brief depth Recursion depth.
*/
Vector radiance(const Ray &r, int depth)
{ 
  double t;                               // distance to IntersectSceneion 
  int id=0;                               // id of IntersectSceneed object 
  if (!IntersectScene(r, t, id)) return Vector(0.0,0.0,0.0); 

  const Sphere &obj = spheres[id];      

  Vector x=r(t);
  Vector n=Normalized(x-obj.p);
  Vector nl=n*(r.Direction())<0?n:n*-1.0;

  Vector f=obj.c;
  double p=obj.f;

  if (++depth>D) /*if (Random()<p) f=f*(1/p); else*/ return obj.e; //R.R. 
  if (obj.refl == 0) // Diffuse
  {    
    double r1=2*M_PI*Random(), r2=Random(), r2s=sqrt(r2); 
    Vector w=nl;
    Vector u;
    Vector v;

    if (fabs(w[0])>0.1) 
    {
      u=Vector(0,1,0);
      v=Vector(w[2],0.0,w[0]);
    }
    else
    {
      u=Vector(1,0,0);
      v=Vector(0.0,-w[2],w[1]);
    }
    Vector d = Normalized(u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1-r2)); 
    return obj.e + f.Scale(radiance(Ray(x,d),depth)); 
  } 
  else if (obj.refl == 1)  // Specular
  {
    return obj.e + f.Scale(radiance(Ray(x,r.Direction()-n*2*(n*r.Direction())),depth)); 
  }
  else // Refractive
  {
    Ray reflRay(x, r.Direction()-n*2*n*(r.Direction()));    
    bool into = n*nl>0;                // Ray from outside going in? 
    double nc=1, nt=1.5, nnt=into?nc/nt:nt/nc, ddn=r.Direction()*nl, cos2t; 
    if ((cos2t=1-nnt*nnt*(1-ddn*ddn))<0)    // Total internal reflection 
      return obj.e + f.Scale(radiance(reflRay,depth)); 
    Vector tdir = Normalized(r.Direction()*nnt - n*((into?1:-1)*(ddn*nnt+sqrt(cos2t)))); 
    double a=nt-nc, b=nt+nc, R0=a*a/(b*b), c = 1-(into?-ddn:tdir*n); 
    double Re=R0+(1-R0)*c*c*c*c*c,Tr=1-Re,P=.25+.5*Re,RP=Re/P,TP=Tr/(1-P); 

    return obj.e + f.Scale(depth>2 ? (Random()<P ?   // Russian roulette 
      radiance(reflRay,depth)*RP:radiance(Ray(x,tdir),depth)*TP) : 
    radiance(reflRay,depth)*Re+radiance(Ray(x,tdir),depth)*Tr); 
  }
} 


int main()
{ 
  int w=X; 
  int h=Y; 
  int samps = S;
  Vector *c=new Vector[X*Y]; 

  Ray camera(Vector(50,52,295.6), Normalized(Vector(0,-0.042612,-1))); // camera pos, dir 
  Vector cx=Vector(w*.5135/h,0,0), cy=Normalized(cx/camera.Direction())*.5135;

  for (int y=0; y<h; y++)
  {  
    fprintf(stderr,"\rRendering (%d spp) %5.2f%%",samps*4,100.*y/(h-1)); 
    for (unsigned short x=0; x<w; x++)
    {
      for (int sy=0, i=(h-y-1)*w+x; sy<2; sy++)
      {
        // 2x2 subpixel rows 
        for (int sx=0; sx<2; sx++)
        {
          Vector r(0.0,0.0,0.0);
          for (int s=0; s<samps; s++)
          { 
            double r1=2*Random(), dx=r1<1 ? sqrt(r1)-1: 1-sqrt(2-r1); 
            double r2=2*Random(), dy=r2<1 ? sqrt(r2)-1: 1-sqrt(2-r2); 
            Vector d = cx*( ( (sx+0.5 + dx)/2 + x)/w - 0.5) + cy*( ( (sy+0.5 + dy)/2 + y)/h - 0.5) + camera.Direction(); 
            r = r + radiance(Ray(camera.Origin()+d*140,Normalized(d)),0)*(1./samps); 
          } 
          c[i] = c[i] + Vector(clamp(r[0]),clamp(r[1]),clamp(r[2]))*.25; 
        } 
      } 
    }
  }

  // Save image as PPM file
  FILE *f = fopen("image.ppm", "w"); 
  fprintf(f, "P3\n%d %d\n%d\n", w, h, 255); 
  for (int i=0; i<w*h; i++) 
  {
    fprintf(f,"%d %d %d ", toInt(c[i][0]), toInt(c[i][1]), toInt(c[i][2]));
  }
  fclose(f);
  delete []c;
  return 0;
}