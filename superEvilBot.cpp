#include "superEvilBot.hpp"
#include "board.hpp"
#include <map>
#include <cstdio>
#include <random>
#include <iostream>

int SuperEvilBot::nextMove(Board board) {
    // ################ HERE GOES YOUR CODE #####################
    vector<int> moves = board.getLegalMoves();
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, moves.size() - 1); // define the range
    int best_move = moves[distr(gen)];
    float best_score = 0.6;
    for (int move : moves){
        float sum = 0;
        for (int player : vector<int>({1, 2})){
            board.makeMove(move, player);
            int score1 = board.countIAR(move, player, 20) + board.countIAR(move, player, -20) - 2;
            int score2 = board.countIAR(move, player, 1 ) + board.countIAR(move, player, -1 ) - 2;
            int score3 = board.countIAR(move, player, 21) + board.countIAR(move, player, -21) - 2;
            int score4 = board.countIAR(move, player, 19) + board.countIAR(move, player, -19) - 2;
            board.undoMove(move);
            if (score1 >= 4 || score2 >= 4 || score3 >= 4 || score4 >= 4){
                return move;
            }
            sum += score1 + score2 +score3 + score4;
            sum += board.getPlayer() == player? 0.5 : 0;
        }
        if (sum > best_score){
            best_score = sum;
            best_move = move;
        }
        sum = 0;
    }
    return best_move;
}