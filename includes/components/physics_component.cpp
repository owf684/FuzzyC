/* Name of Program: physics_component
 *
 * Purpose: simulates physics
 *
 * Author: Christopher Corona
 *
 * Version: v0.1.0 
 *
 * Assumptions:
 * All inputs and outputs of this system
 * are in the metric system
 * 
 */

#include "physics_component.h"
using namespace std::chrono;




// Constructor
PhysicsComponent::PhysicsComponent()
{
 force.y = 0.0;
 force.x = 0.0;
 acceleration.x = 0.0;
 acceleration.y = 0.0;
 velocity.x = 0.0;
 velocity.y = 0.0;
 position.x = 0.0;
 position.y = 0.0;
 gravity = 9.8;
 mass = 100.0;
 debug_enabled = false; 
 pause = false;
 freeze_x_position = false;
 freeze_y_position = false;

}


/* Function: calculate_force
 *
 * Purpose: calculates force using F = M * A for both
 * x and y components
 *
 * Input Limits: None. All real numbers
 * are acceptable
 *
 */

void PhysicsComponent::calculate_force()
{
  // F = M * A 
  force.y = mass * (gravity + impulse.y) ;

  force.x = mass * ( acceleration.x + impulse.x) ;
}

/* Function: calculate_acceleration
 *
 * Purpose: This calculates the acceleration
 * of the object using equation A = F / M for 
 * boy x and y components
 *
 * Input Limits: mass cannot be zero
 * mass of zero will throw mass_error
 * 
 */
void PhysicsComponent::calculate_acceleration()
{
  if (mass == 0) throw mass_error();

  // A = F/M
  acceleration.y = force.y/mass;

  acceleration.x = force.x/mass; 
}

/* Function: calculate_velocity()
 *
 * Purpose: This calculates the velocity of
 * an object using equation V= Vinitial + A*T
 * for both x and y components
 *
 * Input Limits: dt must be greater than or equal to 0
 * a negative dt will throw a frame_time_error
 *
 */

void PhysicsComponent::calculate_velocity(float dt)
{
  // V = Vo + A*T
  
  if (dt < 0) throw frame_time_error();

  velocity.x += acceleration.x*dt;
  velocity.y +=  acceleration.y*dt;
 
 
}

/* Function: calculate_position
 *
 * Purpose: This calculates the velocity of 
 * an object using equation 
 * p = p_initial + v_initial*t + 1/2(a)^2
 * for both x and y components
 *
 * Input Limits: dt must be greater than -1
 * a dt of less than zero will throw a 
 * frame_time_error
 *
 */

void PhysicsComponent::calculate_position(float dt)
{
  // P = Po + Vo*t + 1/2(A)^2
  
  if (dt < 0) throw frame_time_error();
  
  if (!freeze_x_position) position.x = position.x + velocity.x*dt + 0.5*acceleration.x*pow(dt,2);

  if (!freeze_y_position) position.y = position.y + velocity.y*dt + 0.5*acceleration.y*pow(dt,2);  
}

/* Function: calculate_impulse()
*
*  Purpose: This decreases the impulse
*  by the rate of gravity every tick
*
*  Input Limits: none
*
*  Weakness: I think this is not 
*  a realistcally or mathematically
*  correct way to calcualte the 
*  decrease of the impulse. 
*/ 

void PhysicsComponent::calculate_impulse(float dt)
{
  if(impulse.y < 0)
  {
    impulse.y -= mass*velocity.y*dt;
  }
}

/* Function: update()
 *
 * Purpose: This calls the physics functions
 * in the correct order to properly 
 * simulate object physics. 
 *
 * Input Limits: dt must be greater than -1
 * a dt of less than zero will throw a frame_time_error
 *
 */

void PhysicsComponent::update(float dt)
{
  if (dt< 0) throw frame_time_error();

  calculate_force();
  calculate_acceleration();
  calculate_velocity(dt);
  calculate_position(dt);
  calculate_impulse(dt);

  if (debug_enabled)
  {
    debug();
  }
}


/* Function: debug()
 *
 * Purpose: This will print out all the physics
 * attributes if boolean debug_enabled is set true
 *
 * Input Limits: None
 *
 */

void PhysicsComponent::debug()
{
std::cout <<"===================================================" << std::endl;
std::cout <<"\t\t Physics Debug Enabled \n";
std::cout <<"---------------------------------------------------\n";
std::cout << "position.x = " << position.x << std::endl;
std::cout << "position.y = " << position.y << std::endl;
std::cout << "velocity.x = " << velocity.x << std::endl;
std::cout << "velocity.y = " << velocity.y << std::endl;
std::cout << "acceleration.x = " << acceleration.x << std::endl;
std::cout << "acceleration.y = " << acceleration.y << std::endl;
std::cout << "force.x = " << force.x << std::endl;
std::cout << "force.y = " << force.y << std::endl;
std::cout << "mass = " << mass << std::endl;
std::cout <<"=================================================="<<std::endl;
}

/* Function: test()
 *
 * Purpose: This will test the physics systems
 * in the x and y components. Every second 
 * the position, velocity, and acceleration
 * will be captured. This data once captured
 * will be compared to ideal data. If within
 * tolerance the physics systems will pass the test 
 *
 * Tolerance: +-5%
 *
 * Arguments: 
 * gravity_in sets the acceleration for which the 
 * test will run at. For the test to pass it 
 * must be set to 9.8 m/s^2
 * Any other value is accepted but will cause
 * the tests to fail.
 */

void PhysicsComponent::test(float gravity_in)
{
  std::cout << "==========================\n";
  std::cout << "Running Physics Test\n";
  std::cout << "==========================\n";

  // setup constants and frame rate variables
  const float gravity_t = gravity_in;
  gravity = gravity_in;
  float dt = 0.0;
  const float frames_per_second = 60.0;
  const float microseconds = pow(10,6);
  const float frame_duration_us = (1.0/frames_per_second)*microseconds;
  float time_elapsed = 0.0;

  // set up test data
  std::vector<float> y_position_test_points;
  std::vector<float> y_velocity_test_points;
  std::vector<float> y_acceleration_test_points;
  std::vector<float> x_position_test_points;
  std::vector<float> x_velocity_test_points;
  std::vector<float> x_acceleration_test_points;
  std::vector<float> seconds_test_points;
  float seconds_elapsed;
  const float acceleration_ideal_points[8] = { 9.8 , 9.8  , 9.8  ,9.8  ,9.8   ,9.8   ,9.8   ,9.8   };
  const float velocity_ideal_points[8]     = { 9.8 , 19.6 , 29.4 ,39.2 ,49.0  ,58.8  ,68.6  ,78.4  };
  const float position_ideal_points[8]     = { 4.9 , 19.6 , 44.1 ,78.4 ,122.5 ,176.4 ,240.1 ,313.6 };

  // start test with object at rest
  reset();
 

  for (int test_points = 0;test_points < 8; NULL)
  {
    // handle delat time
    auto dt_start = high_resolution_clock::now();

    acceleration.x = gravity_t;
    update(dt);

    // capture test points
    if (time_elapsed >= 1.0 && time_elapsed <= 1.02)
    {
      std::cout << "Capturing Test Point: " << test_points << std::endl;
      seconds_elapsed += time_elapsed;
      seconds_test_points.push_back(seconds_elapsed);

      // capture y data
      y_position_test_points.push_back(position.y);
      y_velocity_test_points.push_back(velocity.y);
      y_acceleration_test_points.push_back(acceleration.y);

      // capture x data
      x_position_test_points.push_back(position.x);
      x_velocity_test_points.push_back(velocity.x);
      x_acceleration_test_points.push_back(acceleration.x);

      test_points++;
      time_elapsed = 0.0;
    }

    // handle delta time
    usleep(frame_duration_us);
    auto dt_end = high_resolution_clock::now();
    auto dt_final = duration_cast<milliseconds> (dt_end - dt_start);
    dt = dt_final.count()/1000.0;

   time_elapsed += dt;
  }

  float y_error_average_a =0.0;
  float y_error_average_v =0.0;
  float y_error_average_p =0.0;

  float x_error_average_a =0.0;
  float x_error_average_v =0.0;
  float x_error_average_p =0.0;

  // test acceleration data
  for (int point = 0; point < 8; point++)
  {
    // calculate the errors
    auto y_error_a = abs(acceleration_ideal_points[point]-y_acceleration_test_points[point])/acceleration_ideal_points[point];
    auto y_error_v = abs(velocity_ideal_points[point]-y_velocity_test_points[point])/velocity_ideal_points[point];
    auto y_error_p = abs(position_ideal_points[point]-y_position_test_points[point])/position_ideal_points[point];

    auto x_error_a = abs(acceleration_ideal_points[point]-x_acceleration_test_points[point])/acceleration_ideal_points[point];
    auto x_error_v = abs(velocity_ideal_points[point]-x_velocity_test_points[point])/velocity_ideal_points[point];
    auto x_error_p = abs(position_ideal_points[point]-x_position_test_points[point])/position_ideal_points[point];

    // accumulate the error
    y_error_average_a += y_error_a;
    y_error_average_v += y_error_v;
    y_error_average_p += y_error_p;

    x_error_average_a += x_error_a;
    x_error_average_v += x_error_v;
    x_error_average_p += x_error_p;

  }

  // calculate the average error
  y_error_average_a /= 8;
  y_error_average_v /= 8;
  y_error_average_p /= 8;

  x_error_average_a /=8;
  x_error_average_v /= 8;
  x_error_average_p /= 8;

  std::cout << "===================================================================\n";
  std::cout << "Y Acceleration Percent Error: " << y_error_average_a*100 << std::endl;
  if (y_error_average_a*100 <= 5.0) std::cout << "Y Acceleration Test Passed\n";
  else std::cout << "Y Acceleration Test FAILED\n";
  std::cout << "===================================================================\n";

  std::cout << "===================================================================\n";
  std::cout << "Y Velcoity Percent Error: " << y_error_average_v*100 << std::endl;
  if (y_error_average_v*100 <= 5.0) std::cout << "Y Velocity Test Passed \n";
  else std::cout << "Y Velocity Test FAILED\n";
  std::cout << "===================================================================\n";

  std::cout << "===================================================================\n";
  std::cout << "Y Position Percent Error: " << y_error_average_p*100 << std::endl;
  if (y_error_average_p*100 <= 5.0) std::cout << "Y Position Test Passed \n";
  else std::cout << "Y Position Test FAILED \n";
  std::cout << "===================================================================\n";


  std::cout << "===================================================================\n";
  std::cout << "X Acceleration Percent Error: " << x_error_average_a*100 << std::endl;
  if (x_error_average_a*100 <= 5.0) std::cout << "X Acceleration Test Passed\n";
  else std::cout << "X Acceleration Test FAILED\n";
  std::cout << "===================================================================\n";

  std::cout << "===================================================================\n";
  std::cout << "X Velcoity Percent Error: " << x_error_average_v*100 << std::endl;
  if (x_error_average_v*100 <= 5.0) std::cout << "X Velocity Test Passed \n";
  else std::cout << "X Velocity Test FAILED\n";
  std::cout << "===================================================================\n";

  std::cout << "===================================================================\n";
  std::cout << "X Position Percent Error: " << x_error_average_p*100 << std::endl;
  if (x_error_average_p*100 <= 5.0) std::cout << "X Position Test Passed \n";
  else std::cout << "X Position Test FAILED \n";
  std::cout << "===================================================================\n";

}

/* Function: reset()
*
*  Purpose: This function
*  resets all the physical
*  attributes back to 0
*  
*/
void PhysicsComponent::reset()
{
  force.y = 0.0;
  force.x = 0.0;
  acceleration.x = 0.0;
  acceleration.y = 0.0;
  velocity.x = 0.0;
  velocity.y = 0.0;
  position.x = 0.0;
  mass = 100.0;
}

/* Function: momentum_x()
*
* Purpose: This function calculates the 
* current momentum of the object in the 
* x direction
*/

float PhysicsComponent::momentum_x()
{
  return float(velocity.x*mass);
}

/* Function: momentum_y()
*
* Purpose: This function calculates the
* current momentum of the object in
* the y direction
*/

float PhysicsComponent::momentum_y()
{
  return float(velocity.y*mass);
}