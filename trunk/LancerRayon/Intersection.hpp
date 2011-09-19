#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include ".\glm-0.9.0\glm\setup.hpp"
#include ".\glm-0.9.0\glm\glm.hpp"
#include ".\glm-0.9.0\glm\ext.hpp"

class Objet3D;
class Intersection
{
public:
	Intersection();
	~Intersection();
	float dist; // La distance � l'origine de l'intersection
	Objet3D *Objet;		// l'objet intersect�
	glm::vec3 normal;


	// Op�rateur de tri des intersections
	int operator <(const Intersection & i) const {
		return dist < i.dist;
	}
	int operator >(const Intersection & i) const {
		return dist > i.dist;
	}
};



#endif
