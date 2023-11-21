#include "5IAR.hpp"
#include "myBot.hpp"
#include "evilBot.hpp"
#include "board.hpp"
#include <vector>
#include <cstdio>
#include <chrono>
using namespace std;

StatsTracker statsTracker;
Board board = Board();

void runGame() {
    setupGame();

    EvilBot evilBot = EvilBot();
    MyBot myBot = MyBot();
    statsTracker = StatsTracker();


    int time_to_play = 1;
    float time_per_turn = 0.001;

    unsigned long long start_time = time();
    unsigned long long end_time = start_time + 10000;

    int currentWinState = 0;

    while (time() < end_time) {

        while(currentWinState == 0) {
            // mybot move 
            int my_bot_move = myBot.nextMove(board);
            if (board.isLegal(my_bot_move)) {
                board.makeMove(my_bot_move, 1);
                board.print();
            }
            else {
                printf("Illegal move: MyBot\n");
            }

            currentWinState = board.isMate();
            if (board.isMate() == 1) {
                statsTracker.incWin(5);
                break; 
            }
            
            // evilBot move
            int evil_bot_move = evilBot.nextMove(board);
            
            if (board.isLegal(evil_bot_move)) {
                board.makeMove(my_bot_move, 1);
                board.print();
            }
            else {
                printf("Illegal move: EvilBot\n");
            }
            currentWinState = board.isMate();
            if (board.isMate() == 2) {
                statsTracker.incWin(10);
                break; 
            }
        }
        printf("Somebody won! Yay!");

        setupGame();
    }
} 

void setupGame() {
    board.reset();
    board.print();
}

unsigned long long time() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}