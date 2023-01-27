/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       encoderDisplay.cpp                                        */
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

void resetDriveEncoders()
{
  lfMotor.setPosition(0, rotationUnits::raw);
  lbMotor.setPosition(0, rotationUnits::raw);
  rfMotor.setPosition(0, rotationUnits::raw);
  rbMotor.setPosition(0, rotationUnits::raw);
}


double *driveOffsetCal()
{
  // ** side diff **
  double leftsideDiff = lfMotor.position(rotationUnits::raw) - lbMotor.position(rotationUnits::raw);
  double rightsideDiff = rfMotor.position(rotationUnits::raw) - rbMotor.position(rotationUnits::raw);

  // ** cross diff **
  double frontcrossDiff = lfMotor.position(rotationUnits::raw) - rfMotor.position(rotationUnits::raw);
  double backcrossDiff = lbMotor.position(rotationUnits::raw) - rbMotor.position(rotationUnits::raw);

  double arr[4] = {leftsideDiff, rightsideDiff, frontcrossDiff, backcrossDiff};

  return arr;
}

void driveOffsetDisplay()
{
 
  double *arr = driveOffsetCal();

  // clear screen to display encoder info
  Brain.Screen.clearScreen();

  // display some useful info
  Brain.Screen.setCursor(2,1);
  Brain.Screen.print( "  LSdiff: %4.0f   position: %6.2f", arr[0] );
  Brain.Screen.newLine();
  Brain.Screen.print( "  RSdiff: %4.0f   position: %6.2f", arr[1] );
  Brain.Screen.newLine();
  Brain.Screen.print( "  FCdiff: %4.0f   position: %6.2f", arr[2] );
  Brain.Screen.newLine();
  Brain.Screen.print( "  BCdiff: %4.0f   position: %6.2f", arr[3] );
  Brain.Screen.newLine();
  Brain.Screen.newLine();

}