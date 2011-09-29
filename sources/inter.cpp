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

int Inter::Intersect(const Ray& ray, Intersection& t1, Intersection& t2) {
	Intersection tl1, tl2, tr1, tr2;
	int retLeft = this->left->Intersect(ray,tl1,tl2);
	int retRight = this->right->Intersect(ray,tr1,tr2);

	//if no collision
	if(!(retLeft || retRight))
			return 0;

	//if collision on the left node only or right node only
	if( (retLeft && !retRight)||(!retLeft && retRight) ){
		return 0;
	//if collision on both
	}
    else {
		//search for the nearest intersection
		if ( tl1 < tr1 ) {
			t1 = tl1;
/*			t1.obj = this->left;*/
		}
        else {
			t1 = tr1;
/*			t1.obj = this->right;*/
		}

		//search for the farest intersection
		if ( tl2 > tr2 ) {
			t2 = tl2;
/*			t2.obj = this->left;*/
		}
        else {
			t2 = tr2;
/*			t2.obj = this->right;*/
		}
	}

	return 1;
}

int Inter::PMC(const Vector& u) {
    return (this->left->PMC(u) && this->right->PMC(u));
}
