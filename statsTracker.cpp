#include <iostream>
#include <map>
#include <algorithm>
#include <math.h>

#include "board.hpp"
#include "statsTracker.hpp"

string pad(int x, string s){
    while ((int)s.length() > x){
        s.pop_back();
    }
    string out;
    out.append(x - s.length(), ' ');
    return out.append(s);
}

string pad(int x, double y){
    return pad(x, to_string((int) round(y)));
}

double StatsTracker::myBotWR(StatsTracker other) const {
    if (stats.at(wins) + other[wins] == 0 || stats.at(wins) == 0){return 0;}
    return stats.at(wins) / (stats.at(wins) + other[wins]);
}

double& StatsTracker::operator[](StatisticIndex i) {
    return stats[i];
}

double StatsTracker::operator[](StatisticIndex i) const{
    if (i == play_time){return stats.at(i) / stats.at(turns) * 100;}
    return stats.at(i);
}

void printStats(const StatsTracker self, const StatsTracker other){
    int len1 = max(6, (int) self.bot_name.length() - 10);
    int len2 = max(6, (int) other.bot_name.length() - 1);
    string out;
    cout << out.append(7 + len1, '#')<<      " STATS "     ;out.clear();cout  << out.append(len2 + 8, '#')            <<     "\n";
    cout << "#      "          << pad(len1 + 10, self.bot_name)       << "  " << pad(len2 + 1, other.bot_name)        <<   " #\n"; 
    cout << "#          wins:" << pad(len1, self[wins])               << "  " << pad(len2, other[wins])               << "   #\n";
    cout << "#      win rate:" << pad(len1, self.myBotWR(other) * 100)<< "% " << pad(len2, other.myBotWR(self) * 100) << "%  #\n";
    cout << "# illegal moves:" << pad(len1, self[illegal_moves])      << "  " << pad(len2, other[illegal_moves])      << "   #\n";
    cout << "# time per move:" << pad(len1, self[play_time])          << "ms" << pad(len2, other[play_time])          << "ms #\n";
    cout << out.append(len1 + 14, '#')                                                                                <<     "\n";
}