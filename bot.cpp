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

int Bot::isMate(vector<int> field){
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {

            if (field[y * 20 + x] == 0) {continue; }

            if (y < 15) {
                int iar = checkDown(y * 20 + x, field);
                if (iar == 5 || iar == 10) {
                    return iar / 5;
                }
            }
            if (x < 15) {
                int iar = checkRight(y * 20 + x, field);
                if (iar == 5 || iar == 10) {
                    return iar / 5;
                }
            }
            if (y < 15 && x < 15) {
                int iar = checkDownRight(y * 20 + x, field);
                if (iar == 5 || iar == 10) {
                    return iar / 5;
                }
            }
            if (y >= 4 && x < 15) {
                int iar = checkUpRight(y * 20 + x, field);
                if (iar == 5 || iar == 10) {
                    return iar / 5;
                }
            }
        }
    }
    return 0;
}

int Bot::checkDown(int i, vector<int> field) {
    int val = field[i];
    if (val == 0) {return 0;}
    return checkDown(i + 20, field) + val;
}

int Bot::checkRight(int i, vector<int> field) {
    int val = field[i];
    if (val == 0) {return 0;}
    return checkRight(i + 1, field) + val;
}

int Bot::checkDownRight(int i, vector<int> field) {
    int val = field[i];
    if (val == 0) {return 0;}
    return checkDownRight(i + 21, field) + val;
}

int Bot::checkUpRight(int i, vector<int> field) {
    int val = field[i];
    if (val == 0) {return 0;}
    return checkUpRight(i - 19, field) + val;
}

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