#include <vector>
#include <string>
#include "board.hpp"
using namespace std;



class EvilBot {
    public:
        EvilBot(){};

        int nextMove(Board rk07_);

        vector<short> x0033p(Board rk07_);

        pair<short, short> x021i(Board* pBoard, short i, short p);
    private:
        void print(int i);
        void print(short i);
        void print(string s);
        void print(int i, int j);
};