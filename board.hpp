#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <tuple> 

using namespace std;

class Board {
public:
    int moveCount;

    /*
     * creates new empty board
    */
    Board() {
        reset();
    };

    Board(const vector<int>& field): field(field) {}

    /*
     * reset all moves
    */
    void reset();

    /*
     * ID used to acsess field
    */
    int getMoveID(int x, int y);

    /*
     * ID used to acsess field
    */
    int getMoveID(tuple<int, int>);

    /*
     * returns move as ```tuple<int, int>```
     * use ```get<0>(move)``` for x and ```get<1>(move)``` for y
    */
    tuple<int, int> getMoveTuple(int MoveID);

    /*
     * Check if x and y are in field bounds and if the spot is taken
     * Does not check, if the game is alreay over (use ```isMate```()) 
    */
    bool isLegal(int move);

    bool isMate();
    /* 
     * Count how many Pieces of a player are in a row.
     * Directions:
     * down = 20
     * right = 1
     * downright = 21
     * downleft = 19
     * ...
     * Used function for isMate
    */
    int countIAR(int start, int player, int direction);

    int getPlayer(){return moveCount % 2 + 1;}
    

    vector<int> getLegalMoves();

    

    void makeMove(int move, int player);

    void undoMove(int move);

    vector<int> getField(){
        return field;
    }

    void setField(vector<int> _field){
        field = _field;
    }

    int& operator[](int move);

private:
    // print function is private, so the bots cant print. 
    // 5IAR functions that are allowed to print are friend functions 
    friend void runGame();
    friend void setupGame();

    void print();

    vector<int> field;
};

#endif // BOARD_H
