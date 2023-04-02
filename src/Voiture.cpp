#include "Voiture.h"

Voiture::Voiture(int x, int y, int taille, bool horizontal) : coord(Coordonnees(x, y)) {
	this->taille = taille;
	this->horizontal = horizontal;
}

Coordonnees Voiture::get_coord() const {
	return this->coord;
}

int Voiture::get_taille() const {
	return this->taille;
}

bool Voiture::is_horizontal() const {
	return this->horizontal;
}

void Voiture::set_coordonnes(int x, int y) {
	this->coord = Coordonnees(x, y);
}


std::ostream& operator<<(std::ostream& stream, Voiture& voiture) {
	stream << voiture.coord.x << " " << voiture.coord.y << " " << voiture.taille << " " << (int) voiture.horizontal;
	return stream;
}