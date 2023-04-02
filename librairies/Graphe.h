#ifndef RUSH_HOUR_ETU_GRAPHE_H
#define RUSH_HOUR_ETU_GRAPHE_H

#include "Noeud.h"
#include <vector>
#include <queue>
#include <functional>

class Graphe {

private:
	Noeud* source;
	std::vector<Noeud*> allNoeuds;
	
	// On change la manière de comparaison pour faire en sorte que les Noeuds possédant le plus petit nbIteration soit les plus prioritaires
	std::queue<Noeud*> liste;

public:
	Graphe(const std::string& file);
	~Graphe();
	Noeud* genereEtParcours(); // Retourne un pointeur sur le Noeud de fin du parcours

	static std::vector<Noeud*> getChemin(Noeud* arrivee); // Retourne un std::vector contenant le chemin depuis l'arrivée jusqu'au début
};


#endif //RUSH_HOUR_ETU_GRAPHE_H
