#include "myBot.hpp"
#include "board.hpp"

#include <iostream>
#include <tuple>

int MyBot::nextMove(Board board) {
    // ################ HERE GOES YOUR CODE #####################
    int x = -1;
    int y = -1;
    while (!board.isLegal(board.getMoveID(x, y)))
    {
        cout << "Whats the plan boss?\n";
        cout << "x: ";
        cin >> x;
        cout << "y: ";
        cin >> y;
        cout << "\n";
    }
    
    return board.getMoveID(x, y);
}
