/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       skills.cpp                                                */
/*    Author:       LoJac10                                                   */
/*    Modified:     25 Jan 2023                                               */
/*    Description:  60-Second Skills Routines                                 */
/*                                                                            */
/*    Modified:     LoJac10                                                   */
/*    Date:         25 Jan 2023                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                       
// LFmotor              motor         1
// LBmotor              motor         10
// RFmotor              motor         11
// RBmotor              motor         19   
// Flywheel1            motor         8               
// Flywheel2            motor         9               
// Indexer              motor         7   
// Inertial Sensor      sensor        20        
// Drivetrain           drivetrain    1, 10, 11, 19      
// ---- END VEXCODE CONFIGURED DEVICES ----

// ----| START CONTROLS INFO |----
// L1 Intake In
// L2 Intake Out
// R1 Indexer
// R2 Flywheel Control
// Tank Drive
// ----| END CONTROLS INFO |----

// Include the V5 Library
#include "vex.h"

#include "drive.h"
#include "operations.h"
#include "printInertialSensor.h"
  
// Allows for use of the VEX Library
using namespace vex;

///////////////////////////////////
//
// --- Skills Routine Selector ---
//
///////////////////////////////////////////////////////////

/*-----------------------------------------------------------------------------*/
/** @brief      Skills Red Program                                             */
/*-----------------------------------------------------------------------------*/
void skillsRed() 
{
  // enter your Red Alliance skills program here...

}

/*-----------------------------------------------------------------------------*/
/** @brief      Skills Blue Program                                            */
/*-----------------------------------------------------------------------------*/
void skillsBlue() 
{
  // DESCRIPTION: auton program to get two rollers

  // factor of 5 --> mulitply distance in inches by a factor of 
  // 5 --> i.e. to move 24-in input 120.00 into legDistance variable
  
  std::cout << "++++++++++++++++++++++++++++++++++++++" << std::endl;
  std::cout << "Beginning roller auto program" << std::endl;
  std::cout << "++++++++++++++++++++++++++++++++++++++" << std::endl;

  std::cout << std::flush; // flushes output stream to terminal 

  autoDrive_linear(75, 2);    // Drives the robot forward for 2-inches
  // ...TBD                   // engage intake roller to spin 1st roller
  autoDrive_linear(75, -5);   // Back up robot 5-in
  autoDrive_turn(75, 230);    // turn 230-degrees
  autoDrive_linear(75, 96);   // travel 96-in to other roller

  // report new heading out to terminal
  std::cout << "Inertial Sensor's current heading (deg): " << inertialSensor.heading() << std::endl;
  wait(1000, msec);
}