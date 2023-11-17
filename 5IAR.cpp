#include "5IAR.hpp"
#include "myBot.hpp"
#include <vector>
#include <cstdio>
#include <chrono>
using namespace std;

vector<int> field;
vector<int> dots;

void runGame() {
    setupGame();
    MyBot myBot = MyBot(field);

    int time_to_play = 1;
    float time_per_turn = 0.001;

    unsigned long long start_time = time();
    unsigned long long end_time = start_time + 10000;

    while (start_time < end_time) {

        while(checkAndUpdateWins() == false) {
            int my_bot_move = myBot.nextMove();
            // logic
            if (isLegalMove(my_bot_move)) {
                field[my_bot_move] = 1;
                dots.push_back(my_bot_move);
                // for evilBot do (1 << 9 + evil_bot_move)
            }
        }
        setupGame();
    }

}  // don't think dots are needed - recursive method with some fancy stuff should be more efficient.

void setupGame() {

    field.clear();
    dots.clear();

    for (int i = 0; i < 20*20; i++) {
        field.push_back(0);
    }
    dots.reserve(sizeof(int) * 20*20);

    printField(field);
}

bool checkAndUpdateWins() {
    for (int i=0; i < dots.size(); i++) {
    }
    return true;
}


bool isLegalMove(int myBotMove) {
    if (field[myBotMove] == 0) {
        return true;
    }
    else {
        return false;
    }
}

unsigned long long time() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void printField(vector<int> field) {
    for (int y = 0; y<20; y++) {
        for (int x = 0; x<20; x++) {
            if (x == 0 and y == 0) {
                printf("┌─");
            }
            else if (x == 0 and y == 19) {
                printf("└─");
            }
            else if (x == 0) {
                printf("├ ");
            }
            else if (x == 19 and y == 0) {
                printf("┐ ");
            }
            else if (x == 19 and y == 19) {
                printf("┘ ");
            }
            else if (x == 19) {
                printf("┤ ");
            }
            else if (y == 0) {
                printf("┬─");
            }
            else if (y == 19) {
                printf("┴─");
            }
            else {
                printf("+ ");
            }
        }
        printf("\n");
    }
}