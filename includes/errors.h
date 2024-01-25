/* Name of Program: errors
 *
 * Purpose: This contains all the error 
 * definitions used in the fuzzy engine
 *
 * Author: Christopher Corona
 *
 * Version: v0.1.0
 *
 */
#include <stdexcept>
#include <exception>
#ifndef ERRORS_H
#define ERRORS_H

class frame_time_error : public std::exception
{
public:
  const char* what() const throw() {
    return "frame_time_error: dt value is zero. must be greater than 0\n";

  }
};


class mass_error : public std::exception
{
public:
  const char* what() const throw(){
    return "mass_error: mass is zero. must be greater than zero\n"; 
  }
};


#endif
