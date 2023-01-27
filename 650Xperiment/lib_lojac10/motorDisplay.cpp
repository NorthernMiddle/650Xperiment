/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       motorDisplay.cpp                                          */
/*    Author:       jpearman                                                  */
/*    Created:      Sat Nov 02 2019                                           */
/*    Description:  A task that just displays motor velocity and position     */
/*                  The motors that are part of a motor group and/or          */
/*                  drivetrain can still be accessed directly.                */
/*                                                                            */
/*    Modified:     LoJac10                                                   */
/*    Date:         25 Jan 2023                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;

int motorDisplay() 
{
  while(true) 
  {
    // display some useful info
    Brain.Screen.setCursor(2,1);
    Brain.Screen.print( "  lfMotor    speed: %4.0f   position: %6.2f", lfMotor.velocity( percent ), lfMotor.position( rev ) );
    Brain.Screen.newLine();
    Brain.Screen.print( "  lbMotor    speed: %4.0f   position: %6.2f", lbMotor.velocity( percent ), lbMotor.position( rev ));
    Brain.Screen.newLine();
    Brain.Screen.print( "  rfMotor    speed: %4.0f   position: %6.2f", rfMotor.velocity( percent ), rfMotor.position( rev ));
    Brain.Screen.newLine();
    Brain.Screen.print( "  rbMotor    speed: %4.0f   position: %6.2f", rbMotor.velocity( percent ), rbMotor.position( rev ));
    Brain.Screen.newLine();
    Brain.Screen.newLine();

    // motor group velocity and position is returned for the first motor in the group
    Brain.Screen.print( "  leftDrive  speed: %4.0f   position: %6.2f", LeftDriveSmart.velocity( percent ), LeftDriveSmart.position( rev ));
    Brain.Screen.newLine();
    Brain.Screen.print( "  rightDrive speed: %4.0f   position: %6.2f", RightDriveSmart.velocity( percent ), RightDriveSmart.position( rev ));
    Brain.Screen.newLine();
    Brain.Screen.newLine();

    // drivetrain velocity is the average of the motor velocities for left and right
    Brain.Screen.print( "  Smartdrive speed: %4.0f", Smartdrive.velocity( percent ) );
    Brain.Screen.newLine();

    // no need to run this loop too quickly
    wait( 20, timeUnits::msec );
  }

  return 0;
}

// ----------------------------------------------------------------------------
// main program entry and drive control
// ----------------------------------------------------------------------------
int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // set 10 second timeout for robot drive movements
  Smartdrive.setTimeout(10, seconds);

  // set the speed used for drive turns
  Smartdrive.setTurnVelocity(50, percent);

  // start the display task
  task displayTaskInstance( motorDisplay );

  // loop forever
  while( true ) 
  {
    // Buitton A is used to rotate drive 90 degrees
    if( Controller1.ButtonA.pressing() ) 
    {
      // tell drivetrain to rotate 90 deg
      Smartdrive.turnFor( 90, degrees );
      // wait for it to be done
      while( Smartdrive.isMoving() )
        wait( 10, timeUnits::msec );
    }
    else 
    {
      // not rotating, then we can drive using controller

      // read percent from controller axis
      int leftSpeed  = Controller1.Axis3.position();
      int rightSpeed = Controller1.Axis2.position();
      // deadband
      if( abs(leftSpeed)  < 10 ) leftSpeed  = 0;
      if( abs(rightSpeed) < 10 ) rightSpeed = 0;

      // send to motors
      LeftDriveSmart.spin( forward, leftSpeed, percent );
      RightDriveSmart.spin( forward, rightSpeed, percent );
    }
        
    // no need to run this loop too quickly
    wait( 20, timeUnits::msec );
  }

  return 0;
}