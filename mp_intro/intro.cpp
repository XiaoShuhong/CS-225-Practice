#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
  PNG inPNG;
  bool b = inPNG.readFromFile(inputFile);
  int w = inPNG.width();
  int h = inPNG.height();
  PNG outPNG = PNG(w, h);
  for (int i = 0; i < w; i++){
    for (int j = 0; j < h; j++){
      HSLAPixel* inPixel = &inPNG.getPixel(i, j);
      HSLAPixel* outPixel = &outPNG.getPixel(w-i-1,h-j-1);
      *outPixel = *inPixel;
    }
  }
  outPNG.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){
      HSLAPixel* myPixel = &png.getPixel(i, j);
      HSLAPixel* oPix = new HSLAPixel(i*44, .78 * j, 1.0 * (i+j)*.43);
      *myPixel =  *oPix;
      delete oPix;
    }
  }

  return png;
}
