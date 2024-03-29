#include "diff.h"


Diff::Diff(void)
{
}

Diff::Diff(Node * left, Node * right) : OpBin(left, right)
{
}

Diff::~Diff(void)
{
}

int Diff::Intersect(const Ray& ray, Intersection& t) {
	Intersection tl1,tl2, tr1,tr2;
	int retLeft = this->left->Intersect(ray,tl1,tl2);
	int retRight = this->right->Intersect(ray,tr1,tr2);

	//if no collision
	if( !(retLeft || retRight))
			return 0;
	//or collision only to the right
	if(!retLeft && retRight)
		return 0;

	//if collision on the left node only
	if(retLeft && !retRight){
		t = tl1;
		t.obj = this->left;
		return 1;
	}

	//else it's a collision between the two objects
	//right intersect in the left obj
	if( (tl1>tr1) && (tl1<tr2) ){
		//right intersect 2 outside the left obj
		if(tl2>tr2){
			t = tr2;
			t.normal = -t.normal;
			t.obj = this->left;
			return 1;
		}
	}


	return 0;
}

int Diff::Intersect(const Ray& ray, Intersection& t1, Intersection& t2) {
	Intersection tl1,tl2, tr1,tr2;
    tl1.obj = this;
    tl2.obj = this;
    tr1.obj = this;
    tr2.obj = this;

    //s'il y a une collision avec left
    if ( this->left->Intersect(ray, tl1, tl2) ) {
        //si l'intersection n'est pas dans right
        if ( !this->right->PMC(tl1.pos) ) {
            t1 = tl1;
            t2 = tl2;
        }
        //sinon
        else {
            if ( this->right->Intersect(ray, tr1, tr2) ) {
                t1 = tr2;
                //on inverse la normale
                t1.normal = t1.normal * -1;
                //on change l'obj pour avoir la bonne couleur
                t1.obj = tl2.obj;
                t2 = tl2;
            }
        }

        return 1;
    }
    //sinon
    else {
        return 0;
    }
}

int Diff::PMC(const Vector& u) {
    return (this->left->PMC(u) && !(this->right->PMC(u)));
}
