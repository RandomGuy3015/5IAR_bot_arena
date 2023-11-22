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


    int time_to_play = -1;
    float time_per_turn = 0.001;

    unsigned long long start_time = time();
    unsigned long long end_time = start_time + time_to_play;

    int currentWinState = 0;

    while (time() < end_time) {

        while(currentWinState == 0) {
            // mybot move 
            int my_bot_move = myBot.nextMove(board);
            if (!board.isLegal(my_bot_move)) {
                printf("Illegal move: MyBot\n");
                statsTracker.incIllegal(1);
                currentWinState = 2;
                break;
            }
            board.makeMove(my_bot_move, 1);
            board.print();
            currentWinState = board.isMate();
    
            if (currentWinState != 0) {break;}
            
            // evilBot move
            int evil_bot_move = evilBot.nextMove(board);
            if (!board.isLegal(evil_bot_move)) {
                printf("Illegal move: EvilBot\n");
                currentWinState = 1;
                statsTracker.incIllegal(2);
                break;
            }
            board.makeMove(evil_bot_move, 2);
            board.print();
            currentWinState = board.isMate();
        }
        printf("Player %d won! Yay!\n", currentWinState);
        statsTracker.incWin(currentWinState);
        
        // reset
        board.reset();
        currentWinState = 0;
    }
    statsTracker.evil_bot_wins = 13;
    statsTracker.my_bot_wins = 28;
    cout << statsTracker;
}

unsigned long long time() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

ostream& operator<<(ostream& os, const StatsTracker &st){
    os << fixed << setprecision(2);
    os << "################### STATS ###################" <<                                  "\n";
    os << "               "<< "MyBot"                 <<" \t EvilBot    "<<                   "\n"; 
    os << "         wins: "<< st.my_bot_wins          <<" \t "<< st.evil_bot_wins <<          "\n";
    os << "     win rate: "<< st.myBotWR() * 100      <<"%\t "<< (1 - st.myBotWR()) * 100 << "%\n";
    os << "illegal moves: "<< st.my_bot_illegal_moves <<" \t "<< st.evil_bot_illegal_moves << "\n";
    os << "#############################################"  <<                                 "\n";
    return os;
}