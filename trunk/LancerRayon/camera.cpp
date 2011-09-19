#include "camera.hpp"
#include "pixelmap.hpp"
#include "rayon.hpp"
#include "Scene.hpp"
#include <stdio.h>

void Camera::Haut(const glm::vec3 & h) {

	haut = h - (dir * (dir * h));


	if (glm::length(haut) != 0.0)
		haut = glm::normalize(haut);

}

void Camera::Calculer_image(Pixelmap & pm, Scene &sc, int complexite) const {
	glm::vec3 foyer; // Foyer optique de la camera
	glm::vec3 droite; // Vecteur partant sur la droite dans le plan de l'ecran
	float dx, dy; // dimension des macro-pixels
	int x, y; // Position dans l'image du pixel en cours de calcul
	glm::vec3 hg; // Position du pixel au centre du premier macro-pixel de l'ecran (en haut a gauche)
	glm::vec3 pt; // Position de l'intersection entre le rayon a lancer et l'ecran
	int index; // Indice du pixel traite

	// On calcule la position du foyer de la camera
	foyer = centre - (dir * dist);

	//std::cout << "centre : " << haut.x << " " << haut.y <<" " << haut.z << std::endl;
	// On calcule le vecteur unitaire "droite" du plan
	droite = glm::cross(dir,haut);


	// On calcule le deltaX et le deltaY
	dx = largeur / pm.Largeur();
	dy = hauteur / pm.Hauteur();

	// On calcule la position du premier point de l'ecran que l'on calculera
	hg = centre + (droite * ((dx / 2) - (largeur / 2))) + (haut * ((hauteur / 2) - (dy / 2)));

	// Pour chaque pixel de l'image a calculer
	index = 0;
	for (y = 0; y < pm.Hauteur(); y++) {
		for (x = 0; x < pm.Largeur(); x++) {
		    // On calcule la position dans l'espace de ce point
		    pt = hg + (droite * (dx * x)) - (haut * (dy * y));
            switch(AA){
                case 1: pm.Map(index++,regularAA(AArays,sc,pt,dx,dy,foyer,complexite));
                        break;
                case 2 : pm.Map(index++,randomAA(AArays,sc,pt,dx,dy,foyer,complexite));
                        break;
                case 3 : pm.Map(index++,semiRandomAA(AArays,sc,pt,dx,dy,foyer,complexite));
                        break;
            }
		}
		//std::cout << "Ligne " << y << std::endl;
	}
}

glm::vec3 Camera::regularAA(int rays,Scene &sc,glm::vec3 pt,float dx, float dy,glm::vec3 foyer,int complexite)const{

	Rayon ray; // Rayon a lancer
	glm::vec3 vect; // Vecteur directeur du rayon a lancer

    ///traitement normal si pas d'antialiassage
    if(rays<2){
        // On prepare le rayon qui part du foyer et qui passe par ce point
            ray.Orig(pt);
            ray.n = 1.0;
            vect = pt - foyer;
            vect = glm::normalize(vect);
            ray.Vect(vect);
            return ray.Lancer(sc,complexite);
    }

    ///lancers
    glm::vec3 res;
    float r = 0.0;
    float g = 0.0;
    float b = 0.0;
    int zoubida = 0;

	//début des lancers
    for(int k =0; k<=rays;k+=rays/2){
        //on décale légèrement le point d'origine sur x
        pt.x += (k+1)*dx/rays;
        for(int l = 0; l<=rays/2;l+=rays/2){
            //on décale légèrement le point d'origine sur y
            pt.y += (l+1)*dy/rays;
            // On prepare le rayon qui part du foyer et qui passe par ce point
            ray.Orig(pt);
            ray.n = 1.0;
            vect = pt - foyer;
            vect = glm::normalize(vect);
            ray.Vect(vect);
            res = ray.Lancer(sc,complexite);
            r+=res.x;g+=res.y;b+=res.z;
            zoubida++;
        }
    }
    res.x = r/zoubida; res.y = g/zoubida; res.z=b/zoubida;
    return res;
}

glm::vec3 Camera::randomAA(int rays,Scene &sc,glm::vec3 pt,float dx, float dy,glm::vec3 foyer,int complexite)const{

	Rayon ray; // Rayon a lancer
	glm::vec3 vect; // Vecteur directeur du rayon a lancer

    ///lancers
    glm::vec3 res;
    float r = 0.0;
    float g = 0.0;
    float b = 0.0;

	//début des lancers
    for(int k =0; k<=rays;k++){
        int a = rand()% rays-1;
        //on décale légèrement le point d'origine sur x
        pt.x += a*dx/rays;
        //on décale légèrement le point d'origine sur y
        pt.y += a*dy/rays;
        // On prepare le rayon qui part du foyer et qui passe par ce point
        ray.Orig(pt);
        ray.n = 1.0;
        vect = pt - foyer;
        vect = glm::normalize(vect);
        ray.Vect(vect);
        res = ray.Lancer(sc,complexite);
        r+=res.x;g+=res.y;b+=res.z;
    }

    res.x = r/rays; res.y = g/rays; res.z=b/rays;
    return res;
}

glm::vec3 Camera::semiRandomAA(int rays,Scene &sc,glm::vec3 pt,float dx, float dy,glm::vec3 foyer,int complexite)const{

	Rayon ray; // Rayon a lancer
	glm::vec3 vect; // Vecteur directeur du rayon a lancer

    ///traitement normal si pas d'antialiassage
    if(rays<2){
        // On prepare le rayon qui part du foyer et qui passe par ce point
            ray.Orig(pt);
            ray.n = 1.0;
            vect = pt - foyer;
            vect = glm::normalize(vect);
            ray.Vect(vect);
            return ray.Lancer(sc,complexite);
    }

    ///lancers
    glm::vec3 res;
    float r = 0.0;
    float g = 0.0;
    float b = 0.0;

    int rayons =0;
	//début des lancers
    for(int k =0; k<=rays/2;k+=rays/2){
        //on décale légèrement le point d'origine sur x
        pt.x += (k+1)*dx/rays;
        for(int l = 0; l<=rays/2;l+=rays/2){
            //on décale légèrement le point d'origine sur y
            pt.y += (l+1)*dy/rays;

            //replacer aléatoirement l'oirgine du rayon aux environs
            pt.x += rand()% (k+1)*dx/rays;
            pt.y += rand()% (l+1)*dy/rays;
            // On prepare le rayon qui part du foyer et qui passe par ce point
            ray.Orig(pt);
            ray.n = 1.0;
            vect = pt - foyer;
            vect = glm::normalize(vect);
            ray.Vect(vect);
            res = ray.Lancer(sc,complexite);
            r+=res.x;g+=res.y;b+=res.z;
            rayons++;
        }
    }
    res.x = r/rayons; res.y = g/rayons; res.z=b/rayons;
    return res;
}

