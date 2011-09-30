#include "rotation.h"
#include <math.h>

#define M_PI  3.14159265358979323846

Rotation::Rotation(void)
{
}

Rotation::Rotation(Node * left,const Vector v,float angle) : Transfo(left)
{
	double rad = angle * M_PI / 180;
	Normalized(v);
	double c = cos(rad);
	double s = sin(rad);
	
	//construire la matrice de rotation autour de l'axe v
	m(0,0) = v.x*v.x + (1-v.x*v.x)*c;    m(0,1) = v.x*v.y*(1-c)-v.z*s;     m(0,2) = v.x*v.z*(1-c)+v.y*s;
	m(1,0) = v.x*v.y*(1-c)+v.z*s;        m(1,1) = v.y*v.y+(1-v.y*v.y)*c;   m(1,2) = v.y*v.z*(1-c)-v.x*s;
	m(2,0) = v.x*v.z*(1-c)-v.y*s;        m(2,1) = v.y*v.z*(1-c)+v.x*s;     m(2,2) = v.z*v.z+(1-v.z*v.z)*c;
	//garder la matrice de rotation pure
	mRotate = m;
	mRotateInv = mRotate.Invert(mRotate);
	//matrice de translation de l'objet à l'origine
	Matrix4Df tr;tr.SetIdentity();
	Vector p = left->getPosition();
	tr(0,3) = -1*p[0];
	tr(1,3) = -1*p[1];
	tr(2,3) = -1*p[2];
	//matrice de translation inverse
	Matrix4Df trInv;trInv.SetIdentity();
	trInv = tr.Invert(tr);

	m = trInv*m*tr;

	//inverse de la matrice de rotation
	mInv = m.Invert(m);
}

Rotation::~Rotation(void)
{
	delete left;
}

int Rotation::Intersect(const Ray& ray, Intersection& t) {
	Intersection tt;
		
	Ray r = Ray( mInv.MulPt(Vector(ray.Origin()[0],ray.Origin()[1],ray.Origin()[2])),
				 mInv.MulDir(ray.Direction()));
	if(left->Intersect(r,tt)){
		t=tt;
		t.pos = m.MulPt(t.pos);
		t.normal = m.MulPt(t.normal);
		t.obj = this->left;
		return 1;
	}
	
	return 0;
}

int Rotation::Intersect(const Ray& ray, Intersection& t, Intersection& t2){
	Intersection tt,tt2;
	
	Ray r = Ray( mInv.MulPt(Vector(ray.Origin()[0],ray.Origin()[1],ray.Origin()[2])),
				 mInv.MulDir(ray.Direction()));

	if(left->Intersect(r,tt,tt2)){
		//premiere intersection
		t=tt;
		t.pos = m.MulPt(t.pos);
		t.normal = mRotate.MulDir(t.normal);
		//deuxieme intersection
		t2=tt2;
		t2.pos = m.MulPt(t2.pos);
		t2.normal = mRotate.MulDir(t2.normal);
		
		return 1;
	}
	
	return 0;
}
int Rotation::PMC(const Vector& u) {
	return left->PMC(mInv.MulPt(u));
}
