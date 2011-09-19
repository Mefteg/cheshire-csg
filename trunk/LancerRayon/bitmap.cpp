#include <stdio.h>
#include <stdlib.h>
#include "bitmap.hpp"

void Image::Map(int i, const glm::vec3 & c) {
	glm::vec3 cc; // La couleur corrigee par bornage dans un intervalle [0,1]
	S_RVB rvb;

	cc = c;
	cc = glm::clamp(cc,0, 1);
	cc *= 255;

	rvb.r = (byte) cc.x;
	rvb.v = (byte) cc.y;
	rvb.b = (byte) cc.z;

	map[i] = rvb;
}

void Image::Map(int x, int y, const glm::vec3 & c) {
	Map((y * largeur) + x, c);
}

struct S_BMP_Header {
	word Dummy; // On est oblige de tenir compte de ce Word excessif car de toutes manieres le compilateur en cree un
	word signature; // =0x4D42
	dword taille_fichier; // Taille du fichier
	word reserv_1; // =0
	word reserv_2; // =0
	dword decalage; // Nb d'octets avant les donnees bitmap
	dword taille_chunk; // Taille du descriptif d'image (=40)
	dword largeur; // Largeur de l'image
	dword hauteur; // Hauteur de l'image
	word nb_plans; // Nombre de plans (=1)
	word nb_bits; // Nombre de bits par pixel (=24)
	dword compression; // Utilisation d'une compression (=0)
	dword taille_X;
	dword XPM;
	dword YPM;
	dword Nb_Clr;
	dword Clr_Imprt;
};

void Image::Enregistrer(char * nom) const {
	//Sauver_image_BMP(nom, largeur, hauteur, map);
	FILE * fichier; // Handle du fichier
	S_BMP_Header * header; // Header du fichier BMP
	int y; // Nombre de lignes traitees
	int x; // Nombre de pixels traites sur la ligne courante
	S_RVB * ligne; // Pointeur sur le debut de la ligne en cours de traitement dans le bitmap
	S_RVB * buffer; // Buffer contenant la version correctement codee des couleurs de la ligne

	fichier = fopen(nom, "wb");
	if (!fichier) {
		fprintf(stderr, "Impossible de sauver l'image %s\n", nom);
		exit(1);
	}

	header = (S_BMP_Header *) malloc(sizeof(S_BMP_Header));
	header->signature = 0x4D42;
	header->taille_fichier = largeur * hauteur * sizeof(S_RVB) * sizeof(header);
	header->reserv_1 = 0;
	header->reserv_2 = 0;
	header->decalage = 54;
	header->taille_chunk = 40;
	header->largeur = largeur;
	header->hauteur = hauteur;
	header->nb_plans = 1;
	header->nb_bits = 24;
	header->compression = 0;
	header->taille_X = 0;
	header->XPM = 0;
	header->YPM = 0;
	header->Nb_Clr = 0;
	header->Clr_Imprt = 0;

	fwrite(((byte *) header) + 2, 54, 1, fichier);
	free(header);

	buffer = (S_RVB *) malloc(sizeof(S_RVB) * largeur);

	for (y = 0, ligne = map + ((hauteur - 1) * largeur); y < hauteur; y++, ligne -= largeur) {
		for (x = 0; x < largeur; x++) {
			buffer[x].r = ligne[x].b;
			buffer[x].v = ligne[x].v;
			buffer[x].b = ligne[x].r;
		}

		fwrite(buffer, sizeof(S_RVB), largeur, fichier);
	}

	free(buffer);

	fclose(fichier);
}

