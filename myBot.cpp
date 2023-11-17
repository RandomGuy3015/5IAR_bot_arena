#include "myBot.hpp"
#include "bot.hpp"

int example()  {
    return 10;
}

MyBot::MyBot(vector<int> _field) {
    field = _field;
    bot = Bot();
}

int MyBot::nextMove() {
            // ################ HERE GOES YOUR CODE #####################
            return bot.getMoveID(10, 10);
        }
