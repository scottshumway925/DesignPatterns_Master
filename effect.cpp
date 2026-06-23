/***********************************************************************
 * Source File:
 *    Fragment : Pieces that fly off a dead bird
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Pieces that fly off a dead bird
 ************************************************************************/

#include "effect.h"
#include <cassert>

#include <vector>
#include <string>
#include "drawIt.h"
using namespace std;

/******************************************************************
 * RANDOM
 * This function generates a random number.
 ****************************************************************/
double random(double min, double max)
{
   assert(min <= max);
   double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
   assert(min <= num && num <= max);
   return num;
}



/***************************************************************/
/***************************************************************/
/*                       CONSTRUCTORS                          */
/***************************************************************/
/***************************************************************/

/************************************************************************
 * FRAGMENT constructor
 *************************************************************************/
Fragment::Fragment(const Position & pt, const Velocity & v) : Effect(pt)
{
   // the velocity is a random kick plus the velocity of the thing that died
   this->v.setDx(v.getDx() * 0.5 + random(-6.0, 6.0));
   this->v.setDy(v.getDy() * 0.5 + random(-6.0, 6.0));
   
    // age
    age = random(0.4, 1.0);
    
    // size
    size = random(1.0, 2.5);
}

/************************************************************************
 * STREEK constructor
 *************************************************************************/
Streek::Streek(const Position & pt, Velocity v) : Effect(pt)
{
   ptEnd = pt;
   v *= -1.0;
   ptEnd += v;
   
    // age
    age = 0.5;
}

/************************************************************************
 * EXHAUST constructor
 *************************************************************************/
Exhaust::Exhaust(const Position & pt, Velocity v) : Effect(pt)
{
    ptEnd = pt;
    v *= -1.0;
    ptEnd += v;

    // age
    age = 0.5;
}

/***************************************************************/
/***************************************************************/
/*                           RENDER                            */
/***************************************************************/
/***************************************************************/

/************************************************************************
 * FRAGMENT RENDER
 * Draw the fragment on the screen
 *************************************************************************/
void Fragment::render() const
{
    // Do nothing if we are already dead
    if (isDead())
        return;
    
    vector<string> command = { "FRAGMENT", to_string(pt.getX()), to_string(pt.getY()), to_string(age), to_string(size) };
    drawIt(command);
}

/************************************************************************
 * STREEK RENDER
 * Draw the shrapnel streek on the screen
 *************************************************************************/
void Streek::render() const
{
    // Do nothing if we are already dead
    if (isDead())
        return;
    
    vector<string> command = { "STREEK", to_string(pt.getX()), to_string(pt.getY()), to_string(ptEnd.getX()), to_string(ptEnd.getY()), to_string(age)};
    drawIt(command);
}

/************************************************************************
 * EXHAUST RENDER
 * Draw a missile exhaust on the screen
 *************************************************************************/
void Exhaust::render() const
{
   // Do nothing if we are already dead
   if (isDead())
       return;
   
   vector<string> command = { "EXHAUST", to_string(pt.getX()), to_string(pt.getY()), to_string(ptEnd.getX()), to_string(ptEnd.getY()), to_string(age) };
   drawIt(command);
}

/***************************************************************/
/***************************************************************/
/*                            FLY                              */
/***************************************************************/
/***************************************************************/

/************************************************************************
 * FRAGMENT FLY
 * Move the fragment on the screen
 *************************************************************************/
void Fragment :: fly()
{
    // move it forward with inertia (no gravity)
    pt += v;
    
    // increase the age so it fades away
    age -= 0.02;
    size *= 0.95;
}

/************************************************************************
 * STREEK FLY
 * The streek will just fade away
 *************************************************************************/
void Streek :: fly()
{
    // move it forward with inertia (no gravity)
//    pt += v;
    
   // increase the age so it fades away
   age -= 0.10;
}

/************************************************************************
 * EXHAUST FLY
 * The exhaust will just fade away
 *************************************************************************/
void Exhaust :: fly()
{
   // move it forward with inertia (no gravity)
//   pt += v;
    
   // increase the age so it fades away
   age -= 0.025;
}
