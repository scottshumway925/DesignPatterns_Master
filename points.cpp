/***********************************************************************
 * Source File:
 *    Points : Points graphic drawn on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Inert point values on the screen.
 ************************************************************************/

#include "points.h"
#include <cassert>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

 /******************************************************************
 * RANDOM
 * These functions generate a random number.
 ****************************************************************/
double randomValue(double min, double max)
{
   assert(min <= max);
   double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
   assert(min <= num && num <= max);
   return num;
}

 /*********************************************
  * POINTS Constructor
  * Create a new points value
  *********************************************/
Points::Points(const Position & pt, int value)
{
   // initial position is where the bullet was last seen
   this->pt = pt;

   // positive for a hit, negative for a miss
   this->value = value;

   // age is initially 100%;
   age = 1.0;

   // up for positive, down for negative
   double multiplyFactor = (value <= 0 ? -1.0 : 1.0);
   v.setDy(randomValue(1.0, 2.0) * multiplyFactor);

   // move points towards the center of the screen
   multiplyFactor = (pt.getX() > 400 ? -1.0 : 1.0);
   v.setDx(randomValue(1.0, 2.0) * multiplyFactor);
}

/*********************************************
 * POINTS SHOW
 * Draw a points value on the screen
 *********************************************/
void Points::show(const ogstream& gout) const
{
   if (value == 0)
      return;

   // set the color
   double red   = (value <= 0.0 ? 1.0 : 0.0) * age;
   double green = (value <= 0.0 ? 0.0 : 1.0) * age;
   double blue  = 0.0;

   // draw the digits
   int number = (value > 0 ? value : -value);

   gout.drawText(pt, to_string(number), red, green, blue);
}

/*********************************************
 * POINTS UPDATE
 * Move the points value on the screen
 *********************************************/
void Points::update()
{
   v.addDx(randomValue(-0.15, 0.15));
   v.addDy(randomValue(-0.15, 0.15));
   pt += v;
   age -= 0.01;
}