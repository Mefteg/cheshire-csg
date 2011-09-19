/*
 *	(c) XLim, UMR-CNRS
 *	Authors: G.Gilet
 *
 */

#include "Frame.h"
#include <iostream>
Frame::Frame()
{
	reference = NULL;
	matrix = glm::mat4(1.0f);
}

void Frame::setReferenceFrame(Frame *f)
{
	reference = f;
}
glm::mat4 Frame::getTransformMatrix()
{
	if (reference != NULL)
		return(reference->getTransformMatrix() * matrix);
	else
		return(matrix);
}

Frame::~Frame()
{
	
}

void Frame::setUpFromMatrix(glm::mat4 m)
{
	matrix = m;
}

void Frame::loadIdentity()
{
	matrix = glm::mat4(1.0f);
}

// Transformations géometriques

void Frame::rotate(glm::vec3 axis, float angle)
{
	matrix = glm::rotate(matrix,angle,axis);
}
void Frame::translate(glm::vec3 t)
{
	matrix = glm::translate(matrix,t);
}

void Frame::scale(glm::vec3 s)
{
	matrix = glm::scale(matrix,s);
}
