#ifndef __TRANSFO__
#define __TRANSFO__

#include "node.h"
#include "Matrix4D.h"

class Transfo : public Node
{
protected:
	Node * left;
	Node * right;
	Matrix4Df m;
public:
	Transfo(void){};
	Transfo(Node*l){m.SetIdentity();left = l;};
	~Transfo(void){};
};

#endif
