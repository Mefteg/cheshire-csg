#ifndef TRIANGLE_H_INCLUDED
#define TRIANGLE_H_INCLUDED

#include "Plane.h"
#include "rayon.hpp"

using namespace std;

class Triangle : public Plane{

    public:

        Triangle(glm::vec3 p1,glm::vec3 p2,glm::vec3 p3, Material *m):Plane(p1,p2,p3,m){
        };

        bool calculIntersection(const Rayon & ray,Intersection &I){
            glm::vec3 dir,wo;
            float r,a,b;

            glm::vec3 u = p2-p1;
            glm::vec3 v = p3-p1;
            glm::vec3 n = glm::cross(u,v);
            //si triangle plat
            if(n==glm::vec3(0.0,0.0,0.0))
                return false;

            ///intersection avec le plan
            wo = ray.Orig() - p1;
            a = - glm::dot(n,wo);
            if(a == 0 )
                return false;
            b = glm::dot(n,ray.Vect());
            if(abs(b)< 0.0000001)
                return false;

            r = a/b;
            if(r<0.0)
                return false;
            glm::vec3 inter = ray.Orig() + r * ray.Vect();

            ///intersection dans le triangle?
            float uu,uv,vv,wu,wv,soso;
            uu = glm::dot(u,u);
            uv = glm::dot(u,v);
            vv = glm::dot(v,v);
            glm::vec3 w = inter - p1;
            wu = glm::dot(w,u);
            wv = glm::dot(w,v);

            soso = uv*uv - uu*vv;

            float s, t;
            s = (uv * wv - vv * wu) / soso;
            if (s < 0.0 || s > 1.0)        // I is outside T
                return false;
            t = (uv * wu - uu * wv) / soso;
            if (t < 0.0 || (s + t) > 1.0)  // I is outside T
                return false;

            I.dist =  r;
            I.normal = this->N;
            I.Objet = this;
            return true;
        };

        void translate(glm::vec3 transVect){
            p1.x += transVect.x; p1.y += transVect.y;p1.z += transVect.z;
            p2.x += transVect.x; p2.y += transVect.y;p2.z += transVect.z;
            p3.x += transVect.x; p3.y += transVect.y;p3.z += transVect.z;
        };

        void scale(glm::vec3 scaleVect){
            p1.x *= scaleVect.x; p1.y *= scaleVect.y;p1.z *= scaleVect.z;
            p2.x *= scaleVect.x; p2.y *= scaleVect.y;p2.z *= scaleVect.z;
            p3.x *= scaleVect.x; p3.y *= scaleVect.y;p3.z *= scaleVect.z;
        };

};


#endif // TRIANGLE_H_INCLUDED
