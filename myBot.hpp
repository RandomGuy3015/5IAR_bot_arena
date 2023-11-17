#include <vector>
#include "bot.hpp"
using namespace std;


int example();

class MyBot {
    public:
        MyBot(vector<int> _field);

        int nextMove();

    private:
        vector<int> field;
        Bot bot;
};