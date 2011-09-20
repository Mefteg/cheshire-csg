#ifndef __OpBin__
#define __OpBin__

#include "node.h"

class OpBin : public Node
{
protected:
	Node * left;
	Node * right;
public:
	OpBin(void);
	OpBin(Node*, Node*);
	~OpBin(void);
};

#endif
