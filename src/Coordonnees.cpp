#include "Coordonnees.h"

Coordonnees::Coordonnees(int x, int y) {
	this->x = x;
	this->y = y;
}

bool operator==(const Coordonnees &a, const Coordonnees &b) {
	return (a.x == b.x && a.y == b.y);
}

bool operator!=(const Coordonnees &a, const Coordonnees &b) {
	return !(a == b);
}