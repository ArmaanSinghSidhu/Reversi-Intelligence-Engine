#include <iostream>
#include <cassert>
#include "Game/Game.h"
#include "TranspositionTable.cpp" 
#include "MiniMax.cpp"

using namespace std;
void test() 
{
    
    Game game;
    TranspositionTable table;

    cout << "best move for black?" <<endl;
    int aiMove = MiniMax::solve(game, 1, 3, table);
    cout << "returned value: " << aiMove << endl;
    int row = aiMove % 10;
    int col = aiMove / 10;

    assert(aiMove >= 0);
    assert(row <= 7);
    assert(col <= 7);
    assert(game.legalMove('B', aiMove));

}

int main() 
{ 
    test();
    return 0;
}