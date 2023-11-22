#include "5IAR.hpp"
#include "myBot.hpp"
#include "evilBot.hpp"
#include "superEvilBot.hpp"
#include "board.hpp"
#include "whatsThePlanBot.hpp"

#include <vector>
#include <cstdio>
#include <chrono>
#include <iostream>
using namespace std;

StatsTracker statsTracker;
Board board;

void runGame() {
    SuperEvilBot evilBot = SuperEvilBot();
    EvilBot myBot = EvilBot();

    statsTracker = StatsTracker();
    board = Board();

    const int time_to_play = 2 * 1000;
    const float time_per_turn = 0.001;

    unsigned long long start_time = time();
    unsigned long long end_time = start_time + time_to_play;
    unsigned long long start_turn;
    unsigned long long end_turn;

    int currentWinState = 0;

    while (time() < end_time) {

        while(currentWinState == 0) {
            // mybot move
            start_turn = time();
            int my_bot_move = -1;
            try{
                my_bot_move = myBot.nextMove(board);
            } catch(const std::exception& e){
                std::cerr << e.what() << '\n';
            }
            end_turn = time();
            statsTracker[mb_time] += (double) end_turn - start_turn;
            statsTracker[mb_turns]++;
            if (!board.isLegal(my_bot_move)){
                printf("Illegal move: MyBot\n");
                statsTracker[eb_wins]++;
                statsTracker[mb_illegal_moves]++;
                currentWinState = 2;
                break;
            }
            board.makeMove(my_bot_move, 1);
            currentWinState = board.isMate();
            if (currentWinState == 1) {
                statsTracker[mb_wins]++;
                break;
            }

            // evilBot move
            start_turn = time();
            int evil_Bot_move = -1;
            try{
                evil_Bot_move = evilBot.nextMove(board);
            } catch(const std::exception& e){
                std::cerr << e.what() << '\n';
            }
            end_turn = time();
            statsTracker[eb_time] += (double) end_turn - start_turn;
            statsTracker[eb_turns]++;
            if (!board.isLegal(evil_Bot_move)){
                printf("Illegal move: MyBot\n");
                statsTracker[mb_wins]++;
                statsTracker[eb_illegal_moves]++;
                currentWinState = 1;
                break;
            }
            board.makeMove(evil_Bot_move, 2);
            currentWinState = board.isMate();
            if (currentWinState == 2) {
                statsTracker[eb_wins]++;
                break;
            }
        }
        board.print();
        printf("Player %d won! Yay!\n", currentWinState);
        
        // reset
        board.reset();
        currentWinState = 0;
    }
    cout << statsTracker;
}

unsigned long long time() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

ostream& operator<<(ostream& os, const StatsTracker &st){
    os << "############### STATS ############## \n";
    os << "#                "<< "MyBot"                   <<" \t EvilBot   "    <<                     "#\n"; 
    os << "#          wins: "<< (int) st[mb_wins]         <<" \t "<< (int) st[eb_wins] <<         "\t   #\n";
    os << "#      win rate: "<< (int) (st.myBotWR() * 100)<<"%\t "<< (int) (st.evilBotWR() * 100)<<"%\t   #\n";
    os << "# illegal moves: "<< (int) st[mb_illegal_moves]<<" \t "<< (int) st[eb_illegal_moves]<< "\t   #\n";
    os << "# time per move: "<< (int) st[mb_time]         <<"ms\t "<<(int) st[eb_time] <<       "ms\t   #\n";
    os << "#################################### \n";
    return os;
}