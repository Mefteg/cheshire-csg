#include "Plane.h"
#include "rayon.hpp"


bool Plane::calculIntersection(const Rayon & ray,Intersection &I){

    float Vd = glm::dot(N,ray.Vect());
    if(Vd<0){
        float V0 = -1*(glm::dot(N,ray.Orig()) + D);
        float t = V0/Vd;
        if(t>0){
            I.dist =  (A*ray.Orig().x+B*ray.Orig().y+C*ray.Orig().z+D)/(sqrt(A*A+B*B+C*C));
            I.normal = this->N;
            I.Objet = this;
            return true;
        }
    }
    return false;

};
