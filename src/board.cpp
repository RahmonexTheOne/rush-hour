#include "board.h"
#include <set>
#include <queue>
#include <algorithm>


Board::Board(int width, int height)
                : board_width(width), board_height(height) {

}



// ---------------------------------------------------- Generate the level file (no Args):
void::Board::generate(){
    listCar.clear();

    //Open the actual level text file
    std::stringstream filePath;
    filePath << "../Levels/level" << actualLevel << ".txt";

    std::ifstream levelFile(filePath.str().c_str(), std::ios::in);
    if(levelFile) {
        std::cout << "Level " << actualLevel << " is going to be loaded" << std::endl << std::endl;
        int rowExit, columnExit;
        levelFile >> rowExit >> columnExit;
        this->setExit(rowExit,columnExit);
        int row, col, lenght, orient;
        while (levelFile >> row >> col >> lenght >> orient){
            listCar.push_back(Car(Place(row, col), intToOrientation(orient), lenght));
        }
        levelFile.close();
        this->m_indexCarToExit = this->getIndexMainCar();
        return;
    }
    std::cout << "Level " << actualLevel << " has not been found !" << std::endl;
    throw std::exception();
}

//------------------------------------------------------------------------------------------------





// ---------------------------------------------------- Generate the level file (entered as Args in main):
void Board::loadLevel(const char* filePath) {
  listCar.clear();
  std::ifstream levelFile(filePath, std::ios::in);

  if(levelFile) {
    int rowExit, columnExit;
    levelFile >> rowExit >> columnExit;
    this->setExit(rowExit,columnExit);
    int lig, col, lenght, orient;
    while (levelFile >> lig >> col >> lenght >> orient){
      listCar.push_back(Car(Place(lig, col), intToOrientation(orient), lenght));
    }
    levelFile.close();
    this->m_indexCarToExit = this->getIndexMainCar();
    return;
  }
  throw std::exception();

}
// ------------------------------------------------------------------------------------------------




// --------- Convert the int in level file to an enumeration Orientation (DOWN UP LEFT RIGHT) :
Orientation Board::intToOrientation(int orientation) {
  return (orientation == 1) ? Orientation::LEFT : Orientation::UP;
}
//--------------------------------------------------------------------




// ----------------------------------------------- Get the index of the main car(in the cars list) :
//If main car always first car : useless
//If exit is only right side we don't need 50% of this function
int Board::getIndexMainCar() {
    Orientation orientation;

    if(this->getWidth() == theExit.getRow() + 1)
        orientation = UP;
    else
        orientation = LEFT;

    int indexCarToExit = 0;
    Car *car, *mainCar;
    for(int index = 0; index < this->listCar.size(); index++){

        car = &this->listCar.at(index);

        if(orientation == UP){

            if( car->getOrientation() == UP &&
            car->getPlace().getColumn() == this->theExit.getColumn()){

                if(indexCarToExit == 0){

                    indexCarToExit = index;
                    mainCar = &this->listCar.at(indexCarToExit);
                }
                else if(abs(mainCar->getPlace().getRow() - this->theExit.getRow()) <
                car->getPlace().getRow() - this->theExit.getRow()){

                    indexCarToExit = index;
                    mainCar = &this->listCar.at(indexCarToExit);
                }
            }
        }
        else{

            if(car->getOrientation() == LEFT &&
            car->getPlace().getRow() == this->theExit.getRow()){

                if(indexCarToExit == 0) {
                    indexCarToExit = index;
                    mainCar = &this->listCar.at(indexCarToExit);
                }
                else if(abs(mainCar->getPlace().getColumn() - this->theExit.getColumn()) <
                car->getPlace().getColumn() - this->theExit.getColumn()){
                    indexCarToExit = index;
                    mainCar = &this->listCar.at(indexCarToExit);
                }
            }
        }
    }
    return indexCarToExit;
}
// -----------------------------------------------------------------------------------------



//---------------------------------------- Set theExit :
void Board::setExit(int height, int width) {
    this->theExit = Place(height,width);
}
//----------------------------------------------------




//-------------------------------------------  Creation of the board :
std::ostream& operator<<(std::ostream& os, const Board& board) {
  //Initialize the tab with empty values (0)
  int level[board.getWidth()][board.getHeight()];
  for(int i = 0; i < board.getWidth(); i++){

    for(int j = 0; j < board.getHeight(); j++){

        level[i][j] = 0;
    }
  }


  //Place cars
  unsigned int boardSize = board.getCar().size();
  for(unsigned int i = 0; i < boardSize; ++i) {
    Car car = board.getCar().at(i);
     //Give a number to each car to make it differenciable
     //Give same number horizontally for cars that have left and right orientation
    if(car.getOrientation() == Orientation::RIGHT || car.getOrientation() == Orientation::LEFT) {
      for(unsigned int j = 0; j < car.getLenght(); ++j) {
        level[car.getPlace().getColumn()  + j][car.getPlace().getRow()] = i + 1;
      }
      //Give same number vertically for cars that have up and down orientation
    } else {
      for(unsigned int j = 0; j < car.getLenght(); ++j) {
        level[car.getPlace().getColumn()][car.getPlace().getRow() + j] = i + 1;
      }
    }
  }

  //Colorize the vehicle 30 is black so we give the color 30+ id of the car so that the empty case that represents 0 are
  //in black (more pretty)
  //source : https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal

  //Delimitate the board from the top side :
  for(int i = 0; i < board.getWidth()+1; i++){
      os  << "\033[1;31m _ \033[0m";
  }
  std::cout << std::endl;
  for(unsigned int i = 0; i < board.getHeight(); ++i) {
      os  << "\033[1;31m| \033[0m";
      for(unsigned int j = 0; j < board.getWidth(); ++j) {
      os << "\033[0;" << 30 + level[j][i] << "m" << level[j][i] << "\033[0m";
      //equilibrate the view of the board
      if(level[j][i] > 9) {
          //composed number so need less space
        os << " ";
      }else {
        os << "  ";
      }

    }
      //Make like a door open near the exit
      if(i == board.getExitRow()){
          os << " ";
          os << std::endl;
      }
      else if (i == board.getExitRow()-1) {
          os  << "\033[1;31m| The Exit\033[0m";
          os << std::endl;
      }
      else {
          os  << "\033[1;31m|\033[0m";
          os << std::endl;
      }

  }

    //Delimitate the board from the bot side :
    for(int i = 0; i < board.getWidth()+1; i++){
        os  << "\033[1;31m _ \033[0m";
    }
    os << std::endl;

  return os;
}
//------------------------------------------------------------------------------
