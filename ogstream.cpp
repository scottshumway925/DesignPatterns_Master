/**********************************************************************
 * ogstream
 * 
 **********************************************************************/

#include "ogstream.h"
using namespace std;

#ifdef __APPLE__

#define GL_SILENCE_DEPRECATION
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_18
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // __linux__

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>         // OpenGL library we copied 
#define _USE_MATH_DEFINES
#include <math.h>
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // _WIN32


/*************************************************************************
 * GL VERTEXT POINT
 * Just a more convenient format of glVertext2f
 *************************************************************************/
inline void glVertexPoint(const Position& point)
{
   glVertex2f((GLfloat)point.getX(), (GLfloat)point.getY());
}


/*************************************************************************
 * GL COLOR
 * Just a more convenient format of glColor3f
 *************************************************************************/
inline void glColor(double red, double green, double blue)
{
   glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);
}

/************************************************************************
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *    INPUT  origin   The center point we will rotate around
 *           x,y      Offset from center that we will be rotating
 *           rotation Rotation in degrees
 *    OUTPUT point    The new position
 *************************************************************************/
Position rotate(const Position& origin,
   double x, double y, double rotation)
{ 
   // because sine and cosine are expensive, we want to call them only once
   double cosA = cos(rotation);
   double sinA = sin(rotation);

   // start with our original point
   Position ptReturn(origin);

   // find the new values
   ptReturn.addX(x * cosA - y * sinA);
   ptReturn.addY(y * cosA + x * sinA /*center of rotation*/);

   return ptReturn;
}

/************************************************************************
 * DRAW RECTANGLE
 * Draw a rectangle on the screen from the beginning to the end.
 *************************************************************************/
void ogstream::drawRectangle(const Position& pt,
   double angle, double width, double height,
   double red, double green, double blue) const
{
   // Get ready...
   glBegin(GL_QUADS);
   glColor(red, green, blue);

   // Draw the actual line
   glVertexPoint(rotate(pt, width / 2.0, height / 2.0, angle));
   glVertexPoint(rotate(pt, width / 2.0, -height / 2.0, angle));
   glVertexPoint(rotate(pt, -width / 2.0, -height / 2.0, angle));
   glVertexPoint(rotate(pt, -width / 2.0, height / 2.0, angle));
   glVertexPoint(rotate(pt, width / 2.0, height / 2.0, angle));

   // Complete drawing
   glColor(1.0 /* red % */, 1.0 /* green % */, 1.0 /* blue % */);
   glEnd();
}

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *************************************************************************/
void ogstream::drawLine(const Position& begin, const Position& end,
   double red, double green, double blue) const
{
   // Get ready...
   glBegin(GL_LINES);
   glColor(red, green, blue);

   // Draw the actual line
   glVertexPoint(begin);
   glVertexPoint(end);

   // Complete drawing
   glColor(1.0 /* red % */, 1.0 /* green % */, 1.0 /* blue % */);
   glEnd();
}

/************************************************************************
 * DRAW DOT
 * Draw a single point (square actually on the screen, r pixels by r pixels
 *************************************************************************/
void ogstream::drawDot(const Position& point, double radius,
   double red, double green, double blue) const
{
   // Get ready, get set...
   glBegin(GL_TRIANGLE_FAN);
   glColor(red, green, blue);
   double r = radius / 2.0;

   // Go...
   glVertex2f((GLfloat)(point.getX() - r), (GLfloat)(point.getY() - r));
   glVertex2f((GLfloat)(point.getX() + r), (GLfloat)(point.getY() - r));
   glVertex2f((GLfloat)(point.getX() + r), (GLfloat)(point.getY() + r));
   glVertex2f((GLfloat)(point.getX() - r), (GLfloat)(point.getY() + r));

   // Done!  OK, that was a bit too dramatic
   glColor(1.0 /* red % */, 1.0 /* green % */, 1.0 /* blue % */);
   glEnd();
}

/************************************************************************
 * DRAW Disk
 * Draw a filled circule at [center] with size [radius]
 *************************************************************************/
void ogstream::drawDisk(const Position& center, double radius,
   double red, double green, double blue) const
{
   //assert(radius > 1.0);
   const double increment = M_PI / radius;  // bigger the circle, the more increments

   // begin drawing
   glBegin(GL_TRIANGLES);
   glColor(red, green , blue);

   // three points: center, pt1, pt2
   Position pt1;
   pt1.setX(center.getX() + (radius * cos(0.0)));
   pt1.setY(center.getY() + (radius * sin(0.0)));
   Position pt2(pt1);

   // go around the circle
   for (double radians = increment;
      radians <= M_PI * 2.0 + .5;
      radians += increment)
   {
      pt2.setX(center.getX() + (radius * cos(radians)));
      pt2.setY(center.getY() + (radius * sin(radians)));

      glVertexPoint(center);
      glVertexPoint(pt1);
      glVertexPoint(pt2);

      pt1 = pt2;
   }

   // complete drawing
   glEnd();
}

/************************************************************************
 * DRAW Background
 * Fill in the background
 *  INPUT color   Background color
 *************************************************************************/
void ogstream::drawBackground(double redBack, double greenBack, double blueBack) const
{   
   glBegin(GL_TRIANGLE_FAN);

   // two triangles is the fastest way to fill the screen.
   glColor(redBack, greenBack, blueBack);
   glVertex2f((GLfloat)0.0, (GLfloat)0.0);
   glVertex2f((GLfloat)pt.getX(), (GLfloat)0.0);
   glVertex2f((GLfloat)pt.getX(), (GLfloat)pt.getY());
   glVertex2f((GLfloat)0.0, (GLfloat)pt.getY());

   glEnd();
}

/************************************************************************
 * DRAW Timer
 * Draw a large timer on the screen
 *  INPUT percent     Amount of time left
 *        Foreground  Foreground color
 *        Background  Background color
 *************************************************************************/
void ogstream::drawHourglass(double percent,
   double redFore, double greenFore, double blueFore,
   double redBack, double greenBack, double blueBack) const
{
   double radians;

   GLfloat length = (GLfloat)pt.getX();
   GLfloat half = length / (GLfloat)2.0;

   // do the background stuff
   drawBackground(redBack, greenBack, blueBack);

   // foreground stuff
   radians = percent * M_PI * 2.0;
   GLfloat x_extent = half + length * (GLfloat)sin(radians);
   GLfloat y_extent = half + length * (GLfloat)cos(radians);

   // get read to draw the triangles
   glBegin(GL_TRIANGLE_FAN);
   glColor(redFore, greenFore, blueFore);
   glVertex2f(half, half);

   // fill in the triangles, one eight at a time
   switch ((int)(percent * 8.0))
   {
   case 7: // 315 - 360
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, 0.0);
      glVertex2f(0.0, 0.0);
      glVertex2f(0.0, length);
      break;
   case 6: // 270 - 315
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, 0.0);
      glVertex2f(0.0, 0.0);
      glVertex2f(0.0, half);
      break;
   case 5: // 225 - 270
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, 0.0);
      glVertex2f(0.0, 0.0);
      break;
   case 4: // 180 - 225
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, 0.0);
      glVertex2f(half, 0.0);
      break;
   case 3: // 135 - 180
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, half);
      glVertex2f(length, 0.0);
      break;
   case 2: // 90 - 135 degrees
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, half);
      break;
   case 1: // 45 - 90 degrees
      glVertex2f(half, length);
      glVertex2f(length, length);
      break;
   case 0: // 0 - 45 degrees
      glVertex2f(half, length);
      break;
   }
   glVertex2f(x_extent, y_extent);

   // complete drawing
   glEnd();

   // draw the red line now
   drawLine(Position(half, half), Position(x_extent, y_extent), 0.6, 0.0, 0.0);
}


/*************************************************************************
 * DRAW TEXT
 * Draw text using a simple bitmap font
 *   INPUT  point     The position of the text
 *          text      The text to be displayed
 ************************************************************************/
void ogstream::drawText(const Position& point, const string& text,
   double red, double green, double blue) const
{
   void* pFont = GLUT_TEXT;

   const char* c_text = text.c_str();
   glColor(red, green, blue);

   // prepare to output the text from the top-left corner
   glRasterPos2f((GLfloat)point.getX(), (GLfloat)point.getY());

   // loop through the text
   for (const char* p = c_text; *p; p++)
      glutBitmapCharacter(pFont, *p);
}