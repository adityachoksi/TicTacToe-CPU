#include "TGame.h" 
#include <iostream>

using namespace std;

/**
 * converts a board value to the correct letter for display
 * param n value of board
*/
char convert(int n){
    if(n==0){
        return ' ';
    }
    if(n==1){
        return 'x';   
    }
    if(n==5){
        return 'o';
    }
}

TGame::TGame(bool fst){
    //board = {{0,0,0},{0,0,0},{0,0,0}};
    for (int i = 0; i<3;i++){
        for (int j = 0;j<3;j++){
            board[i][j] = 0;
        }
    }
    first = fst;
    if(first){
        player = 5;
    }
    else{
        player = 1;
    }
    moves = 0;
    start = 80;
}


bool TGame::checkMove(int row, int column) const{
    int r = row;
    int c = column;
    if (c>3 || c<1){
        return false;
    }
    if (r>3 || r<1){
        return false;
    }
    if (board[r-1][c-1] == 0){
        return true;
    }
    return false;
}


void TGame::makeMove(int row, int column){
    moves++;
    board[row-1][column-1] = player;
    if (player == 1){
        player = 5;
    }
    else{
        player = 1;
    }
}


bool TGame::winner() const{
    int p;
    if(player == 1){
        p = 5;
    }
    else{
        p = 1;
    }
    //checking diagonals
    if ((((board[0][0])==p) && (board[1][1]==p) && (board[2][2]==p))||((board[0][2]==p) && (board[1][1]==p) && (board[2][0]==p))){
        return true;
    }
    
    //checking rows
    for(int i = 0; i<3; i++){
        if((board[i][0]==p) && (board[i][1]==p) && (board[i][2]==p)){
            return true;
        }
    }
    //checking columns
    for(int i = 0; i<3; i++){
        if((board[0][i]==p) && (board[1][i]==p) && (board[2][i]==p)){
            return true;
        }
    }
    return false;
}

int TGame::getMoves() const{
    return moves;
}

void TGame::display() const{
    cout << '\n'  << convert(player) <<" turn\n";
    cout << " " << convert(board[0][0]) << " | " << convert(board[0][1]) << " | " << convert(board[0][2]) << '\n';
    cout << "___________"  << '\n';
    cout << " " << convert(board[1][0]) << " | " << convert(board[1][1]) << " | " << convert(board[1][2]) << '\n';
    cout << "___________"  << '\n';
    cout << " " << convert(board[2][0]) << " | " << convert(board[2][1]) << " | " << convert(board[2][2]) << "\n\n";
}


//internal evaluation for computer moves

int TGame::spotThreat(int p) const{
    int threat = p*2;
    for(int i=0; i<3; i++){
        if((board[i][0] + board[i][1] + board[i][2]) == threat){
            return (i+1);
        }
    }
    for(int i=0; i<3; i++){
        if((board[0][i] + board[1][i] + board[2][i]) == threat){
            return (i+4);
        }
    }
    if((board[0][0] + board[1][1] + board[2][2]) == threat){
        return 7;
    }
    if((board[0][2] + board[1][1] + board[2][0]) == threat){
        return 8;
    }
    return 0;
}

void TGame::handle(int threat){
    if(threat<4 && threat>0){
        int trow = threat - 1;
        for(int i=0;i<3;i++){
            if(board[trow][i]==0){
                makeMove(trow+1,i+1);
            }
        }
    }
    else if(threat<7 && threat>3) {
        int tcol = threat - 4;
        for(int i=0;i<3;i++){
            if(board[i][tcol]==0){
                makeMove(i+1,tcol+1);
            }
        }
    }
    else if(threat == 7){
        if(board[0][0] == 0){
            makeMove(1,1);
        }
        if(board[1][1] == 0){
            makeMove(2,2);
        }
        if(board[2][2] == 0){
            makeMove(3,3);
        }
    }
    else if(threat == 8){
        if(board[0][2] == 0){
            makeMove(1,3);
        }
        if(board[1][1] == 0){
            makeMove(2,2);
        }
        if(board[2][0] == 0){
            makeMove(3,1);
        }
    }
}

void TGame::validMove(){
    bool moved = false;
    for(int i = 0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j] == 0 && moved == false){
                makeMove(i+1,j+1);
                moved = true;
            }
        }
    }
}

void TGame::cpuMove(){
    int finish = spotThreat(5);
    int block = spotThreat(1);
    bool played = false;
    if (finish == 0 && block == 0){
        if(getMoves() == 0){
            start = 4;
            makeMove(2,2);
            played = true;
        }
        else if(getMoves() == 1){
            if(board[1][1] == 1){
                start = 0;
                makeMove(3,1);
                played = true;
            }
            else if(board[0][0] + board[0][2] + board[2][0] + board[2][2] == 1){
                start = 1;
                makeMove(2,2);
                played = true;
            }
            else{
                start = 2;
                makeMove(2,2);
                played = true;
            }
        }
        if((getMoves() == 2) && (played == false) && (start == 4)){
            if(board[0][0] + board[0][2] + board[2][0] + board[2][2] == 1){
                if (board[0][0] == 1){
                    makeMove(3,3);
                }
                else if (board[0][2] == 1){
                    makeMove(3,1);
                }
                else if (board[2][0] == 1){
                    makeMove(1,3);
                }
                else{
                    makeMove(1,1);
                }
                played = true;
            }
            else{
                if (board[1][0] + board[0][1] == 5){
                    makeMove(3,3);
                }
                else{
                    makeMove(1,1);
                }
            played = true;
            }
        }
        if (getMoves() == 3 && start == 0 && played == false){
            makeMove(1,1);
            played = true;
        }
    }
    else if(finish != 0){
        handle(finish);
        played = true;
    }
    else{
        handle(block);
        played = true;
    }
    if(played == false){
        validMove();
    }
    
}