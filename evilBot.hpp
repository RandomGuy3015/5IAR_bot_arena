#include <vector>
#include "bot.hpp"
using namespace std;



class EvilBot {
    public:
        EvilBot(vector<int> _field);

        int nextMove();
        vector<int> field;

    private:
        vector<short> getSortedMeaningfulLegalMoves();

        Bot bot;
};