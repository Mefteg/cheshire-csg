# include "triangle.h"

Triangle::Triangle(const Vector& p1, const Vector& p2, const Vector& p3, const Vector& e, const Vector& c, int refl) :
	Primitive(e, c, refl)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
}

int Triangle::Intersect(const Ray& ray, Intersection& inter1 ) {
	return 0;
}

int Triangle::Intersect(const Ray& ray, Intersection& inter1, Intersection& inter2 )
{
	inter1.obj = this;
	inter2.obj = this;

    Vector p = ray.Origin();
    Vector d = ray.Direction();

    Vector u( p2[0]-p1[0], p2[1]-p1[1], p2[2]-p1[2] );
    Vector v( p3[0]-p1[0], p3[1]-p1[1], p3[2]-p1[2] );

    if ( (u/v)*d != 0 ) {
        float D = -1*((u/v)*d);
        Vector w( p[0]-p1[0], p[1]-p1[1], p[2]-p1[2] );

        float a = -1*((w/v)*d)/D;
        float b = -1*((u/w)*d)/D;
        float t = ((u/v)*w)/D;

        if ( a > 0 && b > 0 ) {
            if ( a+b <= 1 ) {
                inter1.t = t;
                inter1.pos = ray(t);
                inter1.normal = Normalized(u/v);
/*                inter1.normal = Vector(0,0,1);*/
                inter2 = inter1;

                return 1;
            }
        }
    }

    return 0;
}

int Triangle::PMC(const Vector& point)
{
	return 0;
}

Vector Triangle::getPosition() {
    Vector i = ((p2 - p3) / 2) + p3;
    return (2*(i-p1)/3)+p1;
}
