#include <vector>
#include <string>
#include "board.hpp"
using namespace std;



class EvilBot {
    public:
        EvilBot(){};

        int nextMove(Board board);

        vector<short> getSortedMeaningfulLegalMoves(Board board);

        pair<short, short> getForcedMove(Board* pBoard, short i, short p);
    private:
        void print(int i);
        void print(short i);
        void print(string s);
        void print(int i, int j);
};