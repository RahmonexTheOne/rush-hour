#ifndef RUSH_HOUR_ETU_SITUATION_H
#define RUSH_HOUR_ETU_SITUATION_H

#include <iostream>
#include <string>
#include <vector>
#include "Voiture.h"

class Situation {

private:
	std::vector<Voiture> voitures;
    bool** genereTableauCasesLibres() const; // Retourne un tableau de booléen indiquant si une case est libre ou non

	static const int SIZE;

public:
    static Coordonnees sortie;
    static Situation* generate_board_from_file(const std::string& file);

	Situation(std::vector<Voiture>&);
	Situation(std::vector<Voiture>&, Coordonnees sortie);

	std::vector<Situation*> genereSituations() const; // Génère les Situations descendantes possible depuis la Situation actuelle
	bool victoire() const;

	friend bool operator==(const Situation &s1, const Situation &s2);
	friend std::ostream& operator<<(std::ostream& stream, Situation*& situation);
};


#endif //RUSH_HOUR_ETU_SITUATION_H
