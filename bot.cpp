#include "bot.hpp"
#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

int Bot::getMoveID(int x, int y){
    return y * 20 + x;
}

int Bot::getMoveID(tuple<int, int> move){
    return get<0>(move) * 20 + get<1>(move);
}

tuple<int, int> Bot::getMoveTuple(int MoveID){
    int y = (int) MoveID / 20;
    return tuple<int, int>(MoveID - y * 20, y);
}

bool Bot::isLegal(vector<int> field, tuple<int, int> move){
    // check if x is in bound
    if (get<0>(move) < 0 || get<0>(move) > 19){
        return false;
    }
    // check if y is in bound
    if (get<1>(move) < 0 || get<1>(move) > 19){
        return false;
    }
    // check if spot is taken
    if(field[getMoveID(move)] != 0){
        return false;
    }
    return true;
};

bool Bot::isMate(vector<int> field){
    //todo pls Tyler mach du
};

vector<tuple<int, int>> Bot::getLegalMoves(vector<int> field){
    vector<tuple<int, int>> legalMoves = vector<tuple<int, int>>();
    tuple<int, int> move;
    for (int y = 0; y<20; y++) {
        for (int x = 0; x<20; x++) {
            move = tuple<int, int>(x, y);
            if(field[getMoveID(move)] == 0){
                legalMoves.push_back(move);
            }
        }
    }
    return legalMoves;
};

vector<int> Bot::makeMove(vector<int> field, tuple<int, int> move, int player){
    if(!isLegal(field, move)){
        cout << "BotError: Tried to make illegal move\n";
        return vector<int>(0);
    }
    field[getMoveID(move)] = player;
    return field;
};

vector<int> Bot::undoMove(vector<int> field, tuple<int, int> move){
    if(!isLegal(field, move)){
        cout << "BotError: Tried to make illegal move\n";
        return vector<int>(0);
    }
    field[getMoveID(move)] = 0;
    return field;
};