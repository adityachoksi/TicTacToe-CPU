#ifndef TGAME_H 
#define TGAME_H 

using namespace std;

class TGame{
 
    public:
    
    /**
     * Constructs a new empty board, 0 represents empty, o is cpu, x is player
     * param fst true if cpu goes first
    */
    TGame(bool fst);
    
    /**
     * Checks a row and column value to see if move is valid
     * param row 1-indexed int representing a row on the board
     * param col 1-indexed int representing a column on the board
    */
    bool checkMove(int row, int column) const;
    
    /**
     * Changes value of board at a row and column to current player's piece value
     * param row-1 indexed int representing a row on the board
     * param col-1 indexed int representing a column on the board
    
    */
    void makeMove(int row, int column);
    
    /**
     * checks whether 3 of the same piece are in a sequence on the board for a player
     * param p player to be checked
     * return true if current player has won the game
    */
    bool winner() const;
    
    /**
     * return the total number of moves played in the game so far
    */
    int getMoves() const;
    
    /**
     * displays the gameboard to the console as well as a turn indicator for clarity
    */
    void display() const;
    
    //below here are functions used by the internal evaluation system
    
    /**
     * checks if there is a game ending move for player p
     * param p player to spot for
     * return 0 if none or int corresponding to a row, column, or diagonal 
    */
    int spotThreat(int p) const;
    
    /**
     * blocks the opponent's game ending moves and makes winning moves based on threat values
     * param threat number generated by spotThreat that is used to make apropriate move
    */
    void handle(int threat);
    
    /**
     * makes the first valid move available on the board
    */
    void validMove();
    
    /**
     * puts together above functions to make a move for a cpu that can never lose
    */
    void cpuMove();
    
    private:
    
    //keeps track of board values
    int board[3][3];
    
    //keeps track of total moves played
    int moves;
    
    //keeps track of current player
    int player;
    
    //keeps track of what start the opponent used
    int start;
    
    //keeps track of whether cpu goes first
    bool first;
};

#endif