//MiniMax.cpp
//Objective 1: Create Binary tree to find optimal game position, higher the value[i.e right side] the better the position is 
#include "Disk.h";
#include "Game.h";
#include "TranspositionTable.cpp";
class MiniMax
{
    
    private:
    //weights
    const int WEIGHTS[8][8] = {4, -3, 2, 2, 2, 2, -3, 4,
               -3, -4, -1, -1, -1, -1, -4, -3,
               2, -1, 1, 0, 0, 1, -1, 2,
               2, -1, 0, 1, 1, 0, -1, 2,
               2, -1, 0, 1, 1, 0, -1, 2,
               2, -1, 1, 0, 0, 1, -1, 2,
               -3, -4, -1, -1, -1, -1, -4, -3,
               4, -3, 2, 2, 2, 2, -3, 4};
    
    //Do static evaluation: i.e. evaluaiton of just the current game position without looking ahead
    static int staticEvaluation(const Game& copy, char color)
    {
        
    }

    //returns minimax value for a given node with A/B pruning
    static int MMAB(Game& state, char aiColor, char turnColor, int depth, bool isMax, int alpha, int beta, TranspositionTable& table)
    {

    }



    public:
    
    //This method returns the max score move; i.e best move
    static Disk solve(Game game, char playerColor, int depth, TranspositionTable& table)
    {
        
        
    }

};

