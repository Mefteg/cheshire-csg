#include "vector.h"


class Node;

class Intersection {
public:
	Intersection(){};
	~Intersection(){};
	double t; // distance to the origin
	Node * obj;		// intersected object
	Vector pos;
	Vector normal;

	// Opérateur de tri des intersections
	int operator <(const Intersection & i) const {
		return t < i.t;
	}
	int operator >(const Intersection & i) const {
		return t > i.t;
	}
};

