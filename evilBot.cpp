#include "evilBot.hpp"
#include "bot.hpp"
#include <map>
#include <cstdio>



EvilBot::EvilBot(vector<int> _field) {
    field = _field;
    bot = Bot();
}

int EvilBot::nextMove() {
    // ################ HERE GOES YOUR CODE #####################
    vector<short> sortedMoves = getSortedMeaningfulLegalMoves();
    if (sortedMoves.empty()){
        return bot.getMoveID(10, 10);
    }
    else {
        return sortedMoves[0];
    }
}

vector<short> EvilBot::getSortedMeaningfulLegalMoves() {
    map<short, short> moves = map<short, short>();
    for (short i = 0; i < 20*20; i++) {
        int sum = 0;
        auto f = [](short y) -> short {return (int) y == 2;};
        if (field[i] != 0) {printf("\033[1;32m O\033[0m"); continue;}
        if (i > 19 && i < 380 && i % 20 > 0 && i % 20 < 19) {
            sum = f(field[i-20]) + f(field[i+20]) + f(field[i-1]) + f(field[i+1]) + f(field[i + 21]) 
                         + f(field[i + 19]) + f(field[i - 21]) + f(field[i - 19]);
        }
        if (i%20 == 0) {printf("\n");};
        printf("% d", sum);
        if (sum > 0) {
            moves.insert(pair<short, short>(sum, i));
        }
    }
    vector<short> out = vector<short>();
    for (map<short, short>::iterator it = moves.begin(); it != moves.end(); it++) {
        out.push_back(it->second);
        printf("\n%d : x= %d  y= %d\n", it->first, it->second%20, it->second/20);
    }
    return out;
}

/*

2 0   0
2 1   0
2 2   2

*/