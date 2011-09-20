#ifndef __OpBin__
#define __OpBin__

#include "node.h"

class OpBin : public Node
{
protected:
	Node * left, right;
public:
	OpBin(void);
	~OpBin(void);
};

#endif
