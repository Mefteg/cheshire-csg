#include "rayon.hpp"
#include "objet3D.hpp"
#include <iostream>
// --------------------------------------------------------------------------
//
// Methodes (et operations) sur les rayons
//
// --------------------------------------------------------------------------


glm::vec3 Rayon::Lancer(Scene &sc, int recur) const {
    ///DECLARATIONS
	glm::vec3 res; // Couleur resultante
	bool reverse = false;
	// Au depart, le point au bout du rayon est noir
	res = glm::vec3(0, 0, 0);
	if(recur ==0)
        return res;
	//intersection la plus près
	Intersection * interMin = new Intersection() ;
	//rayon pour la détection d'occlusion
	Rayon shadowRay;
	//rayon pour la réflexion
	Rayon reflectRay;
	//rayon pour la réfraction
	Rayon refractRay;

    //iterateur sur les objets de la scène
    std::vector < Objet3D*>::iterator it = sc.listObjets.begin();

	// Calcul des intersections du rayon avec la scène
    while( it != sc.listObjets.end() ){
        Intersection inter;
        // Traiter l'intersection la plus proche de l'origine
        if((*it)->calculIntersection(*this,inter)){
            //si la nouvelle intersection est plus grande ou interMin pas encore initialisée
            if( (*interMin>inter) || (interMin->Objet ==NULL) )
                *interMin = inter;
        }
        it++;
    }

    //si il y au moins une intersection
    if(interMin->Objet!=NULL){
        //lumière
        Light l = *(sc.listLights.front());
        //vecteur lumière : part du point lumineux jusqu'à l'intersection
        glm::vec3 vectLumiere;
        vectLumiere = l.pos-(Orig() + Vect()*interMin->dist) ;
        vectLumiere = glm::normalize(vectLumiere);
        //rayon réfléchi
        glm::vec3 R = 2.0f * interMin->normal * glm::dot(interMin->normal,vectLumiere)-vectLumiere;

        //calcul couleur ambiante
        glm::vec3 ia;
        ia = interMin->Objet->mat.coeffs.x * interMin->Objet->mat.Ca;

        //intensités ambiante et diffuse
        glm::vec3 is = glm::vec3(0.0,0.0,0.0);
        glm::vec3 id = glm::vec3(0.0,0.0,0.0);;

        ///)))))))CALCUL D'OMBRE(((((((((((
        //regarder si un objet ne cache pas la lumière
        shadowRay.Orig(Orig() + Vect()*interMin->dist);
        shadowRay.Vect(vectLumiere);
        shadowRay.Orig(shadowRay.Orig() + shadowRay.Vect());
        //si rien n'obstrue la lumière où que l'objet est transparent
        if( ! shadowRay.detectOcc(sc) || interMin->Objet->mat.transparence>0.0){

            //calcul couleur diffuse
            float scal = glm::dot(vectLumiere, interMin->normal);
            //si produit scalaire négatif
            if(scal<=0.0){
                //si l'objet est transparent
                if(interMin->Objet->mat.transparence > 0.0){
                    //on vérifie si l'intersection est à l'intérieur d'un objet
                    scal = glm::dot(vectLumiere, -interMin->normal);
                    //si c'est le cas on inverse la normale
                    if( (glm::dot(Vect(),interMin->normal)>=0.0) && (this->n == interMin->Objet->mat.n)){
                        reverse = true;
                        interMin->normal = -interMin->normal;
                    }
                }else{
                    scal = 0.0;
                }
            }

            //calcul de la lumière diffuse
            id = interMin->Objet->mat.coeffs.y * interMin->Objet->mat.Cd * scal;
            //calcul couleur speculaire
            float produit = pow ( glm::max((float)0.0,glm::dot(R,vectLumiere)) , interMin->Objet->mat.alpha); //le mettre a une puissance donnée

            is = interMin->Objet->mat.coeffs.z * interMin->Objet->mat.Cs * produit;
        }

        //calcul de la couleur
        res = ia  + id +is  ;

        ///CALCUL DE REFLEXION
        reflectRay.Orig(Orig() + Vect()*interMin->dist);
        reflectRay.Vect(R);
        reflectRay.Orig(reflectRay.Orig()+reflectRay.Vect());
        glm::vec3 ref = reflectRay.Lancer(sc,recur-1);
        //si objet réfléchi
        if(ref!=glm::vec3(0.0,0.0,0.0))
            //faire la répartition des couleurs selon l'indice de réfraction
            res = (1.0f-interMin->Objet->mat.reflect)*res + (interMin->Objet->mat.reflect)*ref;

        ///CALCUL DE REFRACTION
        if(interMin->Objet->mat.transparence>0.0){
            refractRay.Orig(Orig() + Vect()*interMin->dist);
            //si le prochain rayon sort de l'objet
            if(this->n == interMin->Objet->mat.n){
                refractRay.n = 1.0;
            }else{

                refractRay.n = interMin->Objet->mat.n;
            }
            //calcul rayon refracté
            float eta=this->n/refractRay.n;
            float val1 = -glm::dot(interMin->normal,Vect());
            float val2 = sqrt(1.0-( ( eta*eta ) * (1.0-val1*val1) ));
            refractRay.Vect( interMin->normal *-Vect() + (eta*val1-val2)*interMin->normal);
            refractRay.Orig(refractRay.Orig()+0.0001f*refractRay.Vect());

            glm::vec3 refra = refractRay.Lancer(sc,recur-1);

            //si objet réfléchi
            res = (1.0f-interMin->Objet->mat.transparence)*res + (interMin->Objet->mat.transparence)*refra;
        }
    }


	return res;
}

bool Rayon::detectOcc(Scene &sc){
    std::vector < Objet3D*>::iterator it = sc.listObjets.begin();
	// Calcul des intersections du rayon avec la scène
    while( it != sc.listObjets.end() ){
        Intersection inter;
        // Traiter l'intersection la plus proche de l'origine pour un objet non transparent
        if((*it)->calculIntersection(*this,inter) && ( !(*it)->mat.transparence >0.0) ){
            return true;
        }
        it++;
    }
    return false;
}
