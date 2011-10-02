/**
 * \file opbin.h
 * \brief class OpBin header
 * \author Gimenez Tom, Roumier Vincent, Matéo Camille
 * \version 1.0
 * \date 01 octobre 2011
 *
 * Containing OpBin class
 *
 */


#ifndef __OpBin__
#define __OpBin__

#include "node.h"

/*! 
 * \class OpBin
 * \brief OpBin class
 * 
 * OpBin is a operand with two primitives
 * 
 */
class OpBin : public Node
{
	protected:
	  
	Node * left; /*!< Left element of the operation */
	Node * right; /*!< Right element of the operation */
	
	public:
	  
	OpBin(void);
	OpBin(Node*, Node*);
	~OpBin(void);
};

#endif
