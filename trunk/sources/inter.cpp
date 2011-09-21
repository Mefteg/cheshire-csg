#include "inter.h"


Inter::Inter(void)
{
}

Inter::Inter(Node * left, Node * right) : OpBin(left, right)
{
}

Inter::~Inter(void)
{
}

int Inter::Intersect(const Ray& ray, Intersection& t) {
	Intersection tl, tr;
	int retLeft = this->left->Intersect(ray,tl);
	int retRight = this->right->Intersect(ray,tr);
	
	//if no collision
	if(!(retLeft || retRight))
			return 0;

	//if collision on the left node only or right node only
	if( (retLeft && !retRight)||(!retLeft && retRight) ){
		return 0;
	//if collision on both
	}else{
		//search for the nearest intersection
		if ( tl < tr ) {
			t = tl;
			t.obj = this->left;
		}else {
			t = tr;
			t.obj = this->right;
		}
	}
	
	return 1;
}