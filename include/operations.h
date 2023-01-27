#ifndef OPERATIONS_H
#define OPERATIONS_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       operations.h                                              */
/*    Author:       LoJac10                                                   */
/*    Created:      9 December 2022                                           */
/*    Description:  mechanism operations for auton and driver mode other      */
/*                  than drive operations. drive operations on another file.  */
/*                                                                            */
/*    Modified:     25 Jan 2023                                               */
/*    Author:       LoJac10                                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/


////////////////////////////////////////////////////////////////
//
// function prototype for operation functions for both autonomous and driver control
//
/////////////////////////////////////////////////////////////////////////////////////////

// function prototypes for thread calls for driver period
void set_flywheel(int input);
int flywheel_f(); 
int intake_f();
int indexer_f();

// function prototypes for autonomous period
void intakeAuton_UP( int I, int runTime );
void intakeAuton_DOWN( int I, int runTime );
void flywheelShoot( int I, int runTime );
int roller();




#endif // OPERATIONS_H