#include "5IAR.hpp"
#include "myBot.hpp"
#include <vector>
#include <cstdio>
using namespace std;

vector<int> field;

void runGame() {
    setupGame();
}

void setupGame() {

    for (int i = 0; i < 20*20; i++) {
        field.push_back(0);
    }
    printField(field);
}

void printField(vector<int> field) {
    for (int y = 0; y<20; y++) {
        for (int x = 0; x<20; x++) {
            printf("+ ");
        }
        printf("\n");
    }
}