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
    unsigned int m_lenght;

    explicit Move(){};
    Move(int indexCar, Orientation orientation, unsigned int lenght)
            : m_indexCar(indexCar),
              m_orientation(orientation),
              m_lenght(lenght){};
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
    //Create a list of Moves that generates the solution:(we need to take the list with smalest size after)
    std::vector<Move> solutionList(const Board src);
    //Send the result
    std::vector<Move> solutionList();
    //Move Car from a place to a direction with a specific lenght
    void moveCar(int index, Orientation orientation, unsigned int lenght);



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
    std::vector<Move> m_listMoves;
    Place theExit;
    //check if the car is on exit :
    bool carIsOnExit() const;
    bool carIsOnExit(Car car) const;
    std::string to_string(Board const& board) const;
    //Test the existence of the board in listBoard
    static bool boardExist(std::unordered_set<std::string > listBoards,std::string stringBoard);
    //Clone Board
    Board cloneBoardWithPossibleMoves(Move move);
    //Get a list of all possible moves arount the car
    std::vector<struct Move> getListPossibleMoves(int indexElement);
    bool canMove(Place src);
    //Main Car to exit
    int m_indexCarToExit;

};

//Function that will create the board
std::ostream& operator<<(std::ostream&, const Board&);

#endif // BOARD_H
