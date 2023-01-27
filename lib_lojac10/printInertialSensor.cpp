/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       inertialSensorDisplay.cpp                                 */
/*    Author:       NMS_RP                                                    */
/*    Created:      03 Dec 2019                                               */
/*    Description:  module for function definitions for user control          */
/*                  drive functions                                           */
/*                                                                            */
/*    Modified:     LoJac10                                                   */
/*    Date:         25 Jan 2023                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;

void inertialSensorDisplay_Brain( void )
{
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  std::cout << "---------------------------------------"  << std::endl;
  
  // Prints the pitch ( rotation around the side to side axis)
  Brain.Screen.print("Pitch Orientation (deg): ");
  Brain.Screen.print((inertialSensor.orientation(pitch, degrees)));
  Brain.Screen.newLine();

  // Prints the acceleration of the y-axis.
  Brain.Screen.print("Y-axis Acceleration (G): ");
  Brain.Screen.print(inertialSensor.acceleration(yaxis));
  Brain.Screen.newLine();
  std::cout << "Y-axis Acceleration (G): " << inertialSensor.acceleration(yaxis) << std::endl;

  // Prints the gyro rate of the y-axis
  Brain.Screen.print("Y-axis Gyro Rate (DPS): ");
  Brain.Screen.print(inertialSensor.gyroRate(yaxis, dps));
  Brain.Screen.newLine();

  // Print the current heading in degrees
  Brain.Screen.print("Inertial Sensor's current heading (deg): ");
  Brain.Screen.print(inertialSensor.heading());
  Brain.Screen.newLine();

  // Print the current angle of rotation in degrees
  Brain.Screen.print("Inertial Sensor's current angle of rotation (deg): ");
  Brain.Screen.print(inertialSensor.rotation());
  wait(0.2, seconds);
  std::cout << "---------------------------------------"  << std::endl;
}

void inertialSensorDisplay_Terminal( void )
{
  std::cout << "INERTIAL SENSOR STATS" << std::endl;
  std::cout << "---------------------------------------" << std::endl;
  
  // Prints the pitch ( rotation around the side to side axis)
  std::cout << "Pitch Orientation (deg): " << inertialSensor.orientation(pitch, degrees) << std::endl;

  // Prints the acceleration of the y-axis.
  std::cout << "Y-axis Acceleration (G): " << inertialSensor.acceleration(yaxis) << std::endl;

  // Prints the gyro rate of the y-axis
  std::cout << "Y-axis Gyro Rate (DPS): " << inertialSensor.gyroRate(yaxis, dps) << std::endl;

  // Print the current heading in degrees
  std::cout << "Inertial Sensor's current heading (deg): " << inertialSensor.heading() << std::endl;
  
  // Print the current angle of rotation in degrees
  std::cout << "Inertial Sensor's current angle of rotation (deg): " << inertialSensor.rotation() << std::endl;
  std::cout <<"---------------------------------------"  << std::endl;
}