#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <vector>
#include <string>
#include <omp.h>

#include "ray.h"
#include "node.h"
#include "primitive.h"
#include "sphere.h"
#include "box.h"
#include "cylinder.h"
#include "opbin.h"
#include "union.h"
#include "inter.h"
#include "diff.h"
#include "translation.h"
#include "triangle.h"
#include "rotation.h"


/*#define X (512/2) // Width*/
/*#define Y (384/2) // Height*/
/*#define S 50     // Samples*/
/*#define D 3       // Recursion depth*/
/*#define Pixel 1 //Pixel subdivision*/

//! \brief Easy coded random function
inline double Random() { return (rand()%10000)/9999.0;}

//! build a coordinate system from vector v1
inline
void CoordinateSystem( const Vector &v1, Vector *v2, Vector *v3 )
{
	if ( fabsf( v1[0] ) > fabsf( v1[1] ) )
    {
		float invLen = 1.f / sqrtf( v1[0] * v1[0] + v1[2] * v1[2] );
        *v2 = Vector( -v1[2] * invLen, 0.f, v1[0] * invLen );
    }
    else
    {
        float invLen = 1.f / sqrtf( v1[1] * v1[1] + v1[2] * v1[2] );
        *v2 = Vector( 0.f, v1[2] * invLen, -v1[1] * invLen );
    }

    *v3 =  v1 / *v2 ;
}

//!< Scene defined as an array of nodes (radius, position, emission, color, material)
std::vector<Node *> nodes;
int nbObj;

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
inline bool IntersectScene(const Ray &r, Intersection& inter)
{
	Intersection t1, t2;
	bool k=false;
	// for each sphere
	for (int i=0;i<nbObj;i++)
	{
		double d;
		// if the ray intersects the sphere i
		if(nodes[i]->Intersect( r, t1, t2 ))
		{
            if ( t1.t > 0 ) {
                // if it's the first intersection
                if (k==false) {
                    inter = t1;
                    d = t1.t;
                }
                // else if the new intersection is in front of the last registered
                else {
                    if (d>t1.t) {
                        inter=t1;
                        d=t1.t;
                    }
                }
                k=true;
            }
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
Vector radiance(const Ray &r, int depth, int D)
{
	Intersection inter;                     // id of Intersected object
	// if no intersection found, return the null vector
	if (!IntersectScene(r, inter)) return Vector(0.0,0.0,0.0);

	Node * obj = inter.obj;

/*	fprintf(stderr,"radiance niveau %d\n",depth);*/
/*    fprintf(stderr,"Refl : %d\n",obj->getRefl());*/
/*    fprintf(stderr, "obj position : %f %f %f \n", obj->getPosition()[0], obj->getPosition()[1], obj->getPosition()[2]);*/
/*    fprintf(stderr, "rayon origin : %f %f %f \n", r.Origin()[0], r.Origin()[1], r.Origin()[2]);*/
/*    fprintf(stderr, "rayon direction : %f %f %f \n", r.Direction()[0], r.Direction()[1], r.Direction()[2]);*/
/*    fprintf(stderr, "rayon/obj impact : %f %f %f \n", inter.pos[0], inter.pos[1], inter.pos[2]);*/

	//intersection coordinates
	Vector x = inter.pos;
/*    x += Vector(0,3,0);*/
	//normal of the object at the intersection
	Vector n = inter.normal;
	Vector nl=n*(r.Direction())<0?n:n*-1.0;
/*    fprintf(stderr, "nl : %f %f %f \n", nl[0], nl[1], nl[2]);*/

	Vector f=obj->getColor();
	double p=obj->getF();

	// if no rebound is required
    if (++depth>D) /*if (Random()<p) f=f*(1/p); else*/ return obj->getEmission(); //R.R.
    if (obj->getRefl() == 0) // Diffuse
    {
        double r1=2*M_PI*Random(), r2=Random(), r2s=sqrt(r2);
        Vector w=nl;
        Vector u;
        Vector v;

        CoordinateSystem(w,&u,&v);
        Vector d = Normalized(u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1-r2));
        return obj->getEmission() + f.Scale(radiance(Ray(x,d),depth,D));
    }
    else if (obj->getRefl() == 1)  // Specular
    {
            return obj->getEmission() + f.Scale(radiance(Ray(x,r.Direction()-n*2*(n*r.Direction())),depth,D));
    }
    else // Refractive
    {
            Ray reflRay(x, r.Direction()-n*2*n*(r.Direction()));
            bool into = n*nl>0;                // Ray from outside going in?
            double nc=1, nt=1.5, nnt=into?nc/nt:nt/nc, ddn=r.Direction()*nl, cos2t;
            if ((cos2t=1-nnt*nnt*(1-ddn*ddn))<0)    // Total internal reflection
                    return obj->getEmission() + f.Scale(radiance(reflRay,depth,D));
            Vector tdir = Normalized(r.Direction()*nnt - n*((into?1:-1)*(ddn*nnt+sqrt(cos2t))));
            double a=nt-nc, b=nt+nc, R0=a*a/(b*b), c = 1-(into?-ddn:tdir*n);
            double Re=R0+(1-R0)*c*c*c*c*c,Tr=1-Re,P=.25+.5*Re,RP=Re/P,TP=Tr/(1-P);

            return obj->getEmission() + f.Scale(depth>2 ? (Random()<P ?   // Russian roulette
                    radiance(reflRay,depth,D)*RP:radiance(Ray(x,tdir),depth,D)*TP) :
            radiance(reflRay,depth,D)*Re+radiance(Ray(x,tdir),depth,D)*Tr);
    }

}

int main( int argc, char ** argv )
{
    int X = (512/2); // Width
    int Y = (384/2); // Height
    int S = 50;    // Samples
    int D = 3;      // Recursion depth
    int Pixel = 2; //Pixel subdivision
    int C = 1; //Cores

	for ( int i=1; i<argc; i++ ) {
        std::string str = argv[i];

		//-s pour S
		if ( str.compare("-s") == 0 ) {
			if ( argv[i+1] != NULL ) {
				std::string v = argv[i+1];
				S = atoi( v.c_str() );
			}
		}

		//-d pour D
		if ( str.compare("-d") == 0 ) {
			if ( argv[i+1] != NULL ) {
				std::string v = argv[i+1];
				D = atoi( v.c_str() );
			}
		}

		//-p pour Pixel
		if ( str.compare("-p") == 0 ) {
			if ( argv[i+1] != NULL ) {
				std::string v = argv[i+1];
				Pixel = atoi( v.c_str() );
			}
		}

		//-c pour C
		if ( str.compare("-c") == 0 ) {
			if ( argv[i+1] != NULL ) {
				std::string v = argv[i+1];
				C = atoi( v.c_str() );
			}
		}
	}
/*
	Sphere * sp1 = new Sphere(15, Vector( 30,30,80), Vector(0.0,0.0,0.0),Vector(.75,.25,.25),0);
	Sphere * sp2 = new Sphere(15, Vector( 40,30,90), Vector(0.0,0.0,0.0),Vector(.25,.25,.75),0);

    Box * b1 = new Box(Vector(10,10,80), Vector(30,30,100), Vector(0,0,0), Vector(0.75,0.25,0.25), 0); //First b
    Box * b2 = new Box(Vector(20,20,90), Vector(40,40,110), Vector(0,0,0), Vector(0.25,0.75,0.25), 0); //First b
    Box * b3 = new Box(Vector(50,30,100), Vector(70,50,130), Vector(0,0,0), Vector(0.25,0.75,0.25), 0); //First b

    Cylinder * c1 = new Cylinder( 10, Vector(40,10,80), 20, Vector(0,0,0), Vector(0.25,0.75,0.75), 0 );
    Cylinder * c2 = new Cylinder( 10, Vector(50,50,50), 20, Vector(0,0,0), Vector(0.25,0.75,0.75), 0 );
    Cylinder * c3 = new Cylinder( 5, Vector(80,20,50), 40, Vector(0,0,0), Vector(0.25,0.75,0.75), 0 );
*/
	//creation of the scene
/*	nodes.push_back(new Translation( sp1, Vector(1,0,0)));*/

/*	nodes.push_back(new Diff( new Diff( b1, b2), b3));*/
/*	nodes.push_back(new Diff( b1, b2));*/
    nodes.push_back(new Box(Vector(-20,0,0), Vector(0,100,200), Vector(0,0,0), Vector(0.75,0.25,0.25), 0)); //Wall left
    nodes.push_back(new Box(Vector(-20+120,0,0), Vector(0+120,100,200), Vector(0,0,0), Vector(0.75,0.25,0.25), 0)); //Wall right
    nodes.push_back(new Box(Vector(-10,0,-10), Vector(100,100,0), Vector(0,0,0), Vector(0.25,0.25,0.75), 0)); //Wall far
    nodes.push_back(new Box(Vector(-10,0,-10+200), Vector(100,100,0+200), Vector(0,0,0), Vector(0.25,0.25,0.75), 0)); //Wall near
    nodes.push_back(new Box(Vector(-10,-10,0), Vector(100,0,200), Vector(0,0,0), Vector(0.75,0.75,0.75), 0)); //Ground
    nodes.push_back(new Box(Vector(-10,0+100,0), Vector(100,10+100,200), Vector(0,0,0), Vector(0.75,0.75,0.75), 0)); //Roof
    nodes.push_back(new Sphere(30, Vector(50,120,40), Vector(8,8,8),  Vector(0.0,0.0,0.0), 0));//Light

/*	nodes.push_back( new Box( Vector(40,10,60), Vector(60,30,80), Vector(0,0,0), Vector(0.25,0.75,0.25), 0 ) );*/

/*	nodes.push_back(new Sphere(1e5, Vector( 1e5+1,40.8,81.6), Vector(0.0,0.0,0.0),Vector(.75,.25,.25),0));//Left red*/
/*	nodes.push_back(new Sphere(1e5, Vector(-1e5+99,40.8,81.6),Vector(0.0,0.0,0.0),Vector(.25,.25,.75),0));//Right blue*/
/*	nodes.push_back(new Sphere(1e5, Vector(50,40.8, 1e5),     Vector(0.0,0.0,0.0),Vector(.75,.75,.75),0));//Back*/
/*	nodes.push_back(new Sphere(1e5, Vector(50,40.8,-1e5+170), Vector(0.0,0.0,0.0),Vector(0.0,0.0,0.0),0));//Front*/
/*	nodes.push_back(new Sphere(1e5, Vector(50, 1e5, 81.6),    Vector(0.0,0.0,0.0),Vector(.75,.75,.75),0));//Botom white*/
/*	nodes.push_back(new Sphere(1e5, Vector(50,-1e5+81.6,81.6),Vector(0.0,0.0,0.0),Vector(.75,.75,.75),0));//Top white*/
/*	nodes.push_back(new Sphere(16.5,Vector(27,16.5,47),       Vector(0.0,0.0,0.0),Vector(1,1,1)*.999,1));//Mirror*/
/*	nodes.push_back(new Sphere(16.5,Vector(73,16.5,78),       Vector(0.0,0.0,0.0),Vector(1,1,1)*.999, 2));//Glass*/
/*	nodes.push_back(new Sphere(600, Vector(50,681.6-.27,81.6),Vector(12,12,12),  Vector(0.0,0.0,0.0), 0));//Light*/
	//nodes.push_back(new Box(Vector(42,22.5,100), Vector(55,29,120), Vector(0.0,0.0,0.0), Vector(0.75,0.25,0.25), 0)); //First box
/*	nodes.push_back(new Box(Vector(-30,-30,-30), Vector(30,30,30), Vector(0,0,0), Vector(0.25,0.75,0.25), 0)); //First box*/
	//nodes.push_back(new Sphere(1,Vector(0,0,0),       Vector(0.0,0.0,0.0),Vector(1,1,1)*.999,1));//Mirror
	//nodes.push_back(new Sphere(1,Vector(2,0,0),       Vector(0.0,0.0,0.0),Vector(1,1,1)*.999,1));//Mirror
	//nodes.push_back(new Sphere(1,Vector(0,2,0),       Vector(0.0,0.0,0.0),Vector(1,1,1)*.999,1));//Mirror
	//nodes.push_back(new Sphere(1,Vector(0,0,2),       Vector(0.0,0.0,0.0),Vector(1,1,1)*.999,1));//Mirror
/*    nodes.push_back(new Box(Vector(0,2,-1), Vector(6,4,1), Vector(12,12,12), Vector(1,1,1)*0.9, 1)); //Lig*/

 
/************************  Cheshire's Cat  ************************/

	/*** La tête ***/

	// Les dents :
/*	Box* dent_1 = new Box(Vector(20,10,50), Vector(22,30,50), Vector(0,0,0), Vector(0,0,0), 0);
	Box* dent_2 = new Box(Vector(22,10,50), Vector(24,30,50), Vector(0,0,0), Vector(255,255,255), 0);
	Box* dent_3 = new Box(Vector(24,10,50), Vector(26,30,50), Vector(0,0,0), Vector(0,0,0), 0);
	Box* dent_4 = new Box(Vector(26,10,50), Vector(28,30,50), Vector(0,0,0), Vector(255,255,255), 0);
	Box* dent_5 = new Box(Vector(28,10,50), Vector(30,30,50), Vector(0,0,0), Vector(0,0,0), 0);
	Box* dent_6 = new Box(Vector(30,10,50), Vector(32,30,50), Vector(0,0,0), Vector(255,255,255), 0);
	Box* dent_7 = new Box(Vector(32,10,50), Vector(34,30,50), Vector(0,0,0), Vector(0,0,0), 0);
	Box* dent_8 = new Box(Vector(34,10,50), Vector(36,30,50), Vector(0,0,0), Vector(255,255,255), 0);
	Box* dent_9 = new Box(Vector(36,10,50), Vector(38,30,50), Vector(0,0,0), Vector(0,0,0), 0);
	Box* dent_10 = new Box(Vector(38,10,50), Vector(40,30,50), Vector(0,0,0), Vector(255,255,255), 0);
	Box* dent_11 = new Box(Vector(40,10,50), Vector(42,30,50), Vector(0,0,0), Vector(255,255,255), 0);
	Box* dent_12 = new Box(Vector(42,10,50), Vector(44,30,50), Vector(0,0,0), Vector(0,0,0), 0);
	Box* dent_13 = new Box(Vector(44,10,50), Vector(46,30,50), Vector(0,0,0), Vector(255,255,255), 0);
	Node* dents = new Union(new Union(new Union(new Union(new Union(new Union(new Union(new Union(new Union(new Union(new Union(new Union(dent_1, dent_2), dent_3), dent_4), dent_5), dent_6), dent_7), dent_8), dent_9), dent_10), dent_11), dent_12), dent_13);
	
	// Le sourire :
	Node* sourire = new Diff(new Sphere(, Vector(,,), Vector(0,0,0),  Vector(0.0,0.0,0.0), 0),new Diff(new Sphere(, Vector(,,), Vector(0,0,0),  Vector(0.0,0.0,0.0), 0), dents));
*/	
	// Les oreilles :
	Triangle* oreille_gauche = new Triangle(Vector(13,79,68),Vector(20,79,68),Vector(16,86,68), Vector(0,0,0), Vector(0.8,0.8,0.2), 0);
	Triangle* oreille_droite = new Triangle(Vector(26,79,68),Vector(33,79,68),Vector(28,86,68), Vector(0,0,0), Vector(0.8,0.8,0.2), 0);

	// Les yeux :
	Sphere* oeil_gauche = new Sphere(4, Vector(19,72,82), Vector(0,0,0),  Vector(255,255,255), 0);
	Sphere* oeil_droit = new Sphere(4, Vector(28,72,82), Vector(0,0,0),  Vector(255,255,255), 0);

	// Les pupilles :
	Sphere* pupille_gauche = new Sphere(2, Vector(20,71,86), Vector(0,0,0),  Vector(0,0,0), 0);
	Sphere* pupille_droite = new Sphere(2, Vector(29,71,86), Vector(0,0,0),  Vector(0,0,0), 0);

	// Le nez :
	Triangle* nez = new Triangle(Vector(23,66,90),Vector(26,66,90),Vector(24,68,90), Vector(0,0,0), Vector(255,0,0), 0);
	
	// le visage :
	Sphere* visage = new Sphere(15, Vector(22,70,60), Vector(0,0,0), Vector(0.8,0.8,0.2), 0);




//	Node* tete = new Union(new Union(new Union(new Union(new Union(new Union(new Union(visage, nez), pupille_gauche), pupille_droite), oeil_gauche), oeil_droit), oreille_gauche), oreille_droite);
//nodes.push_back(tete);	
//	Node* tete = new Union(new Union(new Union(new Union(new Union(new Union(new Union(new Union(visage, nez), pupille_gauche), pupille_droite), oeil_gauche), oeil_droite), oreille_gauche), oreilles_droite), sourire);

	/***************/
	
	/*** Le corps ***/

	// Les épaules :
	Sphere* epaules = new Sphere(15, Vector(37,47,60), Vector(0,0,0), Vector(0.8,0.8,0.2), 0);


	// Le bassin :
	Node* bassin = new Inter(new Sphere( , Vector(,,), Vector(0,0,0), Vector(204,51,204), 0), new Sphere( , Vector(,,), Vector(0,0,0), Vector(204,51,204), 0));
	
	// Le buste :
	Rotation* buste = new Rotation(new Cylinder(15, Vector(37,47,60), 30, Vector(0,0,0), Vector(0.8,0.8,0.2), 0), Vector(0,0,1), 90);


	// La patte avant :
	
	// La patte arrière :

	/****************/
	
	/*** La queue ***/
	
	// YAHOUUUUUU
	
	/****************/
	
	nodes.push_back(oreille_gauche);
	nodes.push_back(oreille_droite);
	nodes.push_back(nez);
	nodes.push_back(pupille_gauche);
	nodes.push_back(pupille_droite);
	nodes.push_back(oeil_gauche);
	nodes.push_back(oeil_droit);
	nodes.push_back(visage);
	nodes.push_back(buste);
	nodes.push_back(epaules);
	
/******************************************************************/

	nbObj = (int) nodes.size();

	//fprintf(stderr, " %f %f %f \n \n",nodes[9]->getColor()[0],nodes[9]->getColor()[1],nodes[9]->getColor()[2]);
	int w=X;
	int h=Y;
	int samps = S;
	// Save the color of each pixel
	Vector* c = new Vector[X*Y];

	Ray camera(Vector(50,52,295.6), Normalized(Vector(0,-0.042612,-1))); // camera pos, dir
	Vector cx=Vector(w*.5135/h,0,0), cy=Normalized(cx/camera.Direction())*.5135;

	// for each line of pixel
	#pragma omp parallel for num_threads(C)
/*	for (int y=0; y<0; y++)*/
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
						r = r + radiance(Ray(camera.Origin()+d*140,Normalized(d)),0,D)*(1./samps);
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

    fprintf(stderr, "\n");

	return 0;
}

