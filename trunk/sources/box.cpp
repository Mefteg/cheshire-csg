
#include <stdio.h>
#include "box.h"


const double Box::epsilon=1.0e-5;

Box::Box(const Vector& c,const double& r)
{
	a=c-Vector(r,r,r);
	b=c+Vector(r,r,r);
}

Box::Box(const Vector& a,const Vector& b, const Vector& e, const Vector &c, int refl) :
	Primitive( e, c, refl )
{
	this->a=a;
	this->b=b;
}

Box::Box(const Vector& a)
{
	Box::b=Box::a=a;
}

Box::Box(Vector* v, int n)
{
	for (int j = 0; j < 3; j++)
	{
		a[j] = v[0][j];
		b[j] = v[0][j];
		
		for (int i = 1; i < n; i++)
		{
			if (v[i][j] < a[j]) a[j] = v[i][j];
			if (v[i][j] > b[j]) b[j] = v[i][j];
		}
	}
}

Box::Box(const Box& x,const Box& y)
{
	a = min(x.a,y.a);
	b = max(x.b,y.b);
}

int Box::Intersect(const Ray& ray, Intersection& inter) {
	Intersection inter1,inter2;
	int i = this->Intersect(ray, inter1, inter2);

    inter = inter2;
    //get the nearest intersection
	if(inter1.t > 0.000001)
		//get the nearest intersection
		inter = inter1;
	else
		inter = inter2;
	//position of the intersection
	inter.pos = ray(inter.t);
	//pointer to the box
	inter.obj = this;

	return i;
}

int Box::Intersect(const Ray& ray,Intersection& intermin,Intersection& intermax)
{
	intermin.t =-1e16;
	intermax.t =1e16;
	intermin.obj = this;
	intermax.obj = this;

	Vector p=ray.Origin();
	Vector d=ray.Direction();

	double t;

	if (d[0]<-epsilon)
	{
		t=(a[0]-p[0])/d[0];
		if (t<intermin.t) return 0;
		if (t<=intermax.t)
		{
			intermax.t=t;
			intermax.normal=Vector(-1.0,0.0,0.0); //face gauche
		}
		t=(b[0]-p[0])/d[0];
		if (t>=intermin.t)
		{
			if (t>intermax.t) return 0;
			intermin.t=t;
			intermin.normal=Vector(1.0,0.0,0.0); //face droite
		}
	}
	else if (d[0]>epsilon)
	{
		t=(b[0]-p[0])/d[0];
		if (t<intermin.t) return 0;
		if (t<=intermax.t)
		{
			intermax.t=t;
			intermax.normal=Vector(1.0,0.0,0.0); //face droite
		}
		t=(a[0]-p[0])/d[0];
		if (t>=intermin.t)
		{
			if (t>intermax.t) return 0;
			intermin.t=t;
			intermin.normal=Vector(-1.0,0.0,0.0); //face gauche
		}
	}
	else if (p[0]<a[0] || p[0]>b[0]) return 0;

	if (d[1]<-epsilon)
	{
		t=(a[1]-p[1])/d[1];
		if (t<intermin.t) return 0;
		if (t<=intermax.t)
		{
			intermax.t=t;
			intermax.normal=Vector(0.0,-1.0,0.0); //face dessous
		}
		t=(b[1]-p[1])/d[1];
		if (t>=intermin.t)
		{
			if (t>intermax.t) return 0;
			intermin.t=t;
			intermin.normal=Vector(0.0,1.0,0.0); //face dessus
		}
	}
	else if (d[1]>epsilon)
	{
		t=(b[1]-p[1])/d[1];
		if (t<intermin.t) return 0;
		if (t<=intermax.t)
		{
			intermax.t=t;
			intermax.normal=Vector(0.0,1.0,0.0); //face dessus
		}
		t=(a[1]-p[1])/d[1];
		if (t>=intermin.t)
		{
			if (t>intermax.t) return 0;
			intermin.t=t;
			intermin.normal=Vector(0.0,-1.0,0.0); //face dessous
		}
	}
	else if (p[1]<a[1] || p[1]>b[1]) return 0;

	if (d[2]<-epsilon)
	{
		t=(a[2]-p[2])/d[2];
		if (t<intermin.t) return 0;
		if (t<=intermax.t)
		{
			intermax.t=t;
			intermax.normal=Vector(0.0,0.0,-1.0); //face arrière
		}
		t=(b[2]-p[2])/d[2];
		if (t>=intermin.t)
		{
			if (t>intermax.t) return 0;
			intermin.t=t;
			intermin.normal=Vector(0.0,0.0,1.0); //face avant
		}
	}
	else if (d[2]>epsilon)
	{
		t=(b[2]-p[2])/d[2];
		if (t<intermin.t) return 0;
		if (t<=intermax.t)
		{
			intermax.t=t;
			intermax.normal=Vector(0.0,0.0,1.0); //face avant
		}
		t=(a[2]-p[2])/d[2];
		if (t>=intermin.t)
		{
			if (t>intermax.t) return 0;
			intermin.t=t;
			intermin.normal=Vector(0.0,0.0,-1.0); //face arrière
		}
	}
	else if (p[2]<a[2] || p[2]>b[2]) return 0;

	intermin.pos = ray(intermin.t);
	intermax.pos = ray(intermin.t);

	return 1;
}

int Box::Intersect(const Ray& ray,double& t,Vector& n) const
{
	double u;
	Vector nu;
	return 0;
}

int Box::Inside(const Box& box) const
{
	return ((a<box.a) && (b>box.b));
}

int Box::Inside(const Vector& u) const
{
	return ((a<u) && (b>u));
}

int Box::PMC(const Vector& u)
{
	return this->Inside(u);
}
