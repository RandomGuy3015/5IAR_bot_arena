#include <vector>
#include "bot.hpp"
using namespace std;



class EvilBot {
    public:
        EvilBot(vector<int> _field);

        int nextMove();

    private:
        vector<int> field;
        Bot bot;
};