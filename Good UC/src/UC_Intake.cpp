#include "vex.h"
#include "UC_Intake.h"

void User_Control::Intake::Control(void){
  while(true){
    if(Controller.ButtonL2.pressing()){
      IntakeLeft  .spin(directionType::fwd, -100, percentUnits::pct);
      IntakeRight .spin(directionType::fwd, -100, percentUnits::pct);
    }//else if(Controller.ButtonL2.pressing() && (!failureState)){
    else if(Controller.ButtonL1.pressing()){
      IntakeLeft  .spin(directionType::fwd, 100, percentUnits::pct);
      IntakeRight .spin(directionType::fwd, 100, percentUnits::pct);
    }
    else{
      IntakeLeft.stop(brakeType::brake);
      IntakeRight.stop(brakeType::brake);
    }
    task::sleep(25);//don't hog the CPU
  }//while(true){
}//void User_Control::Intake::Control(void){