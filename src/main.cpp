#include "board.h"
#include <windows.h>
#include <stdlib.h>
#include <time.h>


void resolveTerminal(Board board);

//-------------------------- If user want the game to be launched in terminal mode :
int terminal_game(int arg, char *argu[]){
    Board board;
    //If has an argument load the board file parsed as argument
    if(arg > 1) {
        try{
            board.loadLevel(argu[1]);
        }
        //If there was a problem loading the file
        catch(const std::exception&){
            std::cerr << "Error occured while loading File" << std::endl;
            return EXIT_FAILURE;
        }
    //If nothing as argument launch the main level (level 1)
    } else {
        std::cout << "Generating level ..." << std::endl << std::endl;
        board.generate();


    }

    std::cout << "Level " << board.actualLevel << "\n" << board << std::endl;

    //Ask to get the solution
    char askSolution;
    std::cout << "Do you want to get the solution of the Level Yes (Y) or No (N)? : ";
    std::cin >> askSolution;
    if (askSolution == 'Y' || askSolution == 'y') {
        std::cout << "Generating Solution...\n";
        resolveTerminal(board);
    }
    else if (askSolution == 'N' || askSolution == 'n') {
        std::cout << "Closing program...\n";
        return EXIT_SUCCESS;
    }
    else {
        std::cout << "Invalid response. Please enter either Y or N.\n";
    }


    return EXIT_SUCCESS;
}

void resolveTerminal(Board board) {
    //Solution (Algorithm)

    //generating th list of moves that leads to the solution
    std::vector<Move> listMoves = board.solutionList();

   unsigned int i = 1;
    //After each move displays the board
    for(Move move : listMoves){
        board.moveCar(move.m_indexCar, move.m_orientation, move.m_lenght);
        std::cout <<"Move " << i++ <<"\n" << board << std::endl;
    }

    std::cout << "Total Moves : " << listMoves.size() << std::endl;
};
//------------------------------------------------------------------------------




//------------------------------------------------------------Main :
int main(int argc, char *argv[])
{
    char response;
    std::cout << "Do you want to launch the game in terminal mode(T) or graphical mode(G)? : ";
    std::cin >> response;
    int result =0;

    if (response == 'T' || response == 't') {
        std::cout << "Launching game in terminal mode...\n";
        result = terminal_game(argc,argv);
    }
    else if (response == 'G' || response == 'g') {
        std::cout << "Launching game in graphical mode...\n";
        std::cout << "Graphical mode is not ready for launch yet, you can try the terminal mode instead \n";
    }
    else {
        std::cout << "Invalid response. Please enter either T or G.\n";
    }

    return result;

}
//-------------------------------------------------------------------------------------
