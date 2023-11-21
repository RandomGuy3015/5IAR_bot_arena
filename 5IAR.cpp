#include "5IAR.hpp"
#include "myBot.hpp"
#include "evilBot.hpp"
#include "board.hpp"
#include <vector>
#include <cstdio>
#include <chrono>
#include <iostream>
using namespace std;

StatsTracker statsTracker;
Board board;

void runGame() {
    EvilBot evilBot = EvilBot();
    MyBot myBot = MyBot();

    statsTracker = StatsTracker();
    board = Board();


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
                currentWinState = board.isMate();
                cout << currentWinState << endl;
            }
            else {
                printf("Illegal move: MyBot\n");
                currentWinState = 2;
            }
            if (currentWinState != 0) {
                break;
            }
            
            // evilBot move
            int evil_bot_move = evilBot.nextMove(board);
            if (board.isLegal(evil_bot_move)) {
                board.makeMove(evil_bot_move, 2);
                board.print();
                currentWinState = board.isMate();
                cout << currentWinState << endl;
            }
            else {
                printf("Illegal move: EvilBot\n");
                currentWinState = 1;
            }
        }
        printf("Somebody won! Yay!");
        statsTracker.incWin(currentWinState * 5);
        
        // reset
        board.reset();
        currentWinState = 0;
    }
}

unsigned long long time() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}