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
	
	//if no collision
	if(!(retLeft || retRight))
			return 0;

	//if collision on the left node only
	if(retLeft && !retRight){
		t = tl;
		t.obj = this->left;
	//if collision on the right node only
	}else if(!retLeft && retRight){
		t = tr;
		t.obj = this->right;
	//else search for the nearest collision
	}else if ( tl < tr ) {
		t = tl;
		t.obj = this->left;
	}
	else {
		t = tr;
		t.obj = this->right;
	}
	
	return 1;
}