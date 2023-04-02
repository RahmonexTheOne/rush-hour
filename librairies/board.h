#ifndef BOARD_H
#define BOARD_H

#include "place.h"
#include "car.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <unordered_set>

struct Move{
    unsigned int m_indexCar;
    Orientation m_orientation;
    unsigned int m_longueur;

    explicit Move(){};
    Move(int indexCar, Orientation orientation, unsigned int longueur)
            : m_indexCar(indexCar),
              m_orientation(orientation),
              m_longueur(longueur){};
};

class Board
{

public:
    int actualLevel =1;

    explicit Board(int width = 6, int height = 6);

    //Create the board by reading a specific file (file must be written in argument)
    void loadLevel(const char* cheminFichier);

    bool operator== (const Board board) const;

    //Generate a level without parsing any argument
    void generate();



    //--------------------------------------------Getters :
    int getIndexMainCar();
    Car getCarToExit();
    const int getExitRow() const {return theExit.getRow();};
    const int getWidth() const { return this->board_width; }
    const int getHeight() const { return this->board_height; }
    Car* getCarByPlace(Place src);
    const std::vector<Car> getCar() const { return this->listCar; }
    //---------------------------------------------------------



    //--------------------------------------------Setters :
    void setExit(int height, int width);
    //----------------------------------------------------



private:

    Orientation intToOrientation(int orientation);



    int board_width;
    int board_height;
    //List of all cars in the board
    std::vector<Car> listCar;
    //List of the moves (maybe give it a try)
    std::vector<Move> m_listeMove;
    Place theExit;
    //Main Car to exit
    int m_indexCarToExit;


};

//Function that will create the board
std::ostream& operator<<(std::ostream&, const Board&);

#endif // BOARD_H
