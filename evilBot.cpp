#include "evilBot.hpp"
#include "board.hpp"
#include <map>
#include <cstdio>
#include <algorithm>

int EvilBot::nextMove(Board board) {
    // ################ HERE GOES YOUR CODE #####################
    vector<short> sortedMoves = getSortedMeaningfulLegalMoves(board);



    if (sortedMoves.empty()){
        return board.getMoveID(10, 10);
    }
    else {
        return sortedMoves[0];
    }
}

vector<short> EvilBot::getSortedMeaningfulLegalMoves(Board board) {
    vector<pair<short, short>> moves = vector<pair<short, short>>();
    for (short i = 0; i < 20*20; i++) { int sum = 0;
        auto f = [](short y) -> short {return (int) y == 2;};
        if (board[i] != 0) {if (board[i] == 1) {printf("\033[1;32m O\033[0m");} 
        else {printf("\033[1;31m O\033[0m");};  continue; }
        if (i > 19 && i < 380 && i % 20 > 0 && i % 20 < 19) {
            pair<short, short> forcedMove = getForcedMove(&board, i, 1);
            if (forcedMove.first > 0) {moves.push_back(forcedMove);}
            sum = f(board[i-20]) + f(board[i+20]) + f(board[i-1]) + f(board[i+1]) + f(board[i + 21]) 
                         + f(board[i + 19]) + f(board[i - 21]) + f(board[i - 19]);
        }
        if (i%20 == 0) {printf("\n");};
        printf("% d", sum);
        if (sum > 0) {
            pair<short, short> moveValue = getForcedMove(&board, i, 2);
            moves.push_back(pair<short, short>((3 * sum + 2 * moveValue.first) / 4, i));
        }
    }
    printf("\n");
    sort(moves.begin(), moves.end(), [](pair<short, short> x, pair<short, short> y){return x.first > y.first;});

    vector<short> out = vector<short>();

    for (int i = 0; i < moves.size(); i++) {
        printf("\n %d : %d %d ", moves[i].first, moves[i].second % 20, moves[i].second / 20);
        out.push_back(moves[i].second);
    }
    return out;
}

pair<short, short> EvilBot::getForcedMove(Board* pBoard, short i, short p) {
    if (i % 20 == 0 || i % 20 == 19 || i < 20 || i > 379){return pair<short, short>(0, i);}
    pBoard->makeMove((int)i, p);
    int sum = pBoard->countIAR(i, p, 20);
    sum = max(sum, pBoard->countIAR(i, p, -20));
    sum = max(sum, pBoard->countIAR(i, p, 1));
    sum = max(sum, pBoard->countIAR(i, p, -1));
    sum = max(sum, pBoard->countIAR(i, p, 21));
    sum = max(sum, pBoard->countIAR(i, p, 19));
    sum = max(sum, pBoard->countIAR(i, p, -21));
    sum = max(sum, pBoard->countIAR(i, p, -19));
    pBoard->undoMove((int)i);
    return pair<short,short>(sum - 1, i);
}

void EvilBot::print(int i) {
    printf(" %d\n", i);
}
void EvilBot::print(short i) {
    printf(" %d\n", i);
}
void EvilBot::print(string s) {
    printf(" %s\n", s);
}
void EvilBot::print(int i, int j) {
    printf(" %d %d\n", i, j);
}