#include "vex.h"
#include "printInertialSensor.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

///////////////////////////////
//
// VEXcode device constructors
//
////////////////////////////////////////////////////

// sensors
inertial inertialSensor = inertial(PORT20);
rotation rotationSensor = rotation(PORT18, true);
optical rollerOptical = optical(PORT17);

// motors
motor lfMotor = motor(PORT1, ratio6_1, false);
motor lbMotor = motor(PORT10, ratio6_1, false);
motor rfMotor = motor(PORT11, ratio6_1, true);
motor rbMotor = motor(PORT19, ratio6_1, true);
motor indexer = motor(PORT12, ratio36_1, false);
motor intake = motor(PORT2, ratio6_1, false);
motor flywheel1 = motor(PORT16, ratio6_1, false);
motor flywheel2 = motor(PORT17, ratio6_1, true);

// motor_groups
motor_group LeftDriveSmart = motor_group(lfMotor, lbMotor);
motor_group RightDriveSmart = motor_group(rfMotor, rbMotor);
motor_group Flywheel = motor_group(flywheel1, flywheel2);

// constant variables for drivetrain
const double wheelTravel = 299.24;          // 3.25-in wheels
const double trackWidth = 349.25;           // 13.75-inches
const double wheelBase = 241.30;            // 9.5-inches
const double externalGearRatio = 2.0;       // 72-tooth gear : 36-tooth gear

// drivetrain
smartdrive Smartdrive = smartdrive(LeftDriveSmart, RightDriveSmart, InertialSensor, wheelTravel, trackWidth, wheelBase, distanceUnits::mm, externalGearRatio);

/////////////////////////////////
//
// VEXcode generated functions
//
///////////////////////////////////////////////
/**
  * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
  * This should be called at the start of your int main function.
  *
  */
void vexcodeInit( void ) 
{
  std::cout << "---------------------------------------"  << std::endl;

  // info out to V5 Brain
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  //info out to terminal
  std::cout << "Device initialization...\n" << std::endl;

  // calibrate the drivetrain Inertial
  wait(200, msec);
  InertialSensor.calibrate();

  // info out to V5 Brain
  Brain.Screen.print("Calibrating Inertial Sensor for Drivetrain");

  // info out to terminal
  std::cout << "Calibrating Inertial Sensor for Drivetrain" << std::endl;

  // wait for the Inertial calibration process to finish
  while ( InertialSensor.isCalibrating() ) 
  {
    wait(25, msec);
  }

  // info out to V5 Brain calibration is complete
  Brain.Screen.print("Calibration is complete");

  // info out to Terminal calibration is complete
  std::cout << "Calibration is complete" << std::endl;
  wait(500, msec);

  // reset the V5 Brain screen now that the calibration is complete
  Brain.Screen.print("Resetting V5 Brain Screen");
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  wait(50, msec);
  Brain.Screen.clearScreen();
  
  // print out stats for inertial sensor
  inertialPrint_Brain();    // print to V5 Brain Screen
  inertialPrint_Terminal(); // print to Terminal
  wait(500, msec);
}