#include "Graphe.h"

Graphe::Graphe(const std::string& file) {
	Situation* initial = Situation::generate_board_from_file(file);
	this->source = new Noeud(initial);
	this->allNoeuds.push_back(this->source);
	this->liste.push(this->source);
}

Graphe::~Graphe() {
	for(long unsigned int i = 0; i < this->allNoeuds.size(); i++)
		delete this->allNoeuds[i];
}

Noeud* Graphe::genereEtParcours(){
	Noeud* arrivee = nullptr;
	while(!liste.empty() && arrivee == nullptr){
		Noeud* temp = liste.front();
		std::vector<Situation*> ls = temp->getSituation()->genereSituations();
		for(Situation* situationGeneree : ls){
			bool nouveau = true;
			for(Noeud* noeud : allNoeuds){
				Situation* s = noeud->getSituation();
				if(*situationGeneree == *s)
					nouveau=false;
			}
			if(nouveau){
				Noeud* n = new Noeud(situationGeneree,temp->getNbIteration(),temp);
				this->allNoeuds.push_back(n);
				liste.push(n);
				if(situationGeneree->victoire())
					arrivee = n;
			} else {
				delete situationGeneree;
			}
		}
		liste.pop();
	}
	
	return arrivee;
}

std::vector<Noeud*> Graphe::getChemin(Noeud* arrivee) {
    std::vector<Noeud*> res;
    Noeud* temp = arrivee;

    while (temp != nullptr) {
        res.push_back(temp);
        temp = temp->getParent();
    }

    return res;
}
