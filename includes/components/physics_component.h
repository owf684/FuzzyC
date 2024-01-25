#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include <cmath>
#include <iostream>
#include <vector>
#include <chrono>
#include <unistd.h>
#include "../errors.h"



struct xy
{
 float x;
 float y;
};


class PhysicsComponent
{
  public:
   // Constructor
   PhysicsComponent();

   // physics attributes 
   xy position;	

   xy velocity;

   xy acceleration;

   xy force;

   xy impulse;

   xy direction;

   float mass;

   bool debug_enabled;

   bool pause; 
   
   // helper functions
   void update(float gravity, float dt);

   void debug();	

   void test(float gravity_in);

   void reset();

   private:

   // these functions are responible 
   // for the entire physics simulation
   // the call order is as they are defined
   void calculate_force(float gravity);   

   void calculate_acceleration();

   void calculate_velocity(float dt);
   
   void calculate_position(float dt);
   
   void calculate_impulse(float gravity);


};


#endif
