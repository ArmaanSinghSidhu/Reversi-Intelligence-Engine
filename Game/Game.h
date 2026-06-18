#ifndef GAME_H
#define GAME_H
#include "Disk.h"
#include <string>
#include <fstream>
#include <iostream>
class AI;
using namespace std;
class Game {
    private:
    Disk board[8][8]; //board is an array list of disks
    public:
    Game(){ //fills the board with the starting arrangment
        for (int x=0; x<8;x++){
            for (int i=0;i<8;i++){
                board[i][x]=Disk();
            }
        }
        board[3][3].set_color('W');
        board[3][4].set_color('B');
        board[4][3].set_color('B');
        board[4][4].set_color('W');
    }
    // all locations are given in the format of a 2 digit number ex 34=(3,4);
    //Method takes an offset and checks to see if there is a valid move in that offset. Used in legal move and place.
    bool isValidDirection(int location, char color, int offsetX,int offsetY){
        int row=location%10;
        int col=location/10;
        if (!(board[row+offsetY][col+offsetX].get_color()==color)&&board[row+offsetY][col+offsetX].get_color()!='.'){//checks first Disk to make sure it is the opposing color
            int furtherOffsetX=offsetX; //variables to move the offset further
            int furtherOffsetY=offsetY;
            while(col+furtherOffsetX<8&&col+furtherOffsetX>=0&&row+furtherOffsetY<8&&row+furtherOffsetY>=0){ //Stops at board limits.
                if (board[row+furtherOffsetY][col+furtherOffsetX].get_color()=='.'){ //returns false if we run into an empty square.
                    break;
                }
                if (board[row+furtherOffsetY][col+furtherOffsetX].get_color()==color){ //returns true if it runs into another piece of the same color.
                    return true;
                }
                if (!(board[row+furtherOffsetY][col+furtherOffsetX].get_color()==color)){ //keeps moving if it hits something of the same color.
                    furtherOffsetX+=offsetX;
                    furtherOffsetY+=offsetY;
                }
            }
         }
         return false;
    }
    // Decides if a move should be considered legal or not.
    bool legalMove(char color,int location){ 
        int row=location%10;
        int col=location/10;
        if (board[row][col].get_color()!='.'){ // Makes sure we are on an empty space
            return false;
        }
        // checks every direction
        for (int x=-1;x<=1;x++){ 
            for (int i=-1; i<=1;i++){
                if (!(x==0&&i==0)){
                    if (isValidDirection(location,color,i,x)){
                        return true;
                    }
                }
            }
        }
        return false;
    }
    //returns a string of all legal moves
    string legalMoves(char color){
        string returner="";
         for (int x=0; x<80;x+=10){ //checks full board
            for (int i=0;i<8;i++){
                if (legalMove(color,x+i)){
                    returner+="("+to_string(x/10+1)+","+to_string(i+1)+") "; //adds legal targets to the string. Format: (1,2) (3,4)...
                }
            }
        }
        return returner;
    }

    //This method is needed to for assist MiniMax class with findin the board
    const auto& get_board() const 
    {
        return board;
    }   

    // places disk down and converts other pieces.
    void place(char color,int location){
    int row=location%10;
    int col=location/10;
    board[row][col].set_color(color); //changes current spot
    for (int x=-1;x<=1;x++){
        for (int i=-1; i<=1;i++){ //checks every direction for possible Disks to flip.
            if (!(x==0&&i==0)){
                if (isValidDirection(location,color,i,x)){ 
                        int furtherOffsetX=i;
                        int furtherOffsetY=x;
                        while(true){ //Flips everything in the chosen directions untill it hits a disk of the same color.
                        if (!(board[row+furtherOffsetY][col+furtherOffsetX].get_color()==color)){
                        board[row+furtherOffsetY][col+furtherOffsetX].flip();
                        furtherOffsetX+=i;
                        furtherOffsetY+=x;
                        }
                        if (board[row+furtherOffsetY][col+furtherOffsetX].get_color()==color){
                            break;
                        }
                    }
                }
            }
        }
    }
}
    //Format
    //|1|2|3|4|5|6|7|8|
        //- -----------------
    //1 |.|.|.|.|.|.|.|.|
    //- -----------------
    //2 |.|.|.|.|.|.|.|.|
    //- -----------------
    //3 |.|.|.|.|.|.|.|.|
    //- -----------------
    //4 |.|.|.|W|B|.|.|.|
    //- -----------------
    //5 |.|.|.|B|W|.|.|.|
    //- -----------------
    //6 |.|.|.|.|.|.|.|.|
    //- -----------------
    //7 |.|.|.|.|.|.|.|.|
    //- -----------------
    //8 |.|.|.|.|.|.|.|.|
    //- -----------------
    void print(){ // prints board along with indicies on the top and side
        cout<<"  |1|2|3|4|5|6|7|8|\n";
        cout<<"- -----------------\n";
        for(int x=0;x<8;x++){
            cout<<x+1<<" ";
            for (int i=0;i<8;i++){
                cout<<"|"<<board[x][i].get_color();
                if (i==7){
                    cout<<"|\n";
                    cout<<"- -----------------\n";
                }
            }
        }
    }
    //starts the gameplay loop.
    void Gameloop();
    
};
#include "AI.cpp"
inline void Game::Gameloop(){
        int choice;
        cout<<"Enter 1 to play against AI\nEnter 2 to play local multiplayer\n"; // can play multiplayer or vs AI
        while(true){ //protects from exstranious numbers
            cin>>choice;
            if (choice==1||choice==2){
                break;
            } else {
                cout<<"not a valid input please input 1 or 2\n";
            }
        }
        if (choice==1)
        {
             //TODO: implementing AI feature
            AI bot= AI('W');
            while(true)
            {
                print();
               
                //Code For AI implementation in game
                if(legalMoves('W') != "")
                {
                    cout << "\nAI is preparing to make move\n";
                    int aiMove = bot.getBestMove(*this);
                    cout <<"AI moves to : (" << (aiMove/10 + 1) << "," <<(aiMove % 10 + 1) << ")\n";
                    place('W', aiMove);
                    print();
                } else {
                    cout <<"\n No legal moves left for AI! Turn will be skipped\n";
                }


                if(legalMoves('W') == "" && legalMoves('B') == "")
                {
                    break;
                }


                //end

                if (legalMoves('B')!=""){ //see player vs player for commets on this code (its the same)
                cout<<"player you are B. Here are your available moves\n";
                cout<<legalMoves('B')<<"\n";
                cout<<"please enter your move as a two digit number ex 23 = row 2 column 3\n";
                while(true){
                    cin>>choice;
                    if (legalMove('B',choice-11)){
                        break;
                    } else {
                        cout<<"Plese input a valid move\n";
                    }
                }
                place('B',choice-11);
                }
                if (legalMoves('W')==""&&legalMoves('B')==""){
                    break;
                }
            }
            int white=0;
            int black=0;
            for (int x=0; x<8;x++){
                for (int i=0;i<8;i++){
                    if (board[x][i].get_color()=='W'){
                        white++;
                    } else if(board[x][i].get_color()=='B'){
                        black++;
                    }
                }
            }
            cout<<"Black's score= "<<black<<"\n";
            cout<<"White's score= "<<white<<"\n";
            if (white>black){
                cout<<"congrats white you win\n";
            } else if(black>white){
                cout<<"congrats black you win\n";
            } else {
                cout<<"you tied good job both of you\n";
            }
        }
        if (choice==2){ // vs player
            while(true){ //loops till game is over
                print();
                if (legalMoves('B')!=""){ //skips turn if there are no legal moves
                    cout<<"player 1 you are B. Here are your available moves\n";
                    cout<<legalMoves('B')<<"\n";
                    cout<<"please enter your move as a two digit number ex 23 = row 2 column 3\n";
                    while(true){ //checks for valid input
                        cin>>choice;
                        if (legalMove('B',choice-11)){
                            break;
                        } else {
                            cout<<"Plese input a valid move\n";
                        }
                    }
                place('B',choice-11); //makes a given choice
                print();
                }

                if (legalMoves('W')!=""){ //same thing but for second player
                cout<<"player 2 you are W. Here are your available moves\n";
                cout<<legalMoves('W')<<"\n";
                cout<<"please enter your move as a two digit number ex 23 = row 2 column 3\n";
                while(true){
                    cin>>choice;
                    if (legalMove('W',choice-11)){
                        break;
                    } else {
                        cout<<"Please input a valid move\n";
                    }
                }
                place('W',choice-11);
                }
                if (legalMoves('W')==""&&legalMoves('B')==""){ //condition to break the loop makes sure both players cant move
                    break;
                }
            }
            int white=0; //score keeping system
            int black=0;
            for (int x=0; x<8;x++){
                for (int i=0;i<8;i++){
                    if (board[x][i].get_color()=='W'){
                        white++;
                    } else if(board[x][i].get_color()=='B'){
                        black++;
                    }
                }
            }
            cout<<"Black's score = "<<black<<"\n"; //deciding a winner
            cout<<"White's score = "<<white<<"\n";
            if (white>black){
                cout<<"Congrats white you win\n";
            } else if(black>white){
                cout<<"Congrats black you win\n";
            } else {
                cout<<"You tied good job both of you\n";
            }
        }
    }
#endif
