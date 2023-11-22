#include "superEvilBot.hpp"
#include "board.hpp"
#include <map>
#include <cstdio>

int SuperEvilBot::nextMove(Board board) {
    // ################ HERE GOES YOUR CODE #####################
    if(board.moveCount == 0){
        return board.getMoveID(10, 10);
    }
    vector<int> moves = board.getLegalMoves();
    int best_move = moves[moves.size()];
    int best_score = 0;
    for (int move : moves){
        for (int player : vector<int>({1, 2})){
            board.makeMove(move, player);
            int score1 = board.countIAR(move, player, 20) + board.countIAR(move, player, -20);
            int score2 = board.countIAR(move, player, 1 ) + board.countIAR(move, player, -1 );
            int score3 = board.countIAR(move, player, 21) + board.countIAR(move, player, -21);
            int score4 = board.countIAR(move, player, 19) + board.countIAR(move, player, -19);
            board.undoMove(move);
            if (score1 >= 5 || score2 >= 5 || score3 >= 5 || score4 >= 5){
                return move;
            }
            float sum = score1 + score2 +score3 + score4 - player + 1.5;
            if (sum > best_score){
                best_score = sum;
                best_move = move;
            }
        }
    }
    return best_move;
}