#include "vex.h"
#include "UC_Ejector.h"
#include "UC_BallTracking.h"
#include "UC_Flywheel.h"

void User_Control::Ejector::Control(void){
  while(true){
    if(Controller.ButtonA.pressing() || (BallTracking::sendingUpF && !Flywheel::topping)){
      EjectorMotor.spin(directionType::fwd, 100, percentUnits::pct);
    }
    else if(BallTracking::ejecting){
      while(BallTracking::ejecting){
        EjectorMotor.spin(directionType::fwd, -100, percentUnits::pct);
        task::sleep(25);
        if(Controller.ButtonA.pressing()){
          break;
        }
      }
      task::sleep(700);//TUNE this
    }
    else{
      EjectorMotor.stop(brakeType::hold);
    }

    task::sleep(25);//don't hog the CPU
  }//while(true){
}//void User_Control::Intake::Control(void){int onRed = 1;