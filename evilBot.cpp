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
    for (short i = 0; i < 20*20; i++) {
        int sum = 0;
        auto f = [](short y) -> short {return (int) y == 2;};
        if (board[i] != 0) {printf("\033[1;32m O\033[0m"); 
            continue;
        }
        if (i > 19 && i < 380 && i % 20 > 0 && i % 20 < 19) {
            pair<short, short> forcedMove = getForcedMove(&board, i);
            moves.push_back(forcedMove);
            sum = f(board[i-20]) + f(board[i+20]) + f(board[i-1]) + f(board[i+1]) + f(board[i + 21]) 
                         + f(board[i + 19]) + f(board[i - 21]) + f(board[i - 19]);
        }
        if (i%20 == 0) {printf("\n");};
        printf("% d", sum);
        if (sum > 0) {
            moves.push_back(pair<short, short>(sum, i));
        }
    }
    printf("\n");
    sort(moves.begin(), moves.end(), [](pair<short, short> x, pair<short, short> y){return x.first > y.first;});

    vector<short> out = vector<short>();

    for (int i = 0; i < moves.size(); i++) {
        printf("\n %d : %d ", moves[i].first, moves[i].second);
        out.push_back(moves[i].second);
    }
    return out;
}

pair<short, short> EvilBot::getForcedMove(Board* pBoard, short i) {
    if (i % 20 == 0 || i % 20 == 19 || i < 20 || i > 379){return pair<short, short>(0, i);}
    int sum = pBoard->countIAR(i % 20 + i / 20, 1, 20);
    sum = max(sum, pBoard->countIAR(i % 20 + i / 20, 1, -20));
    sum = max(sum, pBoard->countIAR(i % 20 + i / 20, 1, 1));
    sum = max(sum, pBoard->countIAR(i % 20 + i / 20, 1, -1));
    sum = max(sum, pBoard->countIAR(i % 20 + i / 20, 1, 21));
    sum = max(sum, pBoard->countIAR(i % 20 + i / 20, 1, 19));
    sum = max(sum, pBoard->countIAR(i % 20 + i / 20, 1, -21));
    sum = max(sum, pBoard->countIAR(i % 20 + i / 20, 1, -19));
    return pair<short,short>(sum, i);

}

/*

2 0   0
2 1   0
2 2   2

*/