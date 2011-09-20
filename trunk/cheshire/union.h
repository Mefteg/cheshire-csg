#ifndef __Union__
#define __Union__

#include "opbin.h"

class Union : public OpBin
{
public:
	Union(void);
	Union(Node*, Node*);
	~Union(void);

	int Intersect(const Ray&, double&);
};

#endif
