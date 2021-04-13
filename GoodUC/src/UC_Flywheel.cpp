#include "vex.h"
#include "UC_Flywheel.h"
#include "UC_BallTracking.h"

namespace User_Control {
  namespace Flywheel {
    bool topping = false;
  } // namespace Drive {
} // namespace User_Control {

void User_Control::Flywheel::Control(void){
  bool buttonPressed = false;
  
  while(true){
    
    topping = false;
    if(Controller.ButtonR1.pressing() && !buttonPressed && !Controller.ButtonR2.pressing() && !Controller.ButtonA.pressing()){
      buttonPressed = true;
      topping = true;
      FlywheelMotor.spin(directionType::fwd, 100, percentUnits::pct);
      while(BallTracking::ballArray[1]){
        task::sleep(10);//don't hog the CPU
        if(Controller.ButtonR2.pressing() || Controller.ButtonA.pressing()){
          break;
        }
      }
      task::sleep(150);//TUNE THIS!!! Delay before bringing up another ball for goal topping
      topping = false;
    }
    else if(Controller.ButtonR1.pressing() && buttonPressed){
    }
    else{
      buttonPressed = false;
    }

    if(Controller.ButtonR2.pressing() || Controller.ButtonA.pressing()){//TUNE for cycling
      FlywheelMotor.spin(directionType::fwd, 100, percentUnits::pct);
    }
    else if(BallTracking::sendingUpF){//TUNE 20 pct for sending ball up
      FlywheelMotor.spin(directionType::fwd, 20, percentUnits::pct);
    }
    else{
      FlywheelMotor.stop(brakeType::hold);
    }
    task::sleep(10);//don't hog the CPU
  }//while(true){
}//void User_Control::Intake::Control(void){