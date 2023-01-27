/**
  * util.cpp - General purpose utility functions, like those that might be found in C's standard library (but are missing in RobotC, grr!)
  *
  **/

#include "vex.h"

#define arraySize(a) (sizeof(a)/sizeof(a[0]))
#define PI 3.1415926535

/**
  * Performs modulus for floats
  * @param float x The numerator
  * @param float y The demominator
  * @return float The remainder of x / y
  **/
float fmodf(float x, float y) 
{
  return (x - y * floor(x / y));
}


/**
  * Clamps a value to a maximum and minimum
  * @param float val The value to clamp
  * @param float min The minimum value for the value
  * @param float max The maximum value for the value
  * @return float The clamped value
  **/
float clamp(float val, float min, float max) 
{
  return val > max ? max : val < min ? min : val;
}

/**
  * Rescales two values to a specified maximum and returns the specified value
  * @param int max The maximum value, used to calculate the scalar
  * @param int alpha The first value to rescale
  * @param int beta The second value to rescale
  * @param int side The value to return, 0 for alpha, 1 for beta
  **/
int rescaleTo(int max, int alpha, int beta, int side) 
{
  if (alpha <= max && beta <= max) return side ? beta : alpha; // If no sclaing is needed, return
  
  float scalar = alpha > beta ? (float) max / (float) alpha : (float) max / (float) beta;
  return (int)(side ? beta * scalar : alpha * scalar);
}

#define TURBO 2.4
#define HIGHSPEED 1.6
#define TORQUE 1

/**
  * Converts inches to quadrature encoder ticks, for the purpose of setting targets in PIDs
  * Usage:
  *  inchesToTicks(10, 3.25, 1, TURBO);
  *
  * @param float unit The number inches to convert to ticks
  * @param float wheelDiameter The diameter of the wheel, in inches
  * @param float gearing The external gear ration (Speed Up => x, Torque Up => 1/x)
  * @param float motorGear The internal gear ratio of the motor (constants TURBO, HIGHSPEED, and TORQUE have been specified)
  **/
float inchesToTicks(float unit, float wheelDiameter, float gearing, float motorGear) 
{
    return 
    (
        (unit / (motorGear * gearing)) / // Cancel out gear ratio
        (wheelDiameter * PI) // Divide by circumfrence to solve for rotations
    ) * 360; // 360 ticks in a rotation
}