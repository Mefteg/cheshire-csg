/**
 * \file opbin.h
 * \brief class OpBin header
 * \author Gimenez Tom, Roumier Vincent, Matéo Camille
 * \version 1.0
 * \date 01 octobre 2011
 *
 * OpBin is a operand with two primitives
 *
 */


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
