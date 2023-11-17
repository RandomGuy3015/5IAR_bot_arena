#include <vector>
using namespace std;


int example();

class MyBot {
    public:
        MyBot(vector<int> _field) : field(_field) {};

        int nextMove() {
            // ################ HERE GOES YUR CODE #####################
            return move(10, 10);
        }
    private:
        vector<int> field;
};