/*
 *	(c) XLim, UMR-CNRS
 *	Authors: G.Gilet
 *
 */

#ifndef __FRAME__
#define __FRAME__


#include ".\glm-0.9.0\glm\setup.hpp"
#include ".\glm-0.9.0\glm\glm.hpp"
#include ".\glm-0.9.0\glm\ext.hpp"


class Frame
{
public:
	Frame();
	~Frame();

	// Charge la matrice identit�
	void loadIdentity();

	// Charge une matrice arbitraire
	void setUpFromMatrix(glm::mat4 m);

	//R�cup�re la matrice
	glm::mat4* getMatrix(){return(&matrix);};

	// R�cup�re la matrice compl�te des transformations
	glm::mat4 getTransformMatrix();

	void setReferenceFrame(Frame *f);
	/*
	*
	* Transformations g�ometriques
	*
	*/

	// Rotation autour d'un vecteur
	void rotate(glm::vec3 axis, float angle);
	// Translation par un vecteur
	void translate(glm::vec3 V);
	// Changement d'echelle
	void scale(glm::vec3 size);




private:
	glm::mat4 matrix;
	Frame *reference;

};








#endif
