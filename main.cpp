/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/**
 * main.c - Entry point for our codebase
 * The structure of the project is as follows:
 *
 * lib/
 *   hal.c - Hardware Abstraction Layer
 *   lcd.c - LCD Library
 *   motor.c - Motor Algorithmns
 *   pid.c - General purpose PID (Super simple, basically just makes the calculation)
 *   rerun.c - Contains code for the rerun system
 * routines/
 *   auton.c - Routines for the 15-second autonomous
 *   skills.c - Routines for the 60-second programming skills
 *
 **/

#include "vex.h"
using namespace vex;

#include "state.h"
#include "util.h"
#include "hal.h"
#include "rerun.h"
#include "auton.h"
#include "skills.h"
#include "operations.h"
#include "auton_select.h"
#include "alliance_select.h"


// #include "lib\lcd.c"


// A global instance of competition
competition Competition;

// state variable for alliance status
// 0 --> RED ALLIANCE 1--> BLUE ALLIANCE
int allianceStatus;

// state variable for autonomous selection
int autonomousProgramSelection = -1;

// state variable for escape from auton selection operation
// int manual_mode = false;


void pre_auton(void) 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  bStopTasksBetweenModes = false;
  bDisplayCompetitionStatusOnLcd = false;

  startTask(handleAll);

  lcdStartup();
  robotConfigure();

  startTask(lcdDebug);

}


void autonomous(void) 
{
  writeDebugStreamLine("autonomous()");
  driveReset();
  stopTask(usercontrol);

  if (match.type == 0) 
  {
    goAuton(match.routine);
  } 
  else if (match.type == 2) 
  {
    goSkills(match.routine);
  }
}


void usercontrol(void) 
{
  writeDebugStreamLine("usercontrol()");
  driveReset();
  stopTask(autonomous);
  clearTimer(T1); // Used for rerun

  while (true) 
  {
    // Mogo Lift
    if (vexRT[Btn6U] || vexRT[Btn5U]) robot.mogo = UP;
    if (vexRT[Btn6D] || vexRT[Btn5D]) robot.mogo = DOWN;

    // Drive
    int forward = abs(vexRT[Ch3]) > 60 ? vexRT[Ch3] * 0.8 : 0,
        turn = abs(vexRT[Ch4]) > 90 ? vexRT[Ch4] * 0.4 : 0,
        left = forward + turn,
        right = forward - turn;

    robot.leftDrive  = sgn(left)  * rescaleTo(127, abs(left), abs(right), 0);
    robot.rightDrive = sgn(right) * rescaleTo(127, abs(left), abs(right), 1);

    if (match.type == 3) 
    {
      rerunHandle();
    }

    wait(20, msec); // Sleep the task for a short amount of time to prevent wasted resources.
  }
}

///////////////////////////////////////////////////////////////
//
// Main will set up the competition functions and callbacks.
//
///////////////////////////////////////////////////////////////
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) 
  {
    wait(100, msec);
  }
}
