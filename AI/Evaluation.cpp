//Evaluation.cpp 
//Objective 1: looks at a given board setup and works with Binary Search Tree from MiniMax.cpp to find best move
//Objective 2: looks at player or AI move and evaluates it
 #include "Disk.h";
 #include "Game.h";
 #include "MiniMax.cpp";
 #include "TranspositionTable.cpp";
class Evaluation
{
    private:
    int searchDepth = 3;
    int userColor;
    TranspositionTable table;


    //weight table; credit, github user: hylbyj 
    //link: https://github.com/hylbyj/Alpha-Beta-Pruning-for-Othello-Game/blob/master/readme_alpha_beta.txt
    const int WEIGHTS[8][8] = {4, -3, 2, 2, 2, 2, -3, 4,
               -3, -4, -1, -1, -1, -1, -4, -3,
               2, -1, 1, 0, 0, 1, -1, 2,
               2, -1, 0, 1, 1, 0, -1, 2,
               2, -1, 0, 1, 1, 0, -1, 2,
               2, -1, 1, 0, 0, 1, -1, 2,
               -3, -4, -1, -1, -1, -1, -4, -3,
               4, -3, 2, 2, 2, 2, -3, 4};

     //Do I need this method? This class seems to have turned into wrapper class for MiniMax.cpp
//     //method to evaluate board layouts
//     int evaluateBoardLayout(Game& copy)
//     {
        
//     }

    public:
    Evaluation() : userColor('.'){}

    Evaluation(int color)
    {
        userColor = color;
        //intialize table
    }

   bool isPlayerUser()
   {
        return false;
   }

   int getBestMove(Game& copy)
   {
        return MiniMax::solve(copy,userColor,searchDepth, table);
   }
   
};

