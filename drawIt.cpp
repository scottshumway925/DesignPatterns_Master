/***********************************************************************
 * Source File:
 *    DrawIt
 * Author:
 *    David Schaad
 * Summary:
 *    Draw birds, bullets, and effects based on commands
 ************************************************************************/

#include "drawIt.h"
#include <cassert>

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

using namespace std;


/***************************************************************/
/***************************************************************/
/*                             BIRD                            */
/***************************************************************/
/***************************************************************/

/************************************************************************
 * DRAW Disk
 * Draw a filled circule at [center] with size [radius]
 *************************************************************************/
void drawDisk(double x, double y, double radius,
              double red, double green, double blue)
{
   assert(radius > 1.0);
   const double increment = M_PI / radius;  // bigger the circle, the more increments

   // begin drawing
   glBegin(GL_TRIANGLES);
   glColor3f((GLfloat)red /* red % */, (GLfloat)green /* green % */, (GLfloat)blue /* blue % */);

   // three points: center, pt1, pt2
   double x2;
   double y2;
   x2 = x + (radius * cos(0.0));
   y2 = y + (radius * sin(0.0));

   double x3;
   double y3;
   x3 = x2;
   y3 = y2;

   // go around the circle
   for (double radians = increment;
      radians <= M_PI * 2.0 + .5;
      radians += increment)
   {
      x3 = x + (radius * cos(radians));
      y3 = y + (radius * sin(radians));

      glVertex2f((GLfloat)x, (GLfloat)y);
      glVertex2f((GLfloat)x2, (GLfloat)y2);
      glVertex2f((GLfloat)x3, (GLfloat)y3);

      x2 = x3;
      y2 = y3;
   }

   // complete drawing
   glEnd();
}

/*********************************************
 * DRAW STANDARD
 * Draw a standard bird: blue center and white outline
 *********************************************/
void drawStandard(double x, double y, double radius)
{
   drawDisk(x, y, radius - 0.0, 1.0, 1.0, 1.0); // white outline
   drawDisk(x, y, radius - 3.0, 0.0, 0.0, 1.0); // blue center
}

/*********************************************
 * DRAW FLOATER
 * Draw a floating bird: white center and blue outline
 *********************************************/
void drawFloater(double x, double y, double radius)
{
   drawDisk(x, y, radius - 0.0, 0.0, 0.0, 1.0); // blue outline
   drawDisk(x, y, radius - 4.0, 1.0, 1.0, 1.0); // white center
}

/*********************************************
 * DRAW CRAZY
 * Draw a crazy bird: concentric circles in a course gradient
 *********************************************/
void drawCrazy(double x, double y, double radius)
{
   drawDisk(x, y, radius * 1.0, 0.0, 0.0, 1.0); // bright blue outside
   drawDisk(x, y, radius * 0.8, 0.2, 0.2, 1.0);
   drawDisk(x, y, radius * 0.6, 0.4, 0.4, 1.0);
   drawDisk(x, y, radius * 0.4, 0.6, 0.6, 1.0);
   drawDisk(x, y, radius * 0.2, 0.8, 0.8, 1.0); // almost white inside

}

/*********************************************
 * DRAW SINKER
 * Draw a sinker bird: black center and dark blue outline
 *********************************************/
void drawSinker(double x, double y, double radius)
{
   drawDisk(x, y, radius - 0.0, 0.0, 0.0, 0.8);
   drawDisk(x, y, radius - 4.0, 0.0, 0.0, 0.0);
}

/***************************************************************/
/***************************************************************/
/*                            BULLET                           */
/***************************************************************/
/***************************************************************/

/*************************************************************************
 * GL VERTEXT POINT
 * Just a more convenient format of glVertext2f
 *************************************************************************/
inline void glVertexPoint(double x, double y)
{
   glVertex2f((GLfloat)x, (GLfloat)y);
}

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *************************************************************************/
void drawLine(double xBegin, double yBegin, double xEnd, double yEnd,
   double red, double green, double blue)
{
   // Get ready...
   glBegin(GL_LINES);
   glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);

   // Draw the actual line
   glVertexPoint(xBegin, yBegin);
   glVertexPoint(xEnd, yEnd);

   // Complete drawing
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/************************************************************************
 * DRAW DOT
 * Draw a single point (square actually on the screen, r pixels by r pixels
 *************************************************************************/
void drawDot(double x, double y, double radius,
   double red, double green, double blue)
{
   // Get ready, get set...
   glBegin(GL_TRIANGLE_FAN);
   glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);
   double r = radius / 2.0;

   // Go...
   glVertex2f((GLfloat)(x - r), (GLfloat)(y - r));
   glVertex2f((GLfloat)(x + r), (GLfloat)(y - r));
   glVertex2f((GLfloat)(x + r), (GLfloat)(y + r));
   glVertex2f((GLfloat)(x - r), (GLfloat)(y + r));

   // Done!  OK, that was a bit too dramatic
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/*********************************************
 * DRAW PELLET
 * Draw a pellet - just a 3-pixel dot
 *********************************************/
void drawPellet(double x, double y)
{
   drawDot(x, y, 3.0, 1.0, 1.0, 0.0);
}

/*********************************************
 * DRAW BOMB
 * Draw a bomb - many dots to make it have a soft edge
 *********************************************/
void drawBomb(double x, double y, double radius)
{
   // Bomb actually has a gradient to cut out the harsh edges
   drawDot(x, y, radius + 2.0, 0.50, 0.50, 0.00);
   drawDot(x, y, radius + 1.0, 0.75, 0.75, 0.00);
   drawDot(x, y, radius + 0.0, 0.87, 0.87, 0.00);
   drawDot(x, y, radius - 1.0, 1.00, 1.00, 0.00);

}

/*********************************************
 * DRAW SHRAPNEL
 * Draw a fragment - a bright yellow dot
 *********************************************/
void drawShrapnel(double x, double y, double radius)
{
   drawDot(x, y, radius, 1.0, 1.0, 0.0);
}

/*********************************************
 * DRAW MISSILE
 * Draw a missile - a line and a dot for the fins
 *********************************************/
void drawMissile(double x, double y, double xNext, double yNext)
{
   // missile is a line with a dot at the end so it looks like fins.
   drawLine(x, y, xNext, yNext, 1.0, 1.0, 0.0);
   drawDot(x, y, 3.0, 1.0, 1.0, 1.0);
}


/***************************************************************/
/***************************************************************/
/*                           EFFECT                            */
/***************************************************************/
/***************************************************************/

/************************************************************************
 * DRAW FRAGMENT
 * Draw the fragment on the screen
 *************************************************************************/
void drawFragment(double x, double y, double age, double size)
{
   // Draw this sucker
   glBegin(GL_TRIANGLE_FAN);

   // the color is a function of age - fading to black
   glColor3f((GLfloat)age, (GLfloat)age, (GLfloat)age);

   // draw the fragment
   glVertex2f((GLfloat)(x - size), (GLfloat)(y - size));
   glVertex2f((GLfloat)(x + size), (GLfloat)(y - size));
   glVertex2f((GLfloat)(x + size), (GLfloat)(y + size));
   glVertex2f((GLfloat)(x - size), (GLfloat)(y + size));
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/************************************************************************
 * DRAW STREEK
 * Draw the shrapnel streek on the screen
 *************************************************************************/
void drawStreek(double x, double y, double xEnd, double yEnd, double age)
{
   // Draw this sucker
   glBegin(GL_LINES);
   glColor3f((GLfloat)age, (GLfloat)age, (GLfloat)age);

   // Draw the actual line
   glVertex2f((GLfloat)x, (GLfloat)y);
   glVertex2f((GLfloat)xEnd, (GLfloat)yEnd);

   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/************************************************************************
 * DRAW EXHAUST
 * Draw a missile exhaust on the screen
 *************************************************************************/
void drawExhaust(double x, double y, double xEnd, double yEnd, double age)
{
   // Draw this sucker
   glBegin(GL_LINES);
   glColor3f((GLfloat)age, (GLfloat)age, (GLfloat)age);

   // Draw the actual line
   glVertex2f((GLfloat)x, (GLfloat)y);
   glVertex2f((GLfloat)xEnd, (GLfloat)yEnd);

   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}


/*********************************************
 * DRAW IT
 * Draw a bird, bullet, or effect based on a given command
 *********************************************/
void drawIt(const vector<string>& command)
{
   vector<double> parameters;

   // Iterate through the command and convert each value to 
   // a double. Copy these values into a new vector
   for (int i = 1; i < command.size(); i++)
      parameters.push_back(stod(command[i]));

   // Birds
   if (command[0] == "STANDARD")
      drawStandard(parameters[0], parameters[1], parameters[2]);
   else if (command[0] == "FLOATER")
      drawFloater(parameters[0], parameters[1], parameters[2]);
   else if (command[0] == "CRAZY")
      drawCrazy(parameters[0], parameters[1], parameters[2]);
   else if (command[0] == "SINKER")
      drawSinker(parameters[0], parameters[1], parameters[2]);

   // Bullets
   else if (command[0] == "PELLET")
      drawPellet(parameters[0], parameters[1]);
   else if (command[0] == "BOMB")
      drawBomb(parameters[0], parameters[1], parameters[2]);
   else if (command[0] == "SHRAPNEL")
      drawShrapnel(parameters[0], parameters[1], parameters[2]);
   else if (command[0] == "MISSILE")
      drawMissile(parameters[0], parameters[1], parameters[2], parameters[3]);

   // Effects
   else if (command[0] == "FRAGMENT")
      drawFragment(parameters[0], parameters[1], parameters[2], parameters[3]);
   else if (command[0] == "STREEK")
      drawStreek(parameters[0], parameters[1], parameters[2], parameters[3], parameters[4]);
   else if (command[0] == "EXHAUST")
      drawExhaust(parameters[0], parameters[1], parameters[2], parameters[3], parameters[4]);
}