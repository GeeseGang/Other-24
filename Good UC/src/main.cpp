#include "vex.h"
#include "Threads.h"
#include "Autonomous.h"
void pre_auton(void){
  vexcodeInit();
  Gyro.startCalibration();
  Color1.setLightPower(5, percentUnits::pct);
  Competition.autonomous(Auto::Test);
}

int main(void) {
  // Run the pre-auto (to select autonomous)
  pre_auton();

  while(true) {//but this is only cycling through while the robot is disabled

    // If the Robot is enabled, then set up the appropiate threads
    if(Competition.isEnabled()) {

      if(Competition.isAutonomous())
        Auto::Setup_Threads();
      else if(Competition.isDriverControl())
        User_Control::Setup_Threads();

    } // if(Competition.isEnabled()) {

    task::sleep(20);
  } // while(true) {
} // int main(void) {