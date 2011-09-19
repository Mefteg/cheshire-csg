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

	// Charge la matrice identité
	void loadIdentity();

	// Charge une matrice arbitraire
	void setUpFromMatrix(glm::mat4 m);

	//Récupère la matrice
	glm::mat4* getMatrix(){return(&matrix);};

	// Récupère la matrice complète des transformations
	glm::mat4 getTransformMatrix();

	void setReferenceFrame(Frame *f);
	/*
	*
	* Transformations géometriques
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
