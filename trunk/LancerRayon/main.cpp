#include <stdio.h>
#include <iostream>
#include "camera.hpp"
#include "pixelmap.hpp"
#include "rayon.hpp"
#include "objet3D.hpp"
#include "Sphere.h"
#include "Plane.h"
#include "Light.h"
#include "Material.h"
#include "Triangle.h"
#include "Mesh.h"
#include "CSG.h"

int main(void) {
    //couleurs
    glm::vec3 BLACK = glm::vec3(0.0,0.0,0.0);
    glm::vec3 WHITE = glm::vec3(1.0,1.0,1.0);
    glm::vec3 RED = glm::vec3(1.0,0.0,0.0);
    glm::vec3 GREEN = glm::vec3(0.0,1.0,0.0);
    glm::vec3 BLUE = glm::vec3(0.0,0.0,1.0);
    glm::vec3 CYAN = glm::vec3(0.0,1.0,1.0);
    glm::vec3 MAJENTA = glm::vec3(1.0,0.0,1.0);
    glm::vec3 YELLOW = glm::vec3(1.0,1.0,0.0);
    glm::vec3 noir[3] = {BLACK,BLACK,WHITE};
    glm::vec3 blanc[3] = {WHITE,WHITE,WHITE};
    glm::vec3 rouge[3] = {RED,RED,WHITE};
    glm::vec3 vert[3] = {GREEN,GREEN,WHITE};
    glm::vec3 bleu[3] = {BLUE,BLUE,WHITE};
    glm::vec3 cyan[3] = {CYAN,CYAN,WHITE};
    glm::vec3 majenta[3] = {MAJENTA,MAJENTA,WHITE};
    glm::vec3 jaune[3] = {YELLOW,YELLOW,WHITE};

	// Une image Pixelmap
	Pixelmap pixmap(800, 600);
	//Pixelmap pixmap(400, 300);
	// Une image Bitmap
	Image bitmap;

	Scene scene;

	//Materiaux
	glm::vec3 coeffs1 = glm::vec3(0.5,0.7,0.1);
    glm::vec3 colours1[3] = {WHITE,WHITE,WHITE};
	Material * mat1 = new Material(coeffs1,colours1,500,0.1f,0.76f,1.00f); //transparent
	glm::vec3 coeffs2 = glm::vec3(0.1,0.9,1.0);
	Material * mat2 = new Material(coeffs2,rouge,200,0.0f,0.0f,1.33f);
	glm::vec3 coeffs3 = glm::vec3(0.1,0.9,0.2);
	Material * mat3 = new Material(coeffs3,vert,100,0.97f,0.0f,0.0f);
	glm::vec3 coeffs4 = glm::vec3(0.1,0.9,0.2);
	Material * mat4 = new Material(coeffs4,jaune,58,0.0f,0.0f,0.0f);
	glm::vec3 coeffs5 = glm::vec3(0.1,0.5,0.5);
	Material * mat5 = new Material(coeffs5,bleu,109,0.8f,0.0f,1.66f);
	glm::vec3 coeffs6 = glm::vec3(0.1,0.9,0.2);
	Material * mat6 = new Material(coeffs6,majenta,1,0.0f,0.0f,0.0f);
	glm::vec3 coeffs7 = glm::vec3(0.1,0.9,0.2);
	Material * mat7 = new Material(coeffs7,noir,160,0.0f,0.0f,0.0f);

	// Initialisation des objets==============================
    scene.ajouterObjet( new Sphere(glm::vec3(5.0,2.2,11.0),1.6,mat5 ) );
    scene.ajouterObjet( new Sphere(glm::vec3(-4.0,0.3,22.0),3.0,mat2) );
    scene.ajouterObjet( new Sphere(glm::vec3(-4.0,5.0,12.0),2.1,mat3) );
    scene.ajouterObjet( new Sphere(glm::vec3(-2.4,2.0,43.0),2.0,mat6) );

    /*Sphere *bouleRouge = new Sphere(glm::vec3(0.0,2.0,18.0),2.0,mat2) ;        //sphere rouge
    Sphere *bouleVerte =  new Sphere(glm::vec3(1.0,2.0,16.0),1.1,mat3) ;         //sphere verte
    scene.ajouterObjet(new CSG(bouleRouge, bouleVerte, 'd')); //difference*/

    Mesh * m = new Mesh("pyramid.obj",mat1);
    m->translate(glm::vec3(-1.3, -0.6, 10.0));
    scene.ajouterObjet( m );
    //PLAN
    /*scene.ajouterObjet( new Plane(glm::vec3(3,1.0,60.0),
                                  glm::vec3(0.6,2.0,60.0),
                                  glm::vec3(1.0,-1.0,60.0),
                                  mat2) );*/
    //Triangle
    scene.ajouterObjet( new Triangle(glm::vec3(200,-100.0,60.0),
                                     glm::vec3(100,100,60),
                                     glm::vec3(-300,50.0,60),
                                     mat3) );

    scene.ajouterLum(new Light(glm::vec3(4.0,0.0,-30.0)));

	// Ajouter les objets à la scene

	// la Camera
	Camera cam;
	cam.initAA(1,20);//anitaliasing
	cam.Centre(glm::vec3(0, 1, 0));
	cam.Dir(glm::vec3(0, 0, 1));
	cam.Haut(glm::vec3(0, 1, 0));
	cam.Largeur((5.6 * 513) / 384);
	cam.Hauteur(5.6);

	cam.Calculer_image(pixmap, scene, 3 );

	pixmap.Transferer(bitmap);
	bitmap.Enregistrer("image.bmp");

	return 0;
}
