#include <vector>
using namespace std;

void runGame();

void setupGame();

void printField(vector<int> field);

bool checkAndUpdateWins();

bool isLegalMove(int myBotMove);

unsigned long long time();

class StatsTracker {
    StatsTracker() : my_bot_wins(0), evil_bot_wins(0), my_bot_illegal_moves(0), evil_bot_illegal_moves(0){};

    float myBotWR() {
        return my_bot_wins / (my_bot_wins + evil_bot_wins) / 100;
    }

    int my_bot_wins;
    int evil_bot_wins;
    int my_bot_illegal_moves;
    int evil_bot_illegal_moves;
};