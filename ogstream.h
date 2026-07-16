/***********************************************************************
 * Header File:
 *    ogstream : 
 * Author:
 *    David Schaad
 * Summary:
 *    
 ************************************************************************/

#pragma once
#include "position.h"
#include <string>

class ogstream
{
public:
   ogstream() {};
   ogstream(Position point) : pt(point) {}
   void flush() {};
   void setPosition(Position pt) { this->pt = pt; };
   void drawRectangle(const Position& pt,
      double angle = 0.0,
      double width = 10.0,
      double height = 100.0,
      double red = 1.0,
      double green = 1.0,
      double blue = 1.0) const;
   void drawLine(const Position& begin, const Position& end,
      double red = 1.0, double green = 1.0, double blue = 1.0) const;
   void drawDot(const Position& point, double radius = 2.0,
      double red = 1.0, double green = 1.0, double blue = 1.0) const;
   void drawDisk(const Position& center, double radius,
      double red, double green, double blue) const;
   void drawBackground(double redBack, double greenBack, double blueBack) const;
   void drawHourglass(double percent,
      double redFore, double greenFore, double blueFore,
      double redBack, double greenBack, double blueBack) const;
   void drawText(const Position& point, const std::string& text,
      double red = 1.0, double green = 1.0, double blue = 1.0) const;

private:
   Position pt;
};

