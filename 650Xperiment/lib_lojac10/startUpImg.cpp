/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       startUpImg.cpp                                            */
/*    Author:       LoJac10                                                   */
/*    Modified:     25 Jan 2023                                               */
/*    Description:  Module to display splash start up image on V5 Brain       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;


void startUpImg() 
{
  /////////////////////////////////////////////////////////////////////////////////////////////////////// 
  //
  //  replace “myimage.bmp” with the name of you image file on the SD card.
  //  make sure the image is less than 480 x 272 (although it will still be cropped to 240 pixels height)
  //  so if you image is called “sahil.png” and fills the screen use 
  //
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  int count = 0;
  while(count < 30)
  {
	  Brain.Screen.drawImageFromFile( "V5_Pirate.png", 0, 0 );
    count = count + 1;
  }

  Brain.Screen.clearScreen();
  // lcdClear();
}