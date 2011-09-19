#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED
#include <iostream>
#include "Objet3D.hpp"

class Sphere : public Objet3D{

    public :
        Sphere(glm::vec3 c,float r){
            center = c;
            radius = r;
        };
        Sphere(glm::vec3 c,float r,Material * m){
            center = c;
            radius = r;
            setMat(m);
        };
        bool calculIntersection(const Rayon & ,Intersection &I);

        float radius;
        glm::vec3 center;

};


#endif // SPHERE_H_INCLUDED
