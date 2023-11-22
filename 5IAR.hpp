#ifndef FIAR_H
#define FIAR_H

#include <vector>
#include <iostream>
#include <iomanip>

#include "board.hpp"

using namespace std;

void runGame();

unsigned long long time();

class StatsTracker {
    public:
        StatsTracker() : my_bot_wins(0), evil_bot_wins(0), my_bot_illegal_moves(0), evil_bot_illegal_moves(0){};

        float myBotWR() const {
            if (my_bot_wins + evil_bot_wins == 0){return 0;}
            return (float) my_bot_wins / (float) (my_bot_wins + evil_bot_wins);
        }

        void incWin(int player) {
            if (player == 1) {my_bot_wins++;}
            else if (player == 2) {evil_bot_wins++;}
        }

        void incIllegal(int player){
            if (player == 1) {my_bot_illegal_moves++;}
            else if (player == 2) {evil_bot_illegal_moves++;}
        }

        int my_bot_wins;
        int evil_bot_wins;
        int my_bot_illegal_moves;
        int evil_bot_illegal_moves;
};

ostream& operator<<(ostream& os, const StatsTracker &st);

#endif // FIAR_H