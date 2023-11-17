#include <vector>
#ifndef BOT_H
#define BOT_H


using namespace std;

class Bot {
    public:
        Bot(){};

        
        int move(int x, int y) {
            return y * 20 + x;
        }

    private:
};

#endif
