#ifndef PIXELMAP_HPP
#define PIXELMAP_HPP

#include "bitmap.hpp"

////////////////////////////////////////////////////////////////// C_PIXELMAP

class Pixelmap {
protected:

	int largeur; // Largeur de l'image
	int hauteur; // Hauteur de l'image
	glm::vec3 * map; // Ensemble des couleurs contenues dans l'image

public:

	// Constructeur
	Pixelmap(int l = 320, int h = 200) {
		largeur = l;
		hauteur = h;
		map = new glm::vec3[largeur * hauteur];
	}
	~Pixelmap() {
		delete[] map;
	}

	// Lecture
	int Largeur() const {
		return largeur;
	}
	int Hauteur() const {
		return hauteur;
	}
	glm::vec3 Map(int i) const {
		return map[i];
	} // ATTENTION!!! : 0 <= i < largeur*hauteur
	glm::vec3 Map(int x, int y) const {
		return map[(y * largeur) + x];
	} // ATTENTION!!! : (0,0) <= (x,y) < (largeur,hauteur)

	// Ecriture
	void Map(int i, const glm::vec3 & c) {
		map[i] = c;
	} // ATTENTION!!! : 0 <= i < largeur*hauteur
	void Map(int x, int y, const glm::vec3 & c) {
		map[(y * largeur) + x] = c;
	} // ATTENTION!!! : (0,0) <= (x,y) < (largeur,hauteur)

	// Methodes
	void Correction(float); // Correction Gamma
	void Normaliser(); // Normalisation de l'image
	void Transferer(Image &) const; // Transfert vers un bitmap
};

#endif

