#include "evilBot.hpp"
#include "bot.hpp"


EvilBot::EvilBot(vector<int> _field) {
    field = _field;
    bot = Bot();
}

int EvilBot::nextMove() {
            // ################ HERE GOES YOUR CODE #####################
            return bot.getMoveID(10, 10);
        }
