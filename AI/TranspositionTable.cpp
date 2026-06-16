//TranspositionTable.cpp
//Objective 1: Use Special Zorbist Hash function to save board posiitons
enum PruningState {
    //Exact represents the acutal value of the game move
    //Alpha represents a weak move
    //Beta represents the best move for you, but it assumes your opponent is an idiot; like think of the scholar's mate in chess
    EXACT, ALPHA, BETA
};

class TranspositionTable
{
    private: 
    //zobrist key
    int depth;
    int value;
    PruningState pruningState;
    bool isValidMove;


    public:

    //constructor


    //store value

    //search for value

     //compute value
    
};

