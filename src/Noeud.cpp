#include "Noeud.h"

Noeud::Noeud(Situation* situation, int nbIteration, Noeud* parent) {
	this->situation = situation;
	this->nbIteration = nbIteration + 1;
	this->parent = parent;
}

Noeud::~Noeud() {
	delete this->situation;
}

bool Noeud::operator<(const Noeud& n) const {
	return this->nbIteration < n.nbIteration;
}

bool Noeud::operator>(const Noeud& n) const {
	return this->nbIteration > n.nbIteration;
}


Situation* Noeud::getSituation() const {
	return this->situation;
}

int Noeud::getNbIteration() const {
	return this->nbIteration;
}

Noeud* Noeud::getParent() const {
    return this->parent;
}

std::ostream& operator<<(std::ostream& stream, Noeud& noeud) {
	stream << noeud.situation;
	return stream;
}

std::ostream& operator<<(std::ostream& stream, Noeud*& noeud) {
    stream << noeud->situation;
    return stream;
}