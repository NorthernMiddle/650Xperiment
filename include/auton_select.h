#ifndef AUTON_SELECT_H
#define AUTON_SELECT_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton_select.h                                            */
/*    Author:       jpearman                                                  */
/*    Description:  autonomous selection program header file for              */
/*                  selection of multipule auton programs                     */
/*                                                                            */
/*    Modified:     25 Jan 2023                                               */
/*    Author:       LoJac10                                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/


struct button;
void displayButtonControls( int index, bool pressed );
int findButton(  int16_t xpos, int16_t ypos );
void initButtons();
void displayButtonControls( int index, bool pressed );
void userTouchCallbackPressed();
void userTouchCallbackReleased();


#endif // AUTON_SELECT_H