#include "myBot.hpp"
#include "bot.hpp"

#include <iostream>
#include <tuple>

MyBot::MyBot(vector<int> _field) {
    field = _field;
    bot = Bot();
}

int MyBot::nextMove() {
    // ################ HERE GOES YOUR CODE #####################
    tuple<int, int> pos = tuple<int, int>(-1, -1);
    while (!bot.isLegal(field, pos))
    {
        cout << "Whats the plan boss?\n";
        cout << "x: ";
        cin >> get<0>(pos);
        cout << "y: ";
        cin >> get<1>(pos);
        cout << "\n";
    }
    
    return bot.getMoveID(pos);
}
