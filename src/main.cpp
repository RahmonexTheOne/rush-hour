#include "board.h"
#include <stdlib.h>
#include <time.h>


//-------------------------- If user want the game to be launched in terminal mode :
int terminal_game(int arg, char *argu[]){
    srand (time(NULL));
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

    //Make the Algorithm
    //std::cout << "Generating a solution..." << std::endl << std::endl;


    return EXIT_SUCCESS;
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


