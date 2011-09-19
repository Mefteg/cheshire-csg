

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <iostream>
#include "Frame.h"
#include "Material.h"
#include "Intersection.hpp"
#include ".\glm-0.9.0\glm\setup.hpp"
#include ".\glm-0.9.0\glm\glm.hpp"
#include ".\glm-0.9.0\glm\ext.hpp"

class Rayon;
class Objet3D
{
 protected:
	 Frame frame;

 public:

	 Objet3D(){};

	 virtual bool calculIntersection(const Rayon & ,Intersection &I){return false;};
	 void setMat(Material * m){mat=*m;};

	 Material mat;
};


#endif
