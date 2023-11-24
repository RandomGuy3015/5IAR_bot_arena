#ifndef STATS_H
#define STATS_H

#include <map>

#include "board.hpp"

enum StatisticIndex {
    wins,
    illegal_moves,
    out_of_time,
    turns,
    play_time,
};

class StatsTracker {
public:
    string bot_name;

    StatsTracker(string _name): bot_name(_name), stats({{wins, 0},{illegal_moves, 0},{out_of_time, 0}, {turns, 0}, {play_time, 0}}), wrongIndexDummy(69) {}

    double myBotWR(StatsTracker other) const;

    double& operator[](StatisticIndex i);

    double operator[](StatisticIndex i) const;
private:
    std::map<StatisticIndex, double> stats;
    double wrongIndexDummy;
};

void printStats(const StatsTracker, const StatsTracker);

string pad(int x, string s);
string pad(int x, int s);
string pad(int x, double s);

#endif