#include "p5.hpp"
#define WHITE 16777215
using namespace std;

int main(){
  size(1000);

  for (int i=0; i<size(); i++) {
    for (int j=0; j<size(); j++) {
      if (i%10 == 0 or j%10 == 0) {
      colorize(i, j, color(0, 0, 0));
      }
      else {
      colorize(i, j, color((j+1)*255/1000, (i+1)*255/2000, (1000-j)/4));
      }
    }
  }


  draw();
  return 0;
}

// #### TO RUN ANOTHER PROGRAM JUST MAKE A NEW FILE AND CHANGE THE MAKEFILE! ####