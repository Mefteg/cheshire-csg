#include "Mesh.h"

bool Mesh::load(string filename)
{
	objLoader *objData = new objLoader();
    cout << "Loading mesh object..." <<filename<< endl;
	objData->load((char*)filename.c_str());

    // Vertice
    if ( (vertexCount = objData->vertexCount)>0)
        vertBuf = new vector<glm::vec3>(objData->vertexCount);
    for (int iVertex=0;iVertex<vertexCount;iVertex++)
    {
        vertBuf->at(iVertex).x = objData->vertexList[iVertex]->e[0];
        vertBuf->at(iVertex).y = objData->vertexList[iVertex]->e[1];
        vertBuf->at(iVertex).z = objData->vertexList[iVertex]->e[2];
    }

    // Normal
    if ( objData->normalCount>0)
        normBuf = new vector<glm::vec3>(objData->normalCount);
    for (int iNormal=0;iNormal<objData->normalCount;iNormal++)
    {
        normBuf->at(iNormal).x = objData->normalList[iNormal]->e[0];
        normBuf->at(iNormal).y = objData->normalList[iNormal]->e[1];
        normBuf->at(iNormal).z = objData->normalList[iNormal]->e[2];
    }

    // Texture
    if ( objData->textureCount>0)
        texBuf = new vector<glm::vec3>(objData->textureCount);
    for (int itexture=0;itexture<objData->textureCount;itexture++)
    {
        texBuf->at(itexture).x = objData->textureList[itexture]->e[0];
        texBuf->at(itexture).y = objData->textureList[itexture]->e[1];
        texBuf->at(itexture).z = objData->textureList[itexture]->e[2];
    }

    // Triangles
    if ( (triangleQuantity=objData->faceCount)>0)
        triBuf = new vector<glm::gtc::type_precision::u16vec3>(objData->faceCount);
    for (int iFace=0;iFace<objData->faceCount;iFace++)
    {
        triBuf->at(iFace).x = objData->faceList[iFace]->vertex_index[0];
        triBuf->at(iFace).y = objData->faceList[iFace]->vertex_index[1];
        triBuf->at(iFace).z = objData->faceList[iFace]->vertex_index[2];
    }

    cout << "Ok" << endl;
    return true;
}


bool Mesh::calculIntersection(const Rayon & ray,Intersection &I){
    for(int i=0;i<faces.size();i++){
        if(faces[i]->calculIntersection(ray,I)){
            return true;
        }
    }
    return false;
}

void Mesh::translate(glm::vec3 transVect){
    for(int i=0;i<faces.size();i++){
        faces[i]->translate(transVect);
    }
}

void Mesh::scale(glm::vec3 scaleVect){
    for(int i=0;i<faces.size();i++){
        faces[i]->scale(scaleVect);
    }
}


