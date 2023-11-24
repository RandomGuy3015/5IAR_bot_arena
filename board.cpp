#include "board.hpp"
#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
using namespace std;

void Board::reset(){
    field = vector<int>(400);
    moveCount = 0;
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

bool Board::isMate() {
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {

            int player = field[y * 20 + x];

            if (player == 0) {continue; }

            // 1: down, 2: right, 3: downright, 4. downleft
            if (y < 16) {
                if (countIAR(y * 20 + x, player, 20) >= 5) {return true;}
            }
            if (x < 16) {
                if (countIAR(y * 20 + x, player, 1) >= 5) {return true;}
            }
            if (y < 16 && x < 16) {
                if (countIAR(y * 20 + x, player, 21) >= 5) {return true;}
            }
            if (x > 3 && y < 16) {
                if (countIAR(y * 20 + x, player, 19) >= 5) {return true;}
            }
        }
    }
    return false;
}

int Board::countIAR(int i, int player, int direction) {
    if (i < 0 || i > 399) {return 0;}
    if (field[i] != player) {return 0;}
    if (abs(floor(i / 20) - floor((i + direction)/ 20)) > 1 || abs(i % 20 - (i + direction) % 20) > 1){return 1;}
    return countIAR(i + direction, player, direction) + 1;
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
    moveCount++;
    return;
};

void Board::undoMove(int move){
    if(isLegal(move)){
        cout << "BotError: Tried to make illegal move\n";
        return;
    }
    field[move] = 0;
    moveCount--;
    return;
};

int& Board::operator[](int move){
    return field[move];
}

void Board::print() {
    auto scaleToPattern = [](int x) -> int {return (int)(x + 17)/18;};
    const char* pattern[] = 
    {
        "┌─", "┬─" ,"┐ " , 
        "├ ", "+ ", "┤ ", 
        "└─", "┴─", "┘ ",
        "\b \033[1;32mO\033[0m ",
        "\b \033[1;31mO\033[0m "
    };

    printf("\n0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9\n");
    for (int y = 0; y<20; y++) {
        for (int x = 0; x<20; x++) {
            int player = field[y * 20 + x];
            if (player == 0){
                printf("%s", pattern[scaleToPattern(y) * 3 + scaleToPattern(x)]);
                continue;
            }
            printf("%s", pattern[player + 8]);
        }
        printf(" %d\n", y);
    }
}
