#include "Scene.hpp"



Scene::Scene()
{
}
Scene::~Scene()
{

}

void Scene::ajouterObjet(Objet3D *o)
{
	listObjets.push_back(o);
}

void Scene::ajouterLum(Light *l)
{
	listLights.push_back(l);
}
