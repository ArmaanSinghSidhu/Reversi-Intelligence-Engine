#ifndef TRANSPOSITION_TABLE_CPP
#define TRANSPOSITION_TABLE_CPP
#include "Disk.h"
//TranspositionTable.cpp
//Objective 1: Use Special Zorbist Hash function to save board posiitons
//Credit to documentation:  http://chessprogramming.org/Transposition_Table, https://www.chessprogramming.org/Zobrist_Hashing
enum PruningState {
    //Exact represents the acutal value of the game move
    //Alpha represents a weak move,
    //Beta represents the best move for you, but it assumes your opponent is an idiot; like think of the scholar's mate in chess
    EXACT, ALPHA, BETA
};

class TranspositionTable
{
    private: 
    //table size 2^12, this number comes from that most games by mid game have around 2000-3000 possible secniros they can be in
    static const int tableSize = 4096;
    unsigned long long zobristGrid[8][8][2];
    //The table structure:
    //zobristKey: unique hash identifer for a board arrangement
    //depth: (0-3) how far down to go in the data tree
    //value: the score of posiiton; i.e. how good it is
    //pruningState: what state table is in
    //isValidData: check if the table is empty or not
    struct Table
    {
        unsigned long long zobristKey;
        int depth;
        int value;
        PruningState pruningState;
        bool isValidData;

    };
    Table table[tableSize];
    public:

    //constructor that resets the table
    TranspositionTable()
    {
        for(int i=0; i<tableSize; i++)
        {
            table[i].zobristKey = 0;
            table[i].depth = -1;
            table[i].value = 0;
            table[i].isValidData = false;
        }
        //random constant
        unsigned long long currentSeed = 6767676767676767ULL;

        for(int row=0; row<8; row++)
        {
            for(int col = 0; col < 8; col++)
            {
                //moving the bits left and right
                // ^ is a comparison operator checking if the orginal and new seeds are different
                currentSeed ^= (currentSeed << 6);
                currentSeed ^= (currentSeed >> 7);
                currentSeed ^= (currentSeed << 9);
                //lets say this will be the key for black
                zobristGrid[row][col][0] = currentSeed;

                currentSeed ^= (currentSeed << 6);
                currentSeed ^= (currentSeed >> 7);
                currentSeed ^= (currentSeed << 9);
                //lets say this will be the key for white
                zobristGrid[row][col][1] = currentSeed;
            }
        }
    }

    //store value
    void store(unsigned long long key, int remainingDepth, int score, PruningState pruningState)
    {
        if(remainingDepth > 3)
        {
            remainingDepth = 3;
        }

        int targetIndex = key % tableSize;
        table[targetIndex].zobristKey = key;
        table[targetIndex].depth = remainingDepth;
        table[targetIndex].value = score;
        table[targetIndex].pruningState = pruningState;
        table[targetIndex].isValidData = true;
    }
    //search for value
    bool search(unsigned long long key, int currentDepth, int& alpha, int& beta, int& output)
    {
        int targetIndex = key % tableSize;

        if(table[targetIndex].isValidData && currentDepth <= table[targetIndex].depth && table[targetIndex].zobristKey == key)
        {
            if(table[targetIndex].pruningState == EXACT)
            {
                output = table[targetIndex].value;
                return true;
            }

            if(table[targetIndex].pruningState == ALPHA && table[targetIndex].value <= alpha)
            {
                output = alpha;
                return true;
            }

            if(table[targetIndex].pruningState == BETA && table[targetIndex].value >= beta)
            {
                output = beta;
                return true;
            }
        }

        return false;
    }
     //compute Hash value
     unsigned long long computeHashValue(const Disk board[8][8])
     {
        unsigned long long generatedHash = 0;
        for(int row = 0; row < 8; row++)
        {
            for(int col = 0; col < 8; col++)
            {
                char color = board[row][col].get_color();
                if(color == 'B')
                {
                    generatedHash ^= zobristGrid[row][col][0];
                }else if(color == 'W'){
                     generatedHash ^= zobristGrid[row][col][1];
                }
            }
        }
        return generatedHash;
     }

    
};
#endif //
