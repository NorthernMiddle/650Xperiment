#ifndef UTIL_H
#define UTIL_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       util.h                                                    */
/*    Author:       MayorMonty                                                */
/*    Description:  utility header file                                       */
/*                                                                            */
/*    Modified:     25 Jan 2023                                               */
/*    Author:       LoJac10                                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/


float fmodf(float x, float y);
float clamp(float val, float min, float max);
int rescaleTo(int max, int alpha, int beta, int side);
float inchesToTicks(float unit, float wheelDiameter, float gearing, float motorGear);


#endif // UTIL_H