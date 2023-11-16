#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include "p5.hpp"
#include <string>
#include <cstring>
#include <vector>
#define WHITE 16777215

// Your code goes here
Screen screen;

void background(const int color) {
    for (int i=0; i<screen.size*screen.size; i++) {
        screen.pixels[i] = color;
    }
}

void background(const int r, const int g, const int b) {
    int c = color(r, g, b);
    for (int i=0; i<screen.size*screen.size; i++) {
        screen.pixels[i] = c;
    }
}


// ################################# SHAPES ###################################


void circle(const int x, const int y, const int radius, const int color) {
    const int radius_squared = radius*radius;
    for (int i = x - radius; i < x + radius; i++) {
        for (int j = y - radius; j < y + radius; j++) {
            if ((abs(x-i))*(abs(x-i)) + (abs(y-j))*(abs(y-j)) < radius_squared) {
                screen.pixels[j*screen.size + i] = color;
            }
        }
    }
}

void circle(const int x, const int y, const int radius) {
    const int radius_squared = radius*radius;
    for (int i = x - radius; i < x + radius; i++) {
        for (int j = y - radius; j < y + radius; j++) {
            if ((abs(x-i))*(abs(x-i)) + (abs(y-j))*(abs(y-j)) < radius_squared) {
                screen.pixels[j*screen.size + i] = screen.fill;
            }
        }
    }
}

void rect(const int x0, const int y0, const int x1, const int y1, const int color) {
    for (int i = x0; i < x1; i++) {
        for (int j = y0; j < y1; j++) {
            screen.pixels[j*screen.size + i] = color;
        }
    }
}

void rect(const int x0, const int y0, const int x1, const int y1) {
    for (int i = x0; i < x1; i++) {
        for (int j = y0; j < y1; j++) {
            screen.pixels[j*screen.size + i] = screen.fill;
        }
    }
}


// ################################# COLORS #####################################



void colorize(const int x, const int y, const int color) {
    screen.pixels[y*screen.size + x] = color;
    }

int color(const int r, const int g, const int b) {
    // bitshift: rrrrrrrrggggggggbbbbbbbb
    return (r << 16) + (g << 8) + b;
}

int red(const int c) {
    return c >> 16;
}

int green(const int c) {
    return (c >> 8) - (red(c) << 8);
}

int blue(const int c) {
    return c - (red(c) << 16) - (green(c) << 8);
}

void fill(const int color) {
    screen.fill = color;
}

void load(std::string fp) {
    std::ifstream file(fp);
    std::vector<int> pixels;

    if (file.is_open()) {
        int singleValue;
        int state = 0;
        int pixel = 0;
        bool inHeader = true;

        while (file >> singleValue) {
            if (inHeader == false) {
                pixel += (singleValue << (8*(2-state)));
                state++;
                if (state == 2) {
                    pixels.push_back(pixel);
                    state = 0;
                    pixel = 0;
                }
            }
            if (singleValue == 255) {inHeader = false;}
        }
    } else {
        std::cerr << "Error: Unable to open file " << fp << std::endl;
    }
}

void draw() {
    // initialize a new file, or overwrite the existing
    const char* filename = screen.fp.c_str();
    FILE *fp = fopen(filename, "w");

    if (!fp) {
        printf("Can not open to write file\n");
        exit(1);
    };
    fprintf(fp, "%s\n", "P3");
    fprintf(fp, "%s\n", "# file created by tyler kelsey");
    fprintf(fp, "%d\n", screen.size);
    fprintf(fp, "%d\n", screen.size);
    fprintf(fp, "%d\n", 255);

    // and write it to the file
    for (int i=0; i<screen.size*screen.size; i++) {
        ssert(red(screen.pixels[i]) <= 255, red(screen.pixels[i]), " is larger than max color value 255.");
        ssert(red(screen.pixels[i]) >= 0, red(screen.pixels[i]), " is smaller than min color value 0.");
        ssert(green(screen.pixels[i]) <= 255, green(screen.pixels[i]), " is larger than max color value 255.");
        ssert(green(screen.pixels[i]) >= 0, green(screen.pixels[i]), " is smaller than min color value 0.");
        ssert(blue(screen.pixels[i]) <= 255, blue(screen.pixels[i]), " is larger than max color value 255.");
        ssert(blue(screen.pixels[i]) >= 0, blue(screen.pixels[i]), " is smaller than min color value 0.");
        fprintf(fp, "%d %d %d ", red(screen.pixels[i]), green(screen.pixels[i]), blue(screen.pixels[i]));
    }
}

void size(const int size) {
    screen = Screen(size);
    background(0);
}

int size() {
    return screen.size;
}
void name(std::string fp) {
    screen = Screen(fp);
    background(0);
}
void initialize(std::string filename, int size) {
    screen = Screen(filename, size);
    background(0);
}

void print(const int x) {
    printf("%d", x);
}

void ssert(const bool expr, const int num, const char* msg) {
    if (!expr) {std::cout << "Error: " << num << msg << std::endl; 
        assert(false); }
}