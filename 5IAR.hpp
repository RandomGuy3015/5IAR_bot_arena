#ifndef FIAR_H
#define FIAR_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <map>

#include "board.hpp"

using namespace std;

void runGame();

unsigned long long time();

enum StatisticIndex {
    mb_wins,
    mb_illegal_moves,
    mb_out_of_time,
    mb_turns,
    mb_time,
    eb_wins,
    eb_illegal_moves,
    eb_out_of_time,
    eb_turns,
    eb_time
};

class StatsTracker {
public:
    StatsTracker(): stats({{mb_wins, 0},{mb_illegal_moves, 0},{mb_out_of_time, 0}, {mb_turns, 0}, {eb_wins, 0},
        {eb_illegal_moves, 0},{eb_out_of_time, 0}, {eb_turns, 0}, {mb_time, 0}, {eb_time, 0}}), wrongIndexDummy(69) {}

    double myBotWR() const {
        if (stats.at(mb_wins) + stats.at(eb_wins) == 0 || stats.at(mb_wins) == 0){return 0;}
        return stats.at(mb_wins) / (stats.at(mb_wins) + stats.at(eb_wins));
    }

    double evilBotWR() const {
        if (stats.at(mb_wins) + stats.at(eb_wins) == 0 || stats.at(eb_wins) == 0){return 0;}
        return stats.at(eb_wins) / (stats.at(mb_wins) + stats.at(eb_wins));
    }

    double& operator[](StatisticIndex i) {
        if (stats.find(i) == stats.end()) {
            std::cerr << "Invalid statistic index\n";
            return wrongIndexDummy;
        }
        return stats[i];
    }

    double operator[](StatisticIndex i) const{
        if (stats.find(i) == stats.end()) {
            std::cerr << "Invalid statistic index\n";
            return 0;
        } else if (i == mb_time){return stats.at(i) / stats.at(mb_turns) * 100;
        } else if (i == eb_time){return stats.at(i) / stats.at(eb_turns) * 100;}
        return stats.at(i);
    }
private:
    std::map<StatisticIndex, double> stats;
    double wrongIndexDummy;
};

ostream& operator<<(ostream& os, const StatsTracker &st);

#endif // FIAR_H