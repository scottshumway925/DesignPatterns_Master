/***********************************************************************
 * Header File:
 *    Flyer
 * Author:
 *    Tryhard Kings
 * Summary:
 *    Bridge that handles all movement
 ************************************************************************/

#pragma once
#include "position.h"
#include "effect.h"
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
   
   // getters
   Position getPosition()  const { return pt;     }
   Velocity getVelocity()  const { return v;      }
   bool isDead()           const { return dead;   }
   double getRadius()      const { return radius; }

   // special functions
   virtual void draw() = 0;
   virtual void move() = 0;
   virtual void kill()                   { dead = true; }
}
