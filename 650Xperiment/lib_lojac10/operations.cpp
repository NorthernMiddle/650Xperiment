/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       operations.cpp                                            */
/*    Author:       LoJac10                                                   */
/*    Created:      30 Nov 2022                                               */
/*    Description:  Competition VRC Template for 650X "Xray". Template        */
/*                  includes options to select autonomous programs using      */
/*                  Jpearman 'buttons' & 'autonSelect' module.                */
/*                                                                            */
/*    Modified:     LoJac10                                                   */
/*    Date:         25 Jan 2023                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;

const int SCALE = 120;
const int DEADBAND = 15;
bool manual_mode = true;      // declare state variable for manual override


//////////////////////////////////////
//
// set operations variables
//
///////////////////////////////////////////////////////////////
int speeds[] = {0, 127, 115, 110, 90};
int speed = 0;
bool indexer_pressed = false;
int target = 0;
int indexer_timer = 0;

int count = 0;
bool last_r2 = false;


/**
  * DESCRIPTION: autonomous drive for linear movements
  * @PARA: velocity level of motors in percentage format
  * @PARA: distance of movement in inches
  *
  */
void autoDrive_linear(double velocityLevel, double distance_in)
{
  // begin linear movement
  std::cout << "Begin "<< distance_in << "-in movement \n" << std::endl;
  wait(500, msec);
  
  double travelDistance_in = distance_in * 5; 
  Smartdrive.driveFor(directionType::rev, travelDistance_in, distanceUnits::in, velocityLevel, velocityUnits::pct, true);
  waitUntil((travelDistance_in >= travelDistance_in));
  wait(500, msec);
  Smartdrive.stop(brake);

  // end linear movement
  std::cout << "End "<< distance_in << "-in movement \n" << std::endl;
  wait(500, msec);
}



/**
  * DESCRIPTION: autonomous drive for turn movements
  * @PARA: velocity level of motors in percentage format
  * @PARA: degree of movement in degrees
  *
  */
void autoDrive_turn(double velocityLevel, double turnDegree)
{
  // begin turn movement
  std::cout << "Begin "<< turnDegree << " degree turn movement \n" << std::endl;
  wait(500, msec);

  // resets heading and reports out to terminal
  Smartdrive.setHeading(0, rotationUnits::deg);
  std::cout << "Inertial Sensor's current heading (deg): " << inertialSensor.heading() << " \n" << std::endl;
  wait(500, msec);

  /* turns the robot to the right
  Smartdrive.setTurnVelocity(velocityLevel, velocityUnits::pct);
  Smartdrive.turnFor(left, turnDegree, rotationUnits::deg, false);
  */

  Smartdrive.turnToHeading(turnDegree, rotationUnits::deg, velocityLevel, velocityUnits::pct, false);
  // waits until the motor reaches turnDegree turn threshold and stops the drivetrain motors
  // waitUntil((InertialSensor.rotation(degrees) >= turnDegree));
  Smartdrive.stop(brake);
  wait(1000, msec);

  // reports out new sensor heading
  // ends turn movement
  std::cout << "Inertial Sensor heading (deg): " << inertialSensor.heading() << " \n" << std::endl;
  std::cout << "Completed "<< turnDegree << " degree turn movement \n" << std::endl;
  wait(500, msec);
  
}



//////////////////////////////////////
//
// set intake voltage DRIVER
// L1 and L2 Button Function Voltage
//
///////////////////////////////////////////////////////////////
/* void set_intake(int input) 
{
  Intake.spin(fwd, input * SCALE, voltageUnits::mV);
}
*/

//////////////////////////////////////
//
// set intake voltage DRIVER
// Left Toggle Function Voltage
//
///////////////////////////////////////////////////////////////
void set_intake_pow( int I )
{
  intake.spin(fwd, I * SCALE, voltageUnits::mV);
}


//////////////////////////////////////
//
// set indexer voltage DRIVER
//
///////////////////////////////////////////////////////////////
void set_indexer(int pos, int speed) 
{
  indexer.startRotateTo(pos, rotationUnits::deg, speed, velocityUnits::pct);
}

//////////////////////////////////////
//
// set flywheel voltage DRIVER
//
///////////////////////////////////////////////////////////////
void set_flywheel(int input) 
{
  flywheel1.spin(fwd, input * SCALE, voltageUnits::mV);
  flywheel2.spin(fwd, input * SCALE, voltageUnits::mV);
}


//////////////////////////////////////
//
// Intake function DRIVER
// L1 Intake In : L2 Intake Out
//
///////////////////////////////////////////////////////////////
/* 
int intake_f()
{
  int count = 0;
  while(true)
  {
    Brain.Screen.setCursor(2,1);
    Brain.Screen.print("Intake has iterated %d times", count);
    count++;

    if (Controller1.ButtonL1.pressing()) 
    {
      set_intake(127); 
    } 
    else if (Controller1.ButtonL2.pressing()) 
    {
      set_intake(-127);
    } 
    else 
    {
      set_intake(0);
    }

    //----------------------------------------------------------------------         
    // You must sleep threads by using the 'this_thread::sleep_for(unit in
    // msec)' command to prevent this thread from using all of the CPU's
    // resources.
    //---------------------------------------------------------------------- 
    this_thread::sleep_for( 25 );
  }

  //----------------------------------------------------------------------                                                           
  //  A threads's callback must return an int, even though the code will  
  //  never get here. You must return an int here. Threads can exit, but  
  //  this one does not.                                                                                                              
  //----------------------------------------------------------------------
  return( 0 );
} 
*/



//////////////////////////////////////
//
// Intake function DRIVER
// Left Toggle Stick
//
///////////////////////////////////////////////////////////////
int intake_f()
{
  int count = 0;
  while(true)
  {
    Brain.Screen.setCursor(2,1);
    Brain.Screen.print("Intake has iterated %d times", count);
    count++;

    int l_joy = abs(Controller1.Axis3.value()) > DEADBAND ? Controller1.Axis3.value() : 0;
    set_intake_pow( l_joy );
  
    //----------------------------------------------------------------------
    // You must sleep threads by using the 'this_thread::sleep_for(unit in
    // msec)' command to prevent this thread from using all of the CPU's
    // resources.
    //----------------------------------------------------------------------
    this_thread::sleep_for( 25 );
  }

  //----------------------------------------------------------------------                                                           
  //  A threads's callback must return an int, even though the code will  
  //  never get here. You must return an int here. Threads can exit, but  
  //  this one does not.                                                                                                              
  //----------------------------------------------------------------------
  return( 0 );
}

//////////////////////////////////////
//
// Flywheel function DRIVER
//
///////////////////////////////////////////////////////////////
int flywheel_f()
{
  int count = 0;
  while( true )
  {
    Brain.Screen.setCursor(3,1);
    Brain.Screen.print("Flywheel has iterated %d times", count);
    count++;

    if (Controller1.ButtonR2.pressing() and !last_r2) 
    {
      if (speed >= 4) 
      {
        speed = 0;
      } 
      else 
      {
        speed++;
      }
    } 

    set_flywheel(speeds[speed]);

    printf("\n %d", speeds[speed]);
    last_r2 = Controller1.ButtonR2.pressing();

    //----------------------------------------------------------------------
    // You must sleep threads by using the 'this_thread::sleep_for(unit in
    // msec)' command to prevent this thread from using all of the CPU's
    // resources.
    //----------------------------------------------------------------------
    this_thread::sleep_for( 25 );
  }

  //----------------------------------------------------------------------                                                           
  //  A threads's callback must return an int, even though the code will  
  //  never get here. You must return an int here. Threads can exit, but  
  //  this one does not.                                                                                                              
  //----------------------------------------------------------------------
  return( 0 );
}


//////////////////////////////////////
//
// Indexer function DRIVER
//
///////////////////////////////////////////////////////////////
int indexer_f()
{
  int count = 0;
  while( true )
  {
    Brain.Screen.setCursor(4,1);
    Brain.Screen.print("Indexer has iterated %d times", count);
    count++;

    if (Controller1.ButtonR1.pressing())
    {
      indexer_pressed = true;
    }
    if (indexer_pressed) 
    {
      if (indexer_timer <= 17) 
      {
        target = 120;
        indexer_timer++;
      } 
      else 
      {
        indexer_timer = 0;
        target = 0;
        indexer_pressed = false;
      }
    }
      
    set_indexer(target, 200);

    //----------------------------------------------------------------------
    // You must sleep threads by using the 'this_thread::sleep_for(unit in
    // msec)' command to prevent this thread from using all of the CPU's
    // resources.
    //----------------------------------------------------------------------
    this_thread::sleep_for( 25 );
  }

 
  //----------------------------------------------------------------------                                                           
  //  A threads's callback must return an int, even though the code will  
  //  never get here. You must return an int here. Threads can exit, but  
  //  this one does not.                                                                                                              
  //----------------------------------------------------------------------
  return( 0 );
}


// ++++++++++++++++++++++++++++++++++++++++++++++++++++ AUTON OPERATIONS PROGRAMS ++++++++++++++++++++++++++++++++++++++++++++++++++++ 
//
// These function and thread calls will be used to control your robot during 
// the autonomous programs and skills runs.
//
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//////////////////////////////////////
//
// Intake function AUTON
//
///////////////////////////////////////////////////////////////
void intakeAuton_UP( int I, int runTime ){
  Intake.spin(directionType::fwd, I * SCALE, voltageUnits::mV);
  wait(runTime, msec);
  Intake.stop();
}

void intakeAuton_DOWN( int I, int runTime ){
  Intake.spin(directionType::rev, I * SCALE, voltageUnits::mV);
  wait(runTime, msec);
  Intake.stop();
  
}

//////////////////////////////////////
//
// Flywheel function AUTON
//
///////////////////////////////////////////////////////////////
void flywheelShoot( int I, int runTime ){
  Flywheel.spin(directionType::fwd, I * SCALE, voltageUnits::mV );
  wait(runTime, msec);
  Flywheel.stop();

}