#ifndef RUSH_HOUR_ETU_NOEUD_H
#define RUSH_HOUR_ETU_NOEUD_H

#include "Situation.h"
#include <vector>

class Noeud {

private:
	Situation* situation;
	int nbIteration;
	std::vector<Noeud*> voisins;
	Noeud* parent;

public:
	Noeud(Situation* situation, int nbIteration = -1, Noeud* parent = nullptr);
	~Noeud();

	Situation* getSituation() const;
    int getNbIteration() const;
    Noeud* getParent() const;

	bool operator<(const Noeud& n) const;
	bool operator>(const Noeud& n) const;

    friend std::ostream& operator<<(std::ostream& stream, Noeud& noeud);
    friend std::ostream& operator<<(std::ostream& stream, Noeud*& noeud);
};


#endif //RUSH_HOUR_ETU_NOEUD_H
