#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED


#include ".\glm-0.9.0\glm\setup.hpp"
#include ".\glm-0.9.0\glm\glm.hpp"
#include ".\glm-0.9.0\glm\ext.hpp"

class Light{

    public:
        Light(glm::vec3 pos){
            this->pos = pos;
        };
        glm::vec3 pos;

};


#endif // LIGHT_H_INCLUDED
