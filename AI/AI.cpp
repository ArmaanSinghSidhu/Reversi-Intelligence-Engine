//This the kinda like the parent class of AI folder
//AI.cpp implements MiniMax.cpp, Evaluation.cpp, and TranspositionTable.cpp
//The classes create an AI player to be implemented for the game
#include "Evaluation.cpp";
#ifndef AI
#define AI 
class AI
{
    private:
        int searchDepth = 3;
        Evaluation evaluation;
        char color; 
        
    public:

    //idk why there is an issue in the constructor
    AI()
    {
       color = "B";
       evaluation = "B";
    }
    AI(char c)
    {
        color = c; 
        evaluation = c;
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

#endif AI