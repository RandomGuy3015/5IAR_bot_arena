#include "board.hpp"
#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

void Board::reset(){
    field = vector<int>(20);
}

int Board::getMoveID(int x, int y){
    return y * 20 + x;
}

int Board::getMoveID(tuple<int, int> move){
    return get<0>(move) * 20 + get<1>(move);
}

tuple<int, int> Board::getMoveTuple(int MoveID){
    int y = (int) MoveID / 20;
    return tuple<int, int>(MoveID - y * 20, y);
}

bool Board::isLegal(int move){
    // check if move is in bound
    if (move < 0 || move > 399){
        return false;
    }
    // check if spot is taken
    if(field[move] != 0){
        return false;
    }
    return true;
};

int Board::isMate() {
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {

            int player = field[y * 20 + x];

            if (player == 0) {continue; }

            if (y < 15) {
                int iar = checkDown(y * 20 + x, player);
                if (iar == 5 || iar == 10) {
                    return true;
                }
            }
            if (x < 15) {
                int iar = checkRight(y * 20 + x, player);
                if (iar == 5 || iar == 10) {
                    return true;
                }
            }
            if (y < 15 && x < 15) {
                int iar = checkDownRight(y * 20 + x, player);
                if (iar == 5 || iar == 10) {
                    return true;
                }
            }
            if (y >= 4 && x < 15) {
                int iar = checkUpRight(y * 20 + x, player);
                if (iar == 5 || iar == 10) {
                    return true;
                }
            }
        }
    }
    return false;
}

int Board::checkDown(int i, int player) {
    int val = field[i];
    if (val != player) {return 0;}
    return checkDown(i + 20, player) + val;
}

int Board::checkRight(int i, int player) {
    int val = field[i];
    if (val != player) {return 0;}
    return checkRight(i + 1, player) + val;
}

int Board::checkDownRight(int i, int player) {
    int val = field[i];
    if (val != player) {return 0;}
    return checkDownRight(i + 21, player) + val;
}

int Board::checkUpRight(int i, int player) {
    int val = field[i];
    if (val != player) {return 0;}
    return checkUpRight(i - 19, player) + val;
}

vector<int> Board::getLegalMoves(){
    vector<int> legalMoves = vector<int>();
    int move;
    for (int y = 0; y<20; y++) {
        for (int x = 0; x<20; x++) {
            move = getMoveID(x, y);
            if(field[move] == 0){
                legalMoves.push_back(move);
            }
        }
    }
    return legalMoves;
};

void Board::makeMove(int move, int player){
    if(!isLegal(move)){
        cout << "BotError: Tried to make illegal move\n";
        return;
    }
    field[move] = player;
    return;
};

void Board::undoMove(int move){
    if(isLegal(move)){
        cout << "BotError: Tried to make illegal move\n";
        return;
    }
    field[move] = 0;
    return;
};