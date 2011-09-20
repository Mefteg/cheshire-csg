#include "union.h"


Union::Union(void)
{
}

Union::Union(Node * left, Node * right) : OpBin(left, right)
{
}

Union::~Union(void)
{
}

int Union::Intersect(const Ray& ray, Intersection& t) {
	Intersection tl, tr;
	int retLeft = this->left->Intersect(ray,tl);
	int retRight = this->right->Intersect(ray,tr);
	t = tl<tr ? tl : tr;

	return (retLeft || retRight);
}
