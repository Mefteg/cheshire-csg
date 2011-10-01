# include "cylinder.h"

Cylinder::Cylinder(const double& radius, const Vector& bottom, const double height, const Vector& e, const Vector& c, int refl) :
	Primitive(e, c, refl)
{
	this->radius = radius;
	this->bottom = bottom;
	this->height = height;
}

int Cylinder::Intersect(const Ray& ray, Intersection& inter1 ) {
	return 0;
}

int Cylinder::Intersect(const Ray& ray, Intersection& inter1, Intersection& inter2 )
{
	inter1.obj = this;
	inter2.obj = this;

	Vector p_bis = ray.Origin() - this->bottom;
	Vector dir = ray.Direction();
	
	//on ramène à l'origine
	Ray r_bis( p_bis, dir );

	float a = dir[0]*dir[0] + dir[2]*dir[2];
	float b = 2*(p_bis[0]*dir[0] + p_bis[2]*dir[2]);
	float c = p_bis[0]*p_bis[0] + p_bis[2]*p_bis[2] - radius*radius;
	float delta = sqrt(b*b - 4*a*c);

	if (delta < 0) return 0;
	else
	{
		float t1 = (-b - delta) / (2*a);
		float t2 = (-b + delta) / (2*a);

		//pour que t1 soit l'intersection la plus proche
		if(t1 > t2)
		{
			float bis = t2;
			t2 = t1;
			t1 = bis;
		}

		Vector tmp;

		inter1.t = t1;
		inter1.pos = r_bis(t1) + bottom;
		tmp = Vector(0,-1,0);
		inter1.normal = Normalized(ray.Direction() - tmp);

		inter2.t = t2;
		inter2.pos = r_bis(t2) + bottom;
		tmp = Vector(0,-1,0);
		inter2.normal = Normalized(ray.Direction() - tmp);

		//si les deux intersections sont au dessus ou au dessous du cylindre, ça ne compte pas
		if((inter1.pos[1] > bottom[1]+height && inter2.pos[1] > bottom[1]+height)
			|| (inter1.pos[1] < bottom[1] && inter2.pos[1] < bottom[1]))
			return 0;

		//si inter1 est au dessus du cylindre
		if ( inter1.pos[1] > (bottom[1] + height) ) {
			int t = (ray.Origin()[1] - (bottom[1] + height)) / ray.Direction()[1];
			inter1.t = t;
			inter1.pos = ray(t);
			inter1.normal = Vector( 0, 1, 0 );
		}
		//sinon si inter1 est au dessous du cylindre
		else if ( inter1.pos[1] < bottom[1] ) {
			int t = (ray.Origin()[1] - bottom[1]) / ray.Direction()[1];
			inter1.t = t;
			inter1.pos = ray(t);
			inter1.normal = Vector( 0, -1, 0 );
		}

		//si inter2 est au dessus du cylindre
		if ( inter2.pos[1] > (bottom[1] + height) ) {
			int t = (ray.Origin()[1] - (bottom[1] + height)) / ray.Direction()[1];
			inter2.t = t;
			inter2.pos = ray(t);
			inter2.normal = Vector( 0, 1, 0 );
		}
		//sinon si inter2 est au dessous du cylindre
		else if ( inter2.pos[1] < bottom[1] ) {
			int t = (ray.Origin()[1] - bottom[1]) / ray.Direction()[1];
			inter2.t = t;
			inter2.pos = ray(t);
			inter2.normal = Vector( 0, -1, 0 );
		}

		return 1;
	}
}

int Cylinder::PMC(const Vector& point)
{
	if((point.y > bottom.y+height) && (point.y < bottom.y)) return 0;
	Vector repos = Vector(point.x + (bottom.x * -1), point.y + (bottom.y * -1), point.z + (bottom.z * -1));
	if(sqrt(repos.x) + sqrt(repos.z) > radius) return 0;

	return 1;
}
