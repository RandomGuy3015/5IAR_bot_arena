#include "5IAR.hpp"
#include "statsTracker.hpp"
#include "board.hpp"

#include "whatsThePlanBot.hpp"
#include "myBot.hpp"
#include "evilBot.hpp"
#include "superEvilBot.hpp"

#include <vector>
#include <cstdio>
#include <chrono>
#include <iostream>
using namespace std;

Board board;

void runGame() {
    SuperEvilBot myBot = SuperEvilBot();
    string myBot_name = "MyBot";

    EvilBot evilBot = EvilBot();
    string evilBot_name ="EvilBot";
    
    StatsTracker mb_statsTracker = StatsTracker(myBot_name);
    StatsTracker eb_statsTracker = StatsTracker(evilBot_name);


    board = Board();

    const int time_to_play = 1 * 1000;
    // const float time_per_turn = 0.001;

    unsigned long long start_time = time();
    unsigned long long end_time = start_time + time_to_play;

    unsigned long long start_turn;
    unsigned long long end_turn;

    bool swap_starting_bot = false;
    bool swap_place = false;

    auto nextMove = [&myBot, &evilBot, &swap_place](Board board)-> int{
        return swap_place? evilBot.nextMove(board): myBot.nextMove(board);
    };

    auto statsTracker = [&mb_statsTracker, &eb_statsTracker, &swap_place](StatisticIndex i)-> double&{
        return swap_place? eb_statsTracker[i] : mb_statsTracker[i];
    };

    while (time() < end_time) {

        int isMate = false;
        while(!isMate) {
            // mybot move
            start_turn = time();
            int my_bot_move = -1;
            try{
                my_bot_move = nextMove(board);
            } catch(const std::exception& e){
                std::cerr << e.what() << '\n';
            }
            end_turn = time();
            statsTracker(play_time) += (double) end_turn - start_turn;
            statsTracker(turns)++;
            if (!board.isLegal(my_bot_move)){
                cout << "Illegal move: " << mb_statsTracker.bot_name << "\n";
                statsTracker(wins)++;
                statsTracker(illegal_moves)++;
                isMate = true;
                break;
            }
            board.makeMove(my_bot_move, 1);
            isMate = board.isMate();
            statsTracker(wins) += (int) isMate;
            swap_place = !swap_place;
        }
        // reset
        board.reset();
        swap_starting_bot = !swap_starting_bot;
        swap_place = swap_starting_bot;
    }
    if (myBot_name.length() < evilBot_name.length()){
        printStats(eb_statsTracker, mb_statsTracker);
    } else {
        printStats(mb_statsTracker, eb_statsTracker);
    }
}

unsigned long long time() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}