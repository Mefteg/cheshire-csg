#include <math.h>
#include "pixelmap.hpp"
#include "bitmap.hpp"

void Pixelmap::Correction(float g) {
	int taille; // Nombre de pixels a traiter
	int index; // Indice du pixel traite
	glm::vec3 * cour; // Pixel en cours d'etude

	// Puis on cherche la valeur maximale de la pixelmap
	taille = largeur * hauteur;
	for (index = 0, cour = map; index < taille; index++, cour++) {
		(*cour).x = (pow((*cour).x, (1 / g)));
		(*cour).y = (pow((*cour).y, (1 / g)));
		(*cour).z = (pow((*cour).z, (1 / g)));
	}
}

void Pixelmap::Normaliser() {
	int taille; // Nombre de pixels a traiter
	int index; // Indice du pixel traite
	glm::vec3 * cour; // Pixel en cours d'etude
	float max; // Intensite maximale des composantes des pixels formant la pixelmap

	// On cherche la valeur maximale de la pixelmap
	taille = largeur * hauteur;
	max = map[0].x;
	for (index = 0, cour = map; index < taille; index++, cour++) {
		if (max < (*cour).x)
			max = (*cour).x;
		if (max < (*cour).y)
			max = (*cour).y;
		if (max < (*cour).z)
			max = (*cour).z;
	}

	// Et enfin on fait le transfert a l'aide de couleurs normalisees
	if (max != 0)
		max = 1 / max;
	for (index = 0, cour = map; index < taille; index++, cour++)
		(*cour) *= max;
}

void Pixelmap::Transferer(Image & b) const {
	int taille; // Nombre de pixels a traiter
	int index; // Indice du pixel traite
	glm::vec3 * cour; // Pixel en cours d'etude

	// On commence par redimmensionner le bitmap a la taille de la pixelmap
	b.Redimensionner(largeur, hauteur);

	// Et on fait le transfert de tous les pixels
	taille = largeur * hauteur;
	for (index = 0, cour = map; index < taille; index++, cour++)
		b.Map(index, (*cour));
}
