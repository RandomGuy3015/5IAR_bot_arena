#include <iostream>
#include <tuple>
#include <vector>
#include "board.hpp"
using namespace std;

class WhatsThePlanBot {
    public:
        WhatsThePlanBot(){};

        int nextMove(Board board) {
            int x = -1;
            int y = -1;
            while (!board.isLegal(board.getMoveID(x, y)))
            {
                cout << "Whats the plan boss?\nx: ";
                cin >> x;
                cout << "y: ";
                cin >> y;
                cout << "\n";
            }
            return board.getMoveID(x, y);
        }
};