#include "vex.h"
#include "UC_Ejector.h"
#include "UC_BallTracking.h"
#include "UC_Flywheel.h"

void User_Control::Ejector::Control(void){
  while(true){
    if(Controller.ButtonA.pressing() || (BallTracking::sendingUpF && !Flywheel::topping) || (Controller.ButtonR2.pressing() && !BallTracking::ejecting && !BallTracking::cycleDelay) ){
      EjectorMotor.spin(directionType::fwd, 100, percentUnits::pct);
    }
    else if(BallTracking::ejecting && !BallTracking::cycleDelay){
      while(BallTracking::ejecting){
        EjectorMotor.spin(directionType::fwd, -100, percentUnits::pct);
        task::sleep(10);
        if(Controller.ButtonA.pressing() || BallTracking::cycleDelay){
          break;
        }
      }
      //if(!BallTracking::cycleDelay)
      task::sleep(100);//TUNE this
      if(BottomRollers.velocity(percentUnits::pct) < 4){
        EjectorMotor.spin(directionType::fwd, 100, percentUnits::pct);
        task::sleep(350);
        EjectorMotor.spin(directionType::fwd, -100, percentUnits::pct);
        task::sleep(200);
      }
    }
    else{
      EjectorMotor.stop(brakeType::hold);
    }

    task::sleep(10);//don't hog the CPU
  }//while(true){
}//void User_Control::Intake::Control(void){int onRed = 1;