#include "evilBot.hpp"
#include "board.hpp"
#include <map>
#include <cstdio>
#include <algorithm>
#include <random>


int EvilBot::nextMove(Board rk07_) {
    // ################ HERE GOES YOUR CODE #####################
    vector<short> sortedMoves = x0033p(rk07_);



    if (sortedMoves.empty()){
        random_device rd;
        mt19937 rng(rd());
        uniform_int_distribution<int> uni(1, 19);

        return rk07_.getMoveID(uni(rng), uni(rng));
    }
    else {
        return sortedMoves[0];
    }
}

vector<short> EvilBot::x0033p(Board rk07_) {
    bool prt = false; vector<pair<short, short>> moves = vector<pair<short, short>>();
    for (short i = 0; i < 20*20; i++) { int sum = 0; auto f = [](short y) -> short 
    {return (int) y == 2;}; if (rk07_[i] != 0) {if (rk07_[i] == 1) {if (prt) 
    {printf("\033[1;32m  O \033[0m");}} else {if (prt) {printf("\033[1;31m  O \033[0m");}}; 
    continue; } short saved = 0; if (i > 19 && i < 380 && i % 20 > 0 && i % 20 < 19) {
    pair<short, short> forcedMove = x021i(&rk07_, i, 1); forcedMove.first *= 2; 
    saved = forcedMove.first; if (forcedMove.first > 0) {moves.push_back(forcedMove);}
    sum = f(rk07_[i-20]) + f(rk07_[i+20]) + f(rk07_[i-1]) + f(rk07_[i+1]) + f(rk07_[i + 21]) 
    + f(rk07_[i + 19]) + f(rk07_[i - 21]) + f(rk07_[i - 19]); } else { saved = 0; } if (sum > 0) 
    { pair<short, short> moveValue = x021i(&rk07_, i, 2); moves.push_back(pair<short, short>
    ((sum + 2 * moveValue.first + saved) / 2, i)); if (moveValue.first == 5) {moves.push_back(
    pair<short, short>(100, i));} if (prt) {if (i%20 == 0) {printf("\n");}; printf("% d%d%d", sum, 
    moveValue.first, saved); } } else { if (prt) {if (i%20 == 0) {printf("\n");};
    printf("--%d ", saved);}}} if (prt) {printf("\n");} sort(moves.begin(), moves.end(), []
    (pair<short, short> x, pair<short, short> y){return x.first > y.first;}); vector<short> out = 
    vector<short>(); for (int i = 0; i < (int) moves.size(); i++) { if (prt) {printf("\n %d : %d %d ", 
    moves[i].first, moves[i].second % 20, moves[i].second / 20);} out.push_back(moves[i].second); }
    return out; } pair<short, short> EvilBot::x021i(Board* pBoard, short i, short p) { 
    if (i % 20 == 0 || i % 20 == 19 || i < 20 || i > 379){return pair<short, short>(0, i);}
    pBoard->makeMove((int)i, p); int sum = pBoard->countIAR(i, p, 20);  vector<short> v{-20, 
    1, -1, 21, 19, -21, -19}; for (short d : v) {sum = max(sum, pBoard->countIAR(i, p, d));} 
    pBoard->undoMove((int)i); return pair<short,short>(sum - 1, i);
}

void EvilBot::print(int i) {
    printf(" %d\n", i);
}
void EvilBot::print(short i) {
    printf(" %d\n", i);
}
void EvilBot::print(string s) {
    printf(" %s\n", s[0]);
}
void EvilBot::print(int i, int j) {
    printf(" %d %d\n", i, j);
}