#ifndef SCENE_HPP
#define SCENE_HPP

#include "Objet3D.hpp"
#include "Light.h"
#include <vector>
class Scene
{
public:
	Scene();
	~Scene();
	void ajouterObjet(Objet3D *o);
	void ajouterLum(Light *l);


	// Contient les elements de la scene
	std::vector < Objet3D*> listObjets;
	//contient les lumières de la scene
	std::vector< Light* > listLights;

};


#endif
