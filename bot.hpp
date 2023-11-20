#ifndef BOT_H
#define BOT_H

#include <vector>
#include <tuple> 

using namespace std;

class Bot {
public:
    Bot() {};

    /*
     * ID is used to acsess field
    */
    int getMoveID(int x, int y);
    int getMoveID(tuple<int, int> move);

    /*
     * returns move as ```tuple<int, int>```
     * use ```get<0>(move)``` for x and ```get<1>(move)``` for y
    */
    tuple<int, int> getMoveTuple(int MoveID);

    /*
     * Check if x and y are in field bounds and if the spot is taken
     * Does not check, if the game is alreay over (use ```isMate```()) 
    */
    bool isLegal(vector<int> field, tuple<int, int> move);

    /*
     * Returns 1 if myBot won and 2 if evilBot won
     * if its not Mate returns 0
    */
    int isMate(vector<int> field);

    vector<tuple<int, int>> getLegalMoves(vector<int> field);

    vector<int> makeMove(vector<int> field, tuple<int, int> move, int player);

    vector<int> undoMove(vector<int> field, tuple<int, int> move);

private:
    // helper functions for isMate
    int checkDown(int i, vector<int> field);
    int checkRight(int i, vector<int> field);
    int checkDownRight(int i, vector<int> field);
    int checkUpRight(int i, vector<int> field);

};

#endif
