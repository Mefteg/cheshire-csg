#ifndef RAYON_HPP_
#define RAYON_HPP_

#include ".\glm-0.9.0\glm\setup.hpp"
#include ".\glm-0.9.0\glm\glm.hpp"
#include ".\glm-0.9.0\glm\ext.hpp"
#include "Scene.hpp"


class Rayon {
protected:

	glm::vec3 orig; // Origine du rayon
	glm::vec3 vect; // Vecteur directeur (oriente) du rayon

public:

	Rayon() {	}

	// Lecture
	glm::vec3 Orig() const {
		return orig;
	}
	glm::vec3 Vect() const {
		return vect;
	}

	// Ecriture
	void Orig(const glm::vec3 & o) {
		orig = o;
	}
	void Vect(const glm::vec3 & v) {
		vect = glm::normalize(v);
	}

	glm::vec3 Lancer(Scene &sc,int current) const;
	bool detectOcc(Scene &sc);

	float n;//indice du materiau
};

#endif /* RAYON_HPP_ */
