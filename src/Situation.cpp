#include "Situation.h"

#include <fstream>
#include <string>
#include <sstream>

//Initialize the exit with rand value
Coordonnees Situation::sortie = {0, 0};

//Size of the Board
const int Situation::SIZE = 6;

//Read file and take values :
//Important (the first line need to be the exit value)
Situation* Situation::generate_board_from_file(const std::string& file) {
	std::ifstream ifs(file);
	if(!ifs.is_open()) {
		std::cerr << "Erreur lors de l'ouverture du fichier : \"" << file << "\"" << std::endl;
		exit(EXIT_FAILURE);
	}

	int x, y, taille, horizontal;
	std::vector<Voiture> voitures;

	std::string line;
	std::getline(ifs, line);
	std::istringstream is(line);
	if(!(is >> x >> y)) {
		std::cerr << "Erreur lors de la lecture de la position de la sortie" << std::endl;
		ifs.close();
		exit(EXIT_FAILURE);
	}

	Coordonnees sortie = {x, y};
	line.clear();

	while(std::getline(ifs, line)) {
		std::istringstream iss(line);
		if(!(iss >> x >> y >> taille >> horizontal)) {
			std::cerr << "Erreur lors de la lecture du fichier" << std::endl;
			ifs.close();
			exit(EXIT_FAILURE);
		}
        //Data of the cars
		voitures.push_back(Voiture(x, y, taille, (bool) horizontal));
	}

	return new Situation(voitures, sortie);
}

Situation::Situation(std::vector<Voiture>& voitures) {
	this->voitures = voitures;
}

Situation::Situation(std::vector<Voiture>& voitures, Coordonnees sortie) {
	this->voitures = voitures;
	Situation::sortie = sortie;
}


bool** Situation::genereTableauCasesLibres() const {

	// Création du tableau + initialisation des cases
	bool** tab = new bool*[Situation::SIZE];
    std::cout << std::endl;
	for(long unsigned int i = 0; i < Situation::SIZE; i++) {
		tab[i] = new bool[Situation::SIZE];
		for(int j = 0; j < Situation::SIZE; j++) {
			tab[i][j] = true;
		}
	}

	for(const Voiture &it : voitures) {
		for(int i = 0; i < it.get_taille(); i++) {
			if(it.is_horizontal()) {
				tab[it.get_coord().x][it.get_coord().y + i] = false;
			} else {
				tab[it.get_coord().x + i][it.get_coord().y] = false;
			}
		}
	}

	return tab;
}


std::vector<Situation*> Situation::genereSituations() const {
	std::vector<Situation*> newSituation;

	bool** tab = this->genereTableauCasesLibres();

	for(long unsigned int iVoiture = 0; iVoiture < voitures.size(); iVoiture++) {

		Coordonnees coordVoiture = voitures[iVoiture].get_coord();

		if(voitures[iVoiture].is_horizontal()) {

			for(int i = coordVoiture.y - 1; i >= 0; i--) {
				if(tab[coordVoiture.x][i] == false)
					break;

				std::vector<Voiture> newVoiture = voitures;
				newVoiture[iVoiture].set_coordonnes(coordVoiture.x, i);
				newSituation.push_back(new Situation(newVoiture));

			}

			for(int i = coordVoiture.y + voitures[iVoiture].get_taille(); i < Situation::SIZE; i++) {
				if(tab[coordVoiture.x][i] == false)
					break;

				std::vector<Voiture> newVoiture = voitures;
				newVoiture[iVoiture].set_coordonnes(coordVoiture.x, i - voitures[iVoiture].get_taille() + 1);
				newSituation.push_back(new Situation(newVoiture));
			}

		} else {

			for(int i = coordVoiture.x - 1; i >= 0; i--) {
				if(tab[i][coordVoiture.y] == false)
					break;

				std::vector<Voiture> newVoiture = voitures;
				newVoiture[iVoiture].set_coordonnes(i, coordVoiture.y);
				newSituation.push_back(new Situation(newVoiture));

			}

			for(int i = coordVoiture.x + voitures[iVoiture].get_taille(); i < Situation::SIZE; i++) {
				if(tab[i][coordVoiture.y] == false)
					break;

				std::vector<Voiture> newVoiture = voitures;
				newVoiture[iVoiture].set_coordonnes(i - voitures[iVoiture].get_taille() + 1, coordVoiture.y);
				newSituation.push_back(new Situation(newVoiture));
			}

		}

	}

	for(int i = 0; i < 6; i++) {
		delete[] tab[i];
	}
	delete[] tab;

	return newSituation;
}


bool Situation::victoire() const {
	const Voiture &voiture = this->voitures[0];
	if(voiture.is_horizontal()) {
		return voiture.get_coord() == Coordonnees(Situation::sortie.x, Situation::sortie.y - (voiture.get_taille() - 1));
	} else {
		return voiture.get_coord() == Coordonnees(Situation::sortie.x - (voiture.get_taille() - 1), Situation::sortie.y);
	}
}


bool operator==(const Situation &s1, const Situation &s2) {
	for(long unsigned int i = 0; i < s1.voitures.size(); i++) {
		if(s1.voitures[i].get_coord() != s2.voitures[i].get_coord()) {
			return false;
		}
	}
	return true;
}

std::ostream& operator<<(std::ostream& stream, Situation*& situation) {
    char** tab = new char*[6];
    for(int i = 0; i < 6; i++) {
        tab[i] = new char[6];
        for(int j = 0; j < 6; j++) {
            tab[i][j] = '~';
        }
    }



	int mainVoiture = 0;
    for(const Voiture& it : situation->voitures) {
        for(int i = 0; i < it.get_taille(); i++) {
            if(it.is_horizontal()) {
                if(mainVoiture == 0)
                    tab[it.get_coord().x][it.get_coord().y + i] = '#';
                else
                    tab[it.get_coord().x][it.get_coord().y + i] = '-';
            } else {
                if(mainVoiture == 0)
                    tab[it.get_coord().x + i][it.get_coord().y] = '#';
                else
                    tab[it.get_coord().x + i][it.get_coord().y] = '|';
            }
        }
		mainVoiture++;
    }

    for(int i = 0; i < 7; i++){
        stream << "_";
    }
    stream << std::endl;
    for(int i = 0; i < 6; i++) {
        stream << "|";
        for(int j = 0; j < 6; j++) {
            stream << tab[i][j];
        }
        stream << "|";
        stream << std::endl;
        delete[] tab[i];
    }

    delete[] tab;

	return stream;
}
