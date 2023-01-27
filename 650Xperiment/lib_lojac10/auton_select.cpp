/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton_select.cpp                                          */
/*    Author:       jpearman                                                  */
/*    Description:  module for pre-auton auton progam selection               */
/*                                                                            */
/*    Modified:     LoJac10                                                   */
/*    Date:         25 Jan 2023                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;

// storage for our auton selection
int autonomousSelection = -1;

// collect data for on screen button
typedef struct _button 
{                              
  int    xpos;
  int    ypos;
  int    width;
  int    height;
  bool   state;
  vex::color color;
  const char *label;
} button;

// hexidecimal color variables
int hex_Red = 0xE00000;     // red HEX color        /* used for Red Autonomous Selection */
int hex_Blue = 0x0000E0;    // blue HEX color       /* used for Blue Autonomous Selection */
int hex_Green = 0x2228c22;  // green HEX color      /* used to indicate most reliable (MONEY) Autonomous Selection */

// Button definitions
button buttons[] = 
{ 
  // red autonomous program buttons                                    
  {   30,  30, 60, 60,  false, hex_Red, "R1" }, // Red Autonomous Program #1
  {  150,  30, 60, 60,  false, hex_Red, "R2" }, // Red Autonomous Program #2
  {  270,  30, 60, 60,  false, hex_Red, "R3" }, // Red Autonomous Program #3
  {  390,  30, 60, 60,  false, hex_Red, "R4" }, // Red Autonomous Program #4

  // blue autonomous program buttons
  {   30, 150, 60, 60,  false, hex_Blue, "B1" }, // Blue Autonomous Program #1
  {  150, 150, 60, 60,  false, hex_Blue, "B2" }, // Blue Autonomous Program #2
  {  270, 150, 60, 60,  false, hex_Blue, "B3" }, // Blue Autonomous Program #3
  {  390, 150, 60, 60,  false, hex_Blue, "B4" }  // Blue Autonomous Program #4
};

// forward ref
void displayButtonControls( int index, bool pressed );

/*-----------------------------------------------------------------------------*/
/** @brief      Check if touch is inside button                                */
/*-----------------------------------------------------------------------------*/
int findButton(  int16_t xpos, int16_t ypos ) 
{
  int nButtons = sizeof(buttons) / sizeof(button);

  for( int index=0; index < nButtons; index++) 
  {
    button *pButton = &buttons[ index ];
    if( xpos < pButton -> xpos || xpos > (pButton -> xpos + pButton -> width) )
      continue;

    if( ypos < pButton -> ypos || ypos > (pButton -> ypos + pButton -> height) )
      continue;
    
    return(index);
  }

  return (-1);
}

/*-----------------------------------------------------------------------------*/
/** @brief      Init button states                                             */
/*-----------------------------------------------------------------------------*/
void initButtons() 
{
  int nButtons = sizeof(buttons) / sizeof(button);

  for( int index=0; index < nButtons; index++) 
  {
    buttons[index].state = false;
  }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Draw all buttons                                               */
/*-----------------------------------------------------------------------------*/
void displayButtonControls( int index, bool pressed ) 
{
  color c;
  Brain.Screen.setPenColor( color( white ) );    // used to outline buttons and write labels

  for( int i=0; i<sizeof(buttons)/sizeof(button); i++ ) 
  {
    
    if( buttons[i].state )
      c = buttons[i].color;
    else
      c = vex::color::black;

    Brain.Screen.setFillColor( c );

    // button fill
    if( i == index && pressed == true ) 
    {
      c = c + 0x404040; // colors button from black (unselected) to gray (transition color) 
                        // for sec after touch until selection color is loaded into button after selection
                        
      Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, c );
    }
    else
      Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height );

    // outline
    Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, color::transparent );

    // draw label
    if(  buttons[i].label != NULL )
      Brain.Screen.printAt( buttons[i].xpos + 5, buttons[i].ypos + buttons[i].height - 5, buttons[i].label );
  }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been touched                                        */
/*-----------------------------------------------------------------------------*/
void userTouchCallbackPressed()
{
  int index;
  int xpos = Brain.Screen.xPosition();
  int ypos = Brain.Screen.yPosition();
  
  if( (index = findButton( xpos, ypos )) >= 0 ) 
  {
    displayButtonControls( index, true );
  }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been (un)touched                                    */
/*-----------------------------------------------------------------------------*/
void userTouchCallbackReleased() 
{
  int index;
  int xpos = Brain.Screen.xPosition();
  int ypos = Brain.Screen.yPosition();
  
  if( (index = findButton( xpos, ypos )) >= 0 ) 
  {
    // clear all buttons to false, ie. unselected
    initButtons();

    // now set this one as true
    buttons[index].state = true;
    
    // save as auton selection
    autonomousSelection = index;
    
    displayButtonControls( index, false );
  }
}