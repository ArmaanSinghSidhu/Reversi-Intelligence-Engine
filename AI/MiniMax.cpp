#ifndef MINIMAX_CPP
#define MINIMAX_CPP
//MiniMax.cpp
//Objective 1: Create Binary tree to find optimal game position, higher the value[i.e right side] the better the position is 
//Such a pain to program 
//Credit to documentation that helped guide me through this: https://www.chessprogramming.org/Alpha-Beta
#include "Disk.h"
#include "TranspositionTable.cpp"
#include <limits>
#include <string>
#include "Game.h"
class MiniMax
{
    
    private:
    //weights
    static const int WEIGHTS[8][8];
    
    //Do static evaluation: i.e. evaluaiton of just the current game position without looking ahead
    static int staticEvaluation(Game& copy, char color)
    {
        int score = 0;
        char opponentColor = 'B';
        if(color == 'B')
        {
            opponentColor = 'W';
        }

        const auto& board = copy.get_board();

        for(int row = 0; row < 8; row++)
        {
            for(int column = 0; column < 8; column++)
            {
                char currentDiskColor = board[row][column].get_color();

                if(currentDiskColor == color)
                {
                    score += WEIGHTS[row][column];
                }else if(currentDiskColor == opponentColor)
                {
                    score -= WEIGHTS[row][column];
                }
            }
        }
        return score;
    }

    //returns minimax value for a given node with A/B pruning
    static int MMAB(Game& state, char aiColor, char turnColor, int depth, bool isMax, int alpha, int beta, TranspositionTable& table)
    {
        
        unsigned long long boardHash = table.computeHashValue(state.get_board());
        int tempValue = 0;

        if(table.search(boardHash, depth, alpha, beta, tempValue))
        {
            return tempValue;
        }

        std::string aiMoves = state.legalMoves(aiColor);
        char opponentColor = 'B';
        if(aiColor == 'B')
        {
            opponentColor = 'W';
        }
        std::string opponentMoves = state.legalMoves(opponentColor);

        bool ifAiCanMove = !aiMoves.empty();
        bool ifOpponentCanMove = !opponentMoves.empty();

        if(depth == 0 || (!ifAiCanMove && !ifOpponentCanMove))
        {
            return staticEvaluation(state, aiColor);
        }

        //If no legal moves left, you can skip the turn
        if((!isMax && !ifAiCanMove) || (!isMax && !ifOpponentCanMove))
        {
            char tempTurnColor = 'B';
            if(turnColor == 'B')
            {
                tempTurnColor = 'W';
            }
            return MMAB(state, aiColor, tempTurnColor, depth -1, !isMax, alpha, beta, table);
        }

        PruningState pruningState = ALPHA;

        if(isMax)
        {
            int maxLimit = std::numeric_limits<int>::min();

            for(int i = 0; i <= 77; i++)
            {
                int row = i % 10;
                int column = i/10;
                if(row <= 7 && column <= 7 && state.legalMove(turnColor, i))
                {
                    Game branch = state;
                    branch.place(turnColor, i);
                    int evaluation = MMAB(branch, aiColor, opponentColor, depth -1, false, alpha, beta, table);

                    if(evaluation > maxLimit)
                    {
                        maxLimit = evaluation;
                    }

                    if(maxLimit > alpha)
                    {
                        alpha = maxLimit;
                    }

                    if(beta <= alpha)
                    {
                        pruningState = BETA;
                        break;
                    }
                }
            }

            if(pruningState != BETA)
            {
                pruningState = EXACT;
            }
            table.store(boardHash, depth, maxLimit, pruningState);
            return maxLimit;
        }else 
        {
            int minLimit = std::numeric_limits<int>::max();
            
            for(int i = 0; i <= 77; i++)
            {
                int row = i % 10;
                int column = i/10;
                if(row <= 7 && column <= 7 && state.legalMove(turnColor, i))
                {
                    Game branch = state;
                    branch.place(turnColor, i);
                    int evaluation = MMAB(branch, aiColor, opponentColor, depth -1, false, alpha, beta, table);

                    if(evaluation < minLimit)
                    {
                        minLimit = evaluation;
                    }

                    if(minLimit < beta)
                    {
                        beta = minLimit;
                    }

                    if(beta <= alpha)
                    {
                        pruningState = BETA;
                        break;
                    }
                }
            }

            if(pruningState != BETA)
            {
                pruningState = EXACT;
            }
             table.store(boardHash, depth, minLimit, pruningState);
            return minLimit;

        }

    }



    public:
    
    //This method returns the max score move; i.e best move
    static int solve(Game game, int playerColor, int depth, TranspositionTable& table)
    {
        if(depth > 3)
        {
            depth = 3;
        }

        char aiColor = 'W';
        if(playerColor == 'W' || playerColor  == 1)
        {
            aiColor = 'B';
        }

        char opponentColor = 'W';
        if(aiColor == 'W')
        {
            opponentColor = 'B';
        }

        int bestMoveLocation = -1;
        int highestScore = std::numeric_limits<int>::min();
        int alpha = std::numeric_limits<int>::min();
        int beta = std::numeric_limits<int>::max();

        for(int i = 0; i <= 77; i++)
        {
            int row = i % 10;
            int column = i / 10;

            if(row <= 7 && column <= 7 && game.legalMove(aiColor, i))
            {
                Game state = game;
                state.place(aiColor, i);

                int moveValue = MMAB(state, aiColor, opponentColor, depth-1, false, alpha, beta, table);

                if(moveValue > highestScore)
                {
                    highestScore = moveValue;
                    bestMoveLocation = i;
                }
            }
        }

        return bestMoveLocation;


    }

};

 //why is c++ weird lol
     const int MiniMax::WEIGHTS[8][8] = {4, -3, 2, 2, 2, 2, -3, 4,
               -3, -4, -1, -1, -1, -1, -4, -3,
               2, -1, 1, 0, 0, 1, -1, 2,
               2, -1, 0, 1, 1, 0, -1, 2,
               2, -1, 0, 1, 1, 0, -1, 2,
               2, -1, 1, 0, 0, 1, -1, 2,
               -3, -4, -1, -1, -1, -1, -4, -3,
               4, -3, 2, 2, 2, 2, -3, 4};

#include "Game.h"
#endif