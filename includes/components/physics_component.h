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

   float gravity;
   
   bool debug_enabled;

   bool pause; 
   
   bool freeze_x_position;

   bool freeze_y_position;
   // helper functions
   void update(float dt);

   void debug();	

   void test(float gravity_in);

   void reset();

   float momentum_x();

   float momentum_y();

   private:

   // these functions are responible 
   // for the entire physics simulation
   // the call order is as they are defined
   void calculate_force();   

   void calculate_acceleration();

   void calculate_velocity(float dt);
   
   void calculate_position(float dt);
   
   void calculate_impulse();

 

};


#endif
