#ifndef RUSH_HOUR_ETU_VOITURE_H
#define RUSH_HOUR_ETU_VOITURE_H

#include <iostream>
#include "Coordonnees.h"

class Voiture {

private:
	Coordonnees coord;
	int taille;
	bool horizontal;

public:
	Voiture(int x, int y, int taille, bool horizontal);
	Coordonnees get_coord() const;
	int get_taille() const;
	bool is_horizontal() const;

	void set_coordonnes(int x, int y);

	friend std::ostream& operator<<(std::ostream& stream, Voiture& voiture);
};


#endif //RUSH_HOUR_ETU_VOITURE_H
