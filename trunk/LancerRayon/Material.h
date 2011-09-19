#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

class Material{

    public :
        Material(){};
        Material(glm::vec3 coeffs,glm::vec3 colours[3],float alpha, float reflect,float transparence,float n){
            this->coeffs = coeffs;
            Ca = colours[0];
            Cd = colours[1];
            Cs = colours[2];
            this->alpha=alpha;
            this->reflect = reflect;
            this->n = n;
            this->transparence = transparence;
        };

        glm::vec3 coeffs;

        glm::vec3 Ca;
        glm::vec3 Cd;
        glm::vec3 Cs;

        float alpha;

        //puissance de reflexion
        float reflect;

        //indice du materiau
        float n;
        //transparence
        float transparence;
};

#endif // MATERIAL_H_INCLUDED
