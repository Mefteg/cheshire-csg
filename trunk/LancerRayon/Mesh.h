#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include "Objet3D.hpp"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Triangle.h"
#include <iostream>
#include "objLoader\objLoader.h"

using namespace std;

struct Face{
    int s1,s2,s3;
};


class Mesh : public Objet3D{
    public:
        Mesh(string filename,Material * m){
            mat = *m;
            load(filename);
            cout<<vertBuf->at(triBuf->at(0).x).z;
            for(int i=0;i<triBuf->size();i++){
                faces.push_back(new Triangle(vertBuf->at(triBuf->at(i).x),
                                         vertBuf->at(triBuf->at(i).y),
                                         vertBuf->at(triBuf->at(i).z),
                                         m) );
            }
        };

        bool load(string filename);
        bool calculIntersection(const Rayon & ray,Intersection &I);
        void translate(glm::vec3);
        void scale(glm::vec3);

        vector<Triangle*> faces;

        vector<glm::vec3> * vertBuf;
        vector<glm::vec3> * normBuf;
        vector<glm::vec3> * texBuf;
        vector<glm::gtc::type_precision::u16vec3> * triBuf;

        int vertexCount;
        int triangleQuantity;

};


#endif // MESH_H_INCLUDED
