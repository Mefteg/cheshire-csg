#ifndef PLANE_H_INCLUDED
#define PLANE_H_INCLUDED

#include "Objet3D.hpp"

class Plane :public  Objet3D
{

    public :
        Plane(){};
        Plane(glm::vec3 p1,glm::vec3 p2,glm::vec3 p3, Material *m){
            this->p1 = p1;
            this->p2 = p2;
            this->p3 = p3;
            setMat(m);

            //normale au plan
            A= p1.y *(p3.z -p2.z)+ p2.y*(p1.z-p3.z) + p3.y*(p2.z-p1.z);
            B= p1.z *(p3.x -p2.x)+ p2.z*(p1.x-p3.x) + p3.z*(p2.x-p1.x);
            C= p1.x *(p3.y -p2.y)+ p2.x*(p1.y-p3.y) + p3.x*(p2.y-p1.y);
            D = (-1)*p1.x*(p3.y*p2.z - p2.y*p3.z)- p2.x*(p1.y*p3.z - p3.y*p1.z )- p3.x*( p2.y*p1.z - p1.y*p2.z);

            N = glm::vec3(A,B,C);
            N=glm::normalize(N);

        };
        bool calculIntersection(const Rayon & ,Intersection &I);

        glm::vec3 p1,p2,p3;
        float A,B,C,D;
        glm::vec3 N;
};


#endif // PLANE_H_INCLUDED
