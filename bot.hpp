#include <vector>
using namespace std;

class GameState {
    public:
        GameState(vector<int> _field) : field(_field) {initBots();};

    private:
        void initBots() {
        }

        vector<int> field;
};

int move(const int x, const int y);