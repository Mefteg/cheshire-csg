#include "Sphere.h"
#include "Rayon.hpp"

bool Sphere::calculIntersection(const Rayon & ray,Intersection &I){

    float B =  2 * (ray.Vect().x * (ray.Orig().x - center.x) + ray.Vect().y * (ray.Orig().y - center.y) + ray.Vect().z * (ray.Orig().z- center.z));

    float C = pow(ray.Orig().x - center.x,2) + pow(ray.Orig().y - center.y,2) + pow(ray.Orig().z - center.z,2) - radius*radius;

    //calcul du discriminant
    float t;
    float delta = B*B - 4*C;
    if(delta>=0){
        t = (-1*B - sqrt(delta))/2 ;
        // si racine 1 négative
        if(t<0)
            t = (-1*B + sqrt(delta))/2;//racine 2
        //changer la distance du point d'intersection à la caméra
        if(t>0){
            I.dist = t;
            //calcul de la normale
            glm::vec3 interPt = glm::vec3((ray.Orig().x + t*ray.Vect().x) , (ray.Orig().y + t*ray.Vect().y), (ray.Orig().z + t*ray.Vect().z));
            I.normal = (interPt-center);
            I.normal = glm::normalize(I.normal);
            I.Objet =  this;
            return true;
        }
    }
    return false;
}

