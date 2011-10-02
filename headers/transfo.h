/**
 * \file transfo.h
 * \brief class Transfo header
 * \author Gimenez Tom, Roumier Vincent, Matéo Camille
 * \version 1.0
 * \date 01 octobre 2011
 *
 * Containing Transfo class
 *
 */


#ifndef __TRANSFO__
#define __TRANSFO__

#include "node.h"
#include "Matrix4D.h"

/*! 
 * \class Transfo
 * \brief Transfo class
 * 
 * Transfo is a kind of node
 * 
 */
class Transfo : public Node
{
	protected:
	  
	Node* left;
	Node* right;
	Matrix4Df m, mInv;
	
	public:
	  
	Transfo(void) {};
	Transfo(Node*l) { m.SetIdentity(); left = l; };
	~Transfo(void) {};
};

#endif
