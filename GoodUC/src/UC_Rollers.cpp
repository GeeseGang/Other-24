#include "vex.h"
#include "UC_Rollers.h"
#include "UC_BallTracking.h"
#include "UC_Flywheel.h"

void User_Control::Rollers::Control(void){
  while(true){
    if(Controller.ButtonA.pressing() || (Controller.ButtonR2.pressing() && !BallTracking::cycleDelay) || BallTracking::sendingUpE || (BallTracking::sendingUpF && !Flywheel::topping) || (BallTracking::ejecting && !BallTracking::cycleDelay)){
      BottomRollers.spin(directionType::fwd, 100, percentUnits::pct);
    }
    else{
      BottomRollers.stop(brakeType::hold);
    }
    task::sleep(10);//don't hog the CPU
  }//while(true){
}//void User_Control::Intake::Control(void){