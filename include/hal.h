#ifndef HAL_H
#define HAL_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       hal.h                                                     */
/*    Author:       MayorMonty                                                */
/*    Description:  Hardware Abstraction Layer header file                    */
/*                                                                            */
/*    Modified:     25 Jan 2023                                               */
/*    Author:       LoJac10                                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/


void drive(int left, int right);
void driveReset();
int driveOffset();
void driveHandle();
void driveDistance(int inches);
int rotationTicks();
void turn(float rotations);
void mogoSet(int value);
void untilMogoDone();
void mogoUp(); 
void mogoDown();
vex::task handleAll();

#endif // HAL_H