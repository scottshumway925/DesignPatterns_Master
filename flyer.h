/***********************************************************************
 * Header File:
 *    Flyer
 * Author:
 *    Tryhard Kings
 * Summary:
 *    Bridge that handles draw and all movement
 ************************************************************************/

#pragma once
#include "position.h"

#include <list>
#include <cassert>

/*********************************************
 * Flyer
 * movement controller
 *********************************************/
class Flyer
{
protected:
   Position pt;
   Velocity v;
   bool dead;
   double radius;
   
public:
   Flyer() : dead(false), radius(1.0) { }
   
   // getters
   Position getPosition()  const { return pt;     }
   Velocity getVelocity()  const { return v;      }
   bool isDead()           const { return dead;   }
   double getRadius()      const { return radius; }

   // special functions
   virtual void draw() const = 0;
   virtual void move() = 0;
   virtual void kill()             { dead = true; }
};
