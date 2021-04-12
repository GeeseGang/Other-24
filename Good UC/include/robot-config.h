#ifndef ROBOT_CONFIGURATION
#define ROBOT_CONFIGURATION

using namespace vex;

extern competition Competition;

extern brain Brain;

extern controller Controller;

extern motor FrontLeft   ;
extern motor FrontRight  ;
extern motor RearLeft    ;
extern motor RearRight   ;
extern motor TopLeft     ;
extern motor TopRight    ;
extern motor IntakeLeft  ;
extern motor IntakeRight ;
extern motor FlywheelMotor;
extern motor BottomRollers;
extern motor EjectorMotor     ;

extern line Tracker1;
extern line TopTracker;
extern line BottomTracker;

extern inertial Gyro;
extern optical Color1;
extern distance D1;

extern encoder Left;
extern encoder Right;
/*
extern motor *FwdL   ;
extern motor *FwdR  ;
extern motor *RearL   ;
extern motor *RearR ;
extern motor *TopL     ;
extern motor *TopR    ;
*/

void vexcodeInit(void);   //just don't mess with this

#endif