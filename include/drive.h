#ifndef DRIVE_H
#define DRIVE_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       drive.h                                                   */
/*    Author:       LoJac10                                                   */
/*    Date:         30 Nov 2022                                               */
/*    Description:  header file for drive functions                           */
/*                                                                            */
/*    Modified:     25 Jan 2023                                               */
/*    Author:       LoJac10                                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/


// function prototypes for driver control period
void set_drive_pow(int l, int r);
void right_arcade_drive();
int arcadeDrive_f();

// function prototypes for autonomous period
void autoDrive_linear(double velocityLevel, double distance_in);
void autoDrive_turn(double velocityLevel, double turnDegree);

#endif // DRIVE_H