#include "5IAR.hpp"
#include "myBot.hpp"
#include "evilBot.hpp"
#include <vector>
#include <cstdio>
#include <chrono>
using namespace std;

vector<int> field;
StatsTracker statsTracker;
Bot bot = Bot();

void runGame() {
    setupGame();

    /*
    field[1] = 1;
    field[22] = 1;
    field[43] = 1;
    field[64] = 1;
    field[85] = 1;
    field[43] = 2;

    checkAndUpdateWins();

    printField(field);
    */
    MyBot myBot = MyBot(field);
    EvilBot evilBot = EvilBot(field);
    statsTracker = StatsTracker();


    int time_to_play = 1;
    float time_per_turn = 0.001;

    unsigned long long start_time = time();
    unsigned long long end_time = start_time + 10000;

    while (time() < end_time) {

        while(checkAndUpdateWins() == false) {
            int my_bot_move = myBot.nextMove();
            if (isLegalMove(my_bot_move)) {
                field[my_bot_move] = 1;
                evilBot.field[my_bot_move] = 1;
                // for evilBot do (1 << 9 + evil_bot_move)
                printField(field);
            }
            else {
                printf("Illegal move: MyBot\n");
            }

            if (checkAndUpdateWins() == true) {break; }

            int evil_bot_move = evilBot.nextMove();
            
            if (isLegalMove(evil_bot_move)) {
                field[evil_bot_move] = 2;
                evilBot.field[evil_bot_move] = 2;
                // for evilBot do (1 << 9 + evil_bot_move)
                printField(field);
            }
            else {
                printf("Illegal move: EvilBot\n");
            }
        }
        printf("Somebody won! Yay!");

        setupGame();
    }

}  //  recursive method with some fancy stuff should be more efficient.

void setupGame() {

    field.clear();

    for (int i = 0; i < 20*20; i++) {
        field.push_back(0);
    }

    printField(field);
}

bool checkAndUpdateWins() {
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {

            int color = field[y * 20 + x];

            if (color == 0) {continue; }

            if (y < 15) {
                int iar = checkDown(y * 20 + x, color);
                if (iar == 5 || iar == 10) {
                    statsTracker.incWin(iar);
                    return true;
                }
            }
            if (x < 15) {
                int iar = checkRight(y * 20 + x, color);
                if (iar == 5 || iar == 10) {
                    statsTracker.incWin(iar);
                    return true;
                }
            }
            if (y < 15 && x < 15) {
                int iar = checkDownRight(y * 20 + x, color);
                if (iar == 5 || iar == 10) {
                    statsTracker.incWin(iar);
                    printf("%d", iar);
                    return true;
                }
            }
            if (y >= 4 && x < 15) {
                int iar = checkUpRight(y * 20 + x, color);
                if (iar == 5 || iar == 10) {
                    statsTracker.incWin(iar);
                    return true;
                }
            }
        }
    }
    return false;
}

int checkDown(int i, int color) {
    int val = field[i];
    if (val != color) {return 0;}
    return checkDown(i + 20, color) + val;
}

int checkRight(int i, int color) {
    int val = field[i];
    if (val != color) {return 0;}
    return checkRight(i + 1, color) + val;
}

int checkDownRight(int i, int color) {
    int val = field[i];
    if (val != color) {return 0;}
    return checkDownRight(i + 21, color) + val;
}

int checkUpRight(int i, int color) {
    int val = field[i];
    if (val != color) {return 0;}
    return checkUpRight(i - 19, color) + val;
}


bool isLegalMove(int myBotMove) {
    if (field[myBotMove] == 0) {        return true;
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
    printf("0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9\n");
    for (int y = 0; y<20; y++) {
        for (int x = 0; x<20; x++) {
            if (field[y * 20 + x] == 1){
                printf("\b \033[1;32mO\033[0m ");
            }
            else if (field[y * 20 + x] == 2){
                printf("\b \033[1;31mO\033[0m ");
            }
            else if (x == 0 and y == 0) {
                printf("┌─");
            }
            else if (x == 0 and y == 19) {
                printf("└─");
            }
            else if (x == 0) {
                printf("├ ");
            }
            else if (x == 19 and y == 0) {
                printf("┐ 0");
            }
            else if (x == 19 and y == 19) {
                printf("┘ 19");
            }
            else if (x == 19) {
                printf("┤ %d", y);
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