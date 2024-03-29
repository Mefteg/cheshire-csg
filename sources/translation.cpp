#include "translation.h"

Translation::Translation(void)
{
}

Translation::Translation(Node * left,const Vector v) : Transfo(left)
{
	m(0,3) = v[0];
	m(1,3) = v[1];
	m(2,3) = v[2];

	
	mInv = m.Invert(m);
}

Translation::~Translation(void)
{
	delete left;
}

int Translation::Intersect(const Ray& ray, Intersection& t) {
	Intersection tt;

	Matrix4Df mInv = m.Invert(m);

	Ray r = Ray( mInv.MulPt(Vector(ray.Origin()[0],ray.Origin()[1],ray.Origin()[2])), ray.Direction());

	if(left->Intersect(r,tt)){
		t=tt;
		t.pos = m.MulPt(t.pos);
		t.normal = m.MulPt(t.normal);
		t.obj = this->left;
		return 1;
	}

	return 0;
}

int Translation::Intersect(const Ray& ray, Intersection& t,Intersection& t2) {
	Intersection tt,tt2;

	Ray r = Ray( mInv.MulPt(Vector(ray.Origin()[0],ray.Origin()[1],ray.Origin()[2])), ray.Direction());

	if(left->Intersect(r,tt,tt2)){
		//first intersection
		t=tt;
		t.pos = m.MulPt(t.pos);
		//second intersection
		t2=tt2;
		t2.pos = m.MulPt(t2.pos);
		
		return 1;
	}

	return 0;
}

int Translation::PMC(const Vector& u) {
	return left->PMC(mInv.MulPt(u));
}
