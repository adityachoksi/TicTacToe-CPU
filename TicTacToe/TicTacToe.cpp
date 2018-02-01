#include "TGame.cpp"
#include <iostream>

using namespace std;

int main(){
    //initializes variables for gameflow and finds out whether player is to start
    int rowinput;
    int colinput;
    bool mistake;
    bool first = true;
    cout << "would you like to go first or second(1/2): ";
    cin >> colinput;
    if(colinput == 1){
        first = false;
    }
    //creates game instance and takes first turn if player is second
    TGame game = TGame(first);
    if(first){
        game.cpuMove();
        game.display();
    }
    else{
        game.display();
    }
        
    //starts game and creates endgame conditions
    while(!(game.winner()) and game.getMoves()<9){
        mistake = false;
        //gets player input and makes sure it is valid
        do{
            if (mistake){
                cout << "Invalid Move!\n";
            }
            cout << "Row(1-3): ";
            cin >> rowinput;
            cout << "Column(1-3): ";
            cin >> colinput;
            mistake = true;
        }
        while(!(game.checkMove(rowinput,colinput)));
        //executes player move based on input
        game.makeMove(rowinput,colinput);
        game.display();
        //executes cpu move
        if(game.getMoves() < 9){
            game.cpuMove();
            game.display();    
        }
    }
    return 0;
}