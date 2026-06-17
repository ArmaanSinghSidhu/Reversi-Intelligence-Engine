//This the kinda like the parent class of AI folder
//AI.cpp implements MiniMax.cpp, Evaluation.cpp, and TranspositionTable.cpp
//The classes create an AI player to be implemented for the game
#include "Evaluation.cpp";

class AI
{
    private:
        int searchDepth = 3;
        Evaluation evaluation;
        char color; 
        
    public:

   
    AI() : color('B'){}

    AI(char c)
    {
        color = c; 
        // evaluation = c;
    }

    //insert copy of current game, then output best move
    int getBestMove(Game& copy)
    {
        return evaluation.getBestMove(copy);
    }

    char getColor()
    {
        return color;
    }

};

