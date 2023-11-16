#ifndef P5
#define P5
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>

class Screen {
    public:
        // Basic screen, of size 2000px * 2000px. Saved in file "image.ppm".
        Screen () : fp("image.ppm"), size(2000), pixels(new int[2000*2000]), fill(0) {};

        // Basic screen, of size 2000px * 2000px. fp denotes the name of the file f.ex.: "myfile.ppm".
        Screen (std::string _fp) : fp(_fp), size(2000), pixels(new int[2000*2000]), fill(0) {};

        // Basic screen, with a width and height equal to size. Saved in file "image.ppm".
        Screen (int _size) : fp("image.ppm"), size(_size), pixels(new int[_size*_size]), fill(0) {};

        // Basic screen, with a width and height equal to size. fp denotes the name of the file f.ex.: "myfile.ppm".
        Screen (std::string _fp, int _size) : fp(_fp), size(_size), pixels(new int[_size*_size]), fill(0) {};

        // Copy constructor. Don't touch.
        Screen (const Screen &_screen) {
            size = _screen.size;
            fp = _screen.fp;
            pixels = new int[size * size];
            fill = _screen.fill;
            memcpy(pixels, _screen.pixels, size * size * sizeof(int));
        }
        // Copy construction operator. Don't touch.
        Screen operator=(const Screen &_screen) {
            size = _screen.size;
            fp = _screen.fp;
            fill = _screen.fill;
            delete[] pixels; // delete the existing pixel data
            pixels = new int[size * size];
            memcpy(pixels, _screen.pixels, size * size * sizeof(int));
            return *this;
        }
        // Destructor. Don't touch.
        ~Screen () { delete[] pixels;}

        std::string fp;
        int size;
        int* pixels;
        int fill;
};

// Set the size of the screen, and initialize the screen.
void size(const int size);

// Gets the current size of the screen
int size();

// Set what the filename is, and initialize the screen.
void name(std::string fp);

// Set the filename and size, and initialize the screen. 
void initialize(std::string filename, int size);

// Sets the background to a color, built using the internal color int
void background(const int color);

// Sets the background to an RGB color.
void background(const int r, const int g, const int b);

// Creates a color out of r,g,b.
int color(const int r, const int g, const int b);

// extracts red from a color int.
int red(const int c);

// extracts red from a color int.
int green(const int c);

// extracts red from a color int.
int blue(const int c);

// Color a pixel to whatever RGB color you want.
void colorize(const int x, const int y, const int color);

// Sets the standard fill to a different color
void fill(const int color);

// Draws a circle with given color.
void circle(const int x, const int y, const int radius, const int color);

// Draws a circle with already given fill color.
void circle(const int x, const int y, const int radius);

// Draws a rectangle with given color.
void rect(const int x0, const int y0, const int x1, const int y1, const int color);

// Draws a rectangle with already given fill color.
void rect(const int x0, const int y0, const int x1, const int y1);

// Assert wrapper, used internally but you can use it if you want, I guess.
void ssert(const bool expr, const int num, const char* msg);

// simple print int
void print(const int x);

// loads a file to a screen
void load(std::string fp);

// Draws the screen to file, in a .ppm format.
void draw();


#endif
