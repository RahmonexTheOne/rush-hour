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
    int row, col, lenght, orient;
    while (levelFile >> row >> col >> lenght >> orient){
      listCar.push_back(Car(Place(row, col), intToOrientation(orient), lenght));
    }
    levelFile.close();
    this->m_indexCarToExit = this->getIndexMainCar();
    return;
  }
  throw std::exception();

}
// ------------------------------------------------------------------------------------------------






//------------------------------------------------------------ Check if car is on exit place:
bool Board::carIsOnExit(Car car) const {
    if(car.getOrientation() == UP){
        if(this->theExit.getRow() == 0){
            if (abs(car.getFirstPlace(UP).getRow() - this->theExit.getRow())==0){
                return true;
            }
            else{
                return false;
            }
        }

        else{
            if (abs(car.getLastPlace(UP).getRow() - this->theExit.getRow())==0){
                return true;
            }
            else{
                return false;
            }
        }

    }
    else{
        if(this->theExit.getColumn() == 0){
            if (abs(car.getFirstPlace(LEFT).getColumn() - this->theExit.getColumn())==0){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            if (abs(car.getLastPlace(LEFT).getColumn() - this->theExit.getColumn())==0){
                return true;
            }
            else{
                return false;
            }
        }
    }
}

bool Board::carIsOnExit() const {
    return this->carIsOnExit(this->listCar.at(this->m_indexCarToExit));
}
//-----------------------------------------------------------------------------------------------






//------------------------------------------------------------- Generating the solution (in list of Moves) :
std::vector<Move> Board::solutionList(const Board src){
    std::queue<Board> listBoardPossible;
    std::unordered_set<std::string > listBoardUsed;
    listBoardPossible.push(src);
    listBoardUsed.insert(src.to_string());
    Board board = src;

    while(!listBoardPossible.empty() && !board.carIsOnExit()) {
        board = listBoardPossible.front();
        listBoardPossible.pop();
        for (int i = 0; i < board.listCar.size(); i++) {
            std::vector<Move> listAllMoves = board.getListPossibleMoves(i);
            for (Move moves: listAllMoves) {
                Board clone = board.cloneBoardWithPossibleMoves(moves);
                //Create clones to test if they are not duppliucated
                if (!boardExist(listBoardUsed, clone.to_string())) {
                    listBoardPossible.push(clone);
                    listBoardUsed.insert(clone.to_string());
                }
            }
        }
    }
    if(!board.carIsOnExit()){
        return std::vector<Move>();
    }

    else{
        return board.m_listMoves;
    }

}


//-------Send result :
std::vector<Move> Board::solutionList() {
    return this->solutionList(*this);
}
//----------------------------------------------------------------------------------------



//---------------------------------------------------------Check if we can Move :
bool Board::canMove(Place src) {
    if(src.getRow() < 0 || src.getColumn() < 0 ||
       src.getRow() >= this->getHeight() || src.getColumn() >= this->getWidth())
        return false;
    return this->getCarByPlace(src) == nullptr;
}
//------------------------------------------------------------------------

//---------------------------------------------Get car by place :
Car *Board::getCarByPlace(Place src){
    for (Car& element : this->listCar) {
        if(element.isOccupied(src))
            return &element;
    }
    return nullptr;
}
//--------------------------------------------



//-------------------------------------------------------Clone board with possible moves:
Board Board::cloneBoardWithPossibleMoves(Move move)  {
    Board board = Board(*this);
    board.listCar.at(move.m_indexCar).move(move.m_orientation,move.m_lenght);
    board.m_listMoves.push_back(move);
    return board;
}
//---------------------------------------------------------------------------------------

//------------------------------------------------------Move Car:
void Board::moveCar(int index, Orientation orientation, unsigned int lenght) {
    this->listCar.at(index).move(orientation, lenght);
}
//------------------------------------------------------------------------





//------------------------------------------- Generating a list of moves around a car :
std::vector<Move> Board::getListPossibleMoves(int indexCar)  {
    std::vector<Move> lPossibleMoves;
    unsigned int lenght = 1;

    Car elementDir1 = Car(this->listCar.at(indexCar));
    elementDir1.move(elementDir1.getOrientation(),1);
    while(canMove(elementDir1.getFirstPlace(elementDir1.getOrientation()))){
        lPossibleMoves.push_back(Move(
                indexCar,
                elementDir1.getOrientation(),
                lenght++)
        );
        elementDir1.move(elementDir1.getOrientation(),1);
    }


    lenght = 1;
    Car elementDir2 = Car(this->listCar.at(indexCar));
    elementDir2.move(elementDir2.getOppositeOrientation(elementDir2.getOrientation()),1);
    while(canMove(elementDir2.getLastPlace(elementDir2.getOrientation()))){
        lPossibleMoves.push_back(Move(
                indexCar,
                elementDir2.getOppositeOrientation(elementDir2.getOrientation()),
                lenght++)
        );
        elementDir2.move(elementDir2.getOppositeOrientation(elementDir2.getOrientation()),1);
    }

    return lPossibleMoves;
}

//-------------------------------------------------------------------------------------------------







//------------------------------------------------------- Helpfull functions :
std::string Board::to_string() const {
    std::stringstream buffer;
    buffer << *this;
    return buffer.str();
}
//--------------
bool Board::boardExist(std::unordered_set<std::string > listBoards, std::string stringBoard){
    return listBoards.find(stringBoard) != listBoards.end();
}
//-----------------------------------------------------------------------------




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


  //Place cars ++ Rajouter collisions (si tab [i][j] != 0 ne pas remplir ??)
  unsigned int boardSize = board.getCar().size();
  for(unsigned int i = 0; i < boardSize; ++i) {
    Car car = board.getCar().at(i);
     //Give a number to each car to make it differenciable
     //Give same number horizontally for cars that have left and right orientation
    if(car.getOrientation() == Orientation::RIGHT || car.getOrientation() == Orientation::LEFT) {
      for(unsigned int j = 0; j < car.getLenght(); ++j) {
          //same row
        level[car.getPlace().getColumn()  + j][car.getPlace().getRow()] = i + 1;
      }
      //Give same number vertically for cars that have up and down orientation
    } else {
      for(unsigned int j = 0; j < car.getLenght(); ++j) {
          //same column
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
