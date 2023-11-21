#include <vector>
#include "board.hpp"
using namespace std;

void runGame();

unsigned long long time();

class StatsTracker {
    public:
        StatsTracker() : my_bot_wins(0), evil_bot_wins(0), my_bot_illegal_moves(0), evil_bot_illegal_moves(0){};

        float myBotWR() {
            return my_bot_wins / (my_bot_wins + evil_bot_wins) / 100;
        }

        void incWin(int win_value) {
            if (win_value == 5) {
                my_bot_wins++;
            }
            else if (win_value == 10) {
                evil_bot_wins++;
            }
        }

        int my_bot_wins;
        int evil_bot_wins;
        int my_bot_illegal_moves;
        int evil_bot_illegal_moves;
};