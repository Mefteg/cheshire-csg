#include <math.h>   
#include <stdlib.h> 
#include <stdio.h>
#include <ctime>
#include <omp.h>

#include "ray.h"
#include "node.h"
#include "primitive.h"
#include "sphere.h"
#include "box.h"


#define X (512/2) // Width
#define Y (384/2) // Height
#define S 100     // Samples
#define D 3       // Recursion depth
#define Pixel 2 //Pixel subdivision

//! \brief Easy coded random function
inline double Random() { return (rand()%10000)/9999.0;}

//!< Scene defined as an array of spheres (radius, position, emission, color, material) 
Node * spheres[] = {
	new Sphere(1e5, Vector( 1e5+1,40.8,81.6), Vector(0.0,0.0,0.0),Vector(.75,.25,.25),0),//Left red
	new Sphere(1e5, Vector(-1e5+99,40.8,81.6),Vector(0.0,0.0,0.0),Vector(.25,.25,.75),0),//Right blue
	new Sphere(1e5, Vector(50,40.8, 1e5),     Vector(0.0,0.0,0.0),Vector(.75,.75,.75),0),//Back 
	new Sphere(1e5, Vector(50,40.8,-1e5+170), Vector(0.0,0.0,0.0),Vector(0.0,0.0,0.0),0),//Front 
	new Sphere(1e5, Vector(50, 1e5, 81.6),    Vector(0.0,0.0,0.0),Vector(.75,.75,.75),0),//Botom white
	new Sphere(1e5, Vector(50,-1e5+81.6,81.6),Vector(0.0,0.0,0.0),Vector(.75,.75,.75),0),//Top white
	new Sphere(16.5,Vector(27,16.5,47),       Vector(0.0,0.0,0.0),Vector(1,1,1)*.999, 1),//Mirror 
	new Sphere(16.5,Vector(73,16.5,78),       Vector(0.0,0.0,0.0),Vector(1,1,1)*.999, 2),//Glass 
	new Sphere(600, Vector(50,681.6-.27,81.6),Vector(12,12,12),  Vector(0.0,0.0,0.0), 0),//Light
	//new Box(Vector(50,16.5,147), Vector(75,25,160), Vector(0.0,0.0,0.0), Vector(0.75,0.25,0.25), 0) //First box 
};
int nbObj=9;

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
\brief Return true if an intersection is found and the nearest object found
*/
inline bool IntersectScene(const Ray &r, double &t, int &id,Vector& n, Vector& x)
{ 
	bool k=false;
	// for each sphere
	for (int i=0;i<nbObj;i++) 
	{
		double d; 
		// if the ray intersects the sphere i
		if(spheres[i]->Intersect(r,d,n,x)) 
		{ 
			// if it's the first intersection
			if (k==false) { t=d; id=i;} 
			// else if the distance d is lower than t
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
	double t;
	Vector n;// distance to Intersection 
	Vector x; //point d'intersection
	int id=0;                               // id of Intersected object 
	// if no intersection found, return the null vector
	if (!IntersectScene(r, t, id,n,x)) return Vector(0.0,0.0,0.0); 

	Node * obj = spheres[id];


	Vector f=obj->getColor();
	double p=obj->getF();

	// if no rebound is required
	if (++depth>D) /*if (Random()<p) f=f*(1/p); else*/ return obj->getEmission(); //R.R. 
	if (obj->getRefl() == 0) // Diffuse
	{    
		double r1=2*M_PI*Random(), r2=Random(), r2s=sqrt(r2); 
		Vector w=n;
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
		return obj->getEmission() + f.Scale(radiance(Ray(x,d),depth)); 
	} 
	else if (obj->getRefl() == 1)  // Specular
	{
		return obj->getEmission() + f.Scale(radiance(Ray(x,r.Direction()-n*2*(n*r.Direction())),depth)); 
	}
	else // Refractive
	{
		Ray reflRay(x, r.Direction()-n*2*n*(r.Direction()));    
		bool into = n/**nl*/>0;                // Ray from outside going in? 
		double nc=1, nt=1.5, nnt=into?nc/nt:nt/nc, ddn=r.Direction()*nl, cos2t; 
		if ((cos2t=1-nnt*nnt*(1-ddn*ddn))<0)    // Total internal reflection 
			return obj->getEmission() + f.Scale(radiance(reflRay,depth)); 
		Vector tdir = Normalized(r.Direction()*nnt - n*((into?1:-1)*(ddn*nnt+sqrt(cos2t)))); 
		double a=nt-nc, b=nt+nc, R0=a*a/(b*b), c = 1-(into?-ddn:tdir*n); 
		double Re=R0+(1-R0)*c*c*c*c*c,Tr=1-Re,P=.25+.5*Re,RP=Re/P,TP=Tr/(1-P); 

		return obj->getEmission() + f.Scale(depth>2 ? (Random()<P ?   // Russian roulette 
			radiance(reflRay,depth)*RP:radiance(Ray(x,tdir),depth)*TP) : 
		radiance(reflRay,depth)*Re+radiance(Ray(x,tdir),depth)*Tr); 
	}
} 

double now()
{
	clock_t t = clock();
	return t;
}

int main()
{ 
	double t = now();

	int w=X; 
	int h=Y; 
	int samps = S;
	// Save the color of each pixel
	Vector* c = new Vector[X*Y]; 

	Ray camera(Vector(50,52,295.6), Normalized(Vector(0,-0.042612,-1))); // camera pos, dir 
	Vector cx=Vector(w*.5135/h,0,0), cy=Normalized(cx/camera.Direction())*.5135;

	// for each line of pixel
	#pragma omp parallel for num_threads(omp_get_num_procs())
	for (int y=0; y<h; y++)
	{  
		//progression update
		fprintf(stderr,"\rRendering (%d spp) %5.2f%%",samps*(Pixel*Pixel),100.*y/(h-1));
		// for each column of pixel
		for (unsigned short x=0; x<w; x++)
		{
			// indicate the focused pixel
			int i=(h-y-1)*w+x;
			// Its color is set to black
			c[i]=Vector(0,0,0);
			// the focused pixel is subdivided in 4 ( 2x2 )
			for (int sy=0; sy<Pixel; sy++)
			{
				// 2x2 subpixel rows 
				for (int sx=0; sx<Pixel; sx++)
				{
					Vector r(0.0,0.0,0.0);
					// in each part of the pixel, $samps ray are thrown
					for (int s=0; s<samps; s++)
					{ 
						double r1=2*Random(), dx=r1<1 ? sqrt(r1)-1: 1-sqrt(2-r1); 
						double r2=2*Random(), dy=r2<1 ? sqrt(r2)-1: 1-sqrt(2-r2); 
						Vector d = cx*( ( (sx+0.5 + dx)/Pixel + x)/w - 0.5) + cy*( ( (sy+0.5 + dy)/Pixel + y)/h - 0.5) + camera.Direction(); 
						//get color of objet hit by the ray
						r = r + radiance(Ray(camera.Origin()+d*140,Normalized(d)),0)*(1./samps); 
					}
					//fill the  pixel with color
					c[i] = c[i] + Vector(clamp(r[0]),clamp(r[1]),clamp(r[2]))*(1.0/((float) (Pixel*Pixel))); 
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
	
	t = now() - t;

	fprintf(stderr, "\nProcessus used: %d", omp_get_num_procs());
	fprintf( stderr, "\nFunction took : %f seconds\n", (t/1000) );
	int out;
	scanf("%d", out );

	return 0;
}