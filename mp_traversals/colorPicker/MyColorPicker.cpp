#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

MyColorPicker::MyColorPicker(double inc){
  inc_ = inc;
  sat_ = 0.0;
}

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel pixel(180, sat_, 0.5);
  sat_ += inc_;
  if (sat_ >= 1.0) {
    sat_ -= 1.0; 
  }
  return pixel;
  return HSLAPixel();
}
