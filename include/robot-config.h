
using namespace vex;

extern brain Brain;

////////////////////////////
//
// VEXcode devices
//
////////////////////////////////////////////////

// controller
extern controller Controller1;

// sensors
extern inertial inertialSensor;
extern rotation rotationSensor;
extern optical rollerOptical;

// motors
extern motor lfMotor;
extern motor lbMotor;
extern motor rfMotor;
extern motor rbMotor;
extern motor indexer;
extern motor intake;
extern motor flywheel1;
extern motor flywheel2;

// motor_group
extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;
extern motor_group Flywheel;


// drivetrain
extern smartdrive Smartdrive;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 **/
void  vexcodeInit( void );