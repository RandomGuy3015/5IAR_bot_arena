#include <vector>
#include "board.hpp"
using namespace std;



class EvilBot {
    public:
        EvilBot(){};

        int nextMove(Board board);

        vector<short> getSortedMeaningfulLegalMoves(Board board);
};