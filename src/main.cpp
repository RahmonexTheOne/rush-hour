#include <iostream>
#include <vector>

#include "Graphe.h"

int main(int argc, char** argv) {

	if(argc == 1) {
		std::cerr << "Veillez renseigner un fichier, exemple : ./rush-hour puzzle.txt" << std::endl;
		exit(EXIT_FAILURE);
	} else {
		Graphe g(argv[1]);
		std::vector<Noeud*> chemin = Graphe::getChemin(g.genereEtParcours());

		for(int i = chemin.size() - 1; i >= 0; i--) {
			std::cout << "Situation n° " << chemin.size() - i - 1 << std::endl;
			std::cout << chemin[i] << "\n" << std::endl;
		}	
	}
	
	return 0;
}
