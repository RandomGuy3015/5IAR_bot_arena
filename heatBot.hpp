#include <vector>
#include <string>
#include "board.hpp"
using namespace std;



class HeatBot {
    public:
        HeatBot(){};

        int nextMove(Board _board);

    private:
        int drill(int i, int player, int direction, int depth);

        int heat(int i);

        Board board;

};