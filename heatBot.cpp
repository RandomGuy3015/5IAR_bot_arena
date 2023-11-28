#include "heatBot.hpp"
#include "board.hpp"
#include <cstdio>
#include <random>
#include <iostream>
using namespace std;


int HeatBot::nextMove(Board _board) {
    board = _board;
    int player = _board.getPlayer();
    int e_b = heat(player);

    printf("% d %d", player, e_b);
    
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(1, 19);

    int a = uni(rng) + uni(rng) * 20;
    while (!_board.isLegal(a)) { a = uni(rng) + uni(rng) * 20;}
    return a;
}


int HeatBot::heat(int player) {
    int celsius = 0;
    vector<int> v{-20, 20, 1, -1, 21, 19, -21, -19};
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 20; y++) {
            if (x == 19 || y == 19) { continue;}
            for (int d : v) {
                int us = max(drill(x + y * 20, player, d, 4), 0);
                int them = max(drill(x + y * 20, abs(player - 3), d, 4), 0);
                celsius += (us - them);
            }
        }
    }
    return celsius;
}


int HeatBot::drill(int i, int player, int direction, int depth) {
    int heat = 1;
    if (i % 20 == 0 || i % 20 == 19 || i < 20 || i > 379) {
        if (board[i] == player) { return 0;}
        else { return -2;}
    }
    else if (board[i] != player) {
        if (board[i] != 0) { heat -= 1;}
        if (depth == 4) { return 0;}
    }
    if (depth == 0) { return heat;}
    return drill(i + direction, player, direction, depth - 1) + heat;
}
