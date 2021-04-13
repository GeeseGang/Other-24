#include "vex.h"

competition Competition = competition();

brain Brain = brain();

controller Controller =  controller( controllerType::primary);
/**************************************************************************

Controller layout (with temporary caveman automation while Ani tests out good automation on the 15)

Index finger is 1, middle finger is 2
A is on the right, B is on the Bottom, X is on the Top, Y is on the right

Drive controls:
Left Joystick: Foward/ Back
Right Joystick: Turn
B: Lock the drive

Driver controlled robot functions:
L1: Intake in
L2: Intake out
R1: Flywheel out (SCORE!)
R2: Eject


Routines / something broke:
A: Eject 1 ball from storage per tap
X: change Intake out so it also makes balls move down from storage (we can't score in the top bc something broke)
Y while driving foward: coast one motor on drive to make it even(Drive broke)

Tuning:
Left: slow down intakes & print values to the screen (speeds up after it hits 5)
Down: slow down bottom rollers & print values to the screen(speeds up after it hits 5)
Right: slow down ejector & print values to the screen(speeds up after it hits 5)
Up: slow down flywheel & print values to the screen(speeds up after it hits 5)

**************************************************************************/

motor FrontLeft    =  motor( PORT2, true  );
//motor *FwdL = &FrontLeft;
motor FrontRight   =  motor( PORT9, false );
//motor *FwdR = &FrontRight;
motor RearLeft     =  motor( PORT4, true  );
motor RearRight    =  motor( PORT8, false );
motor TopLeft      =  motor( PORT13, false  );
motor TopRight     =  motor( PORT19, true );

motor FlywheelMotor     =  motor( PORT6, true);
motor BottomRollers     =  motor( PORT3, true);
motor EjectorMotor           =  motor( PORT11, false);

motor IntakeLeft   =  motor( PORT5, false);
motor IntakeRight  =  motor( PORT7, true);

line Tracker1 =  line(Brain.ThreeWirePort.G);
line TopTracker =  line(Brain.ThreeWirePort.F);
line BottomTracker =  line(Brain.ThreeWirePort.E);

inertial Gyro =  inertial(PORT14);
optical Color1 = optical(PORT1);
distance D1 = distance(PORT18);

encoder Right = encoder(Brain.ThreeWirePort.A);
encoder Left = encoder(Brain.ThreeWirePort.C);

/*
left: C&D
right: A&B
*/

void vexcodeInit(void) {      //just leave this alone
}