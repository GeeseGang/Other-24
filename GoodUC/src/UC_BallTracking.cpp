#include "vex.h"
#include "UC_BallTracking.h"

namespace User_Control {
  namespace BallTracking {
    bool sendingUpE = true;
    bool sendingUpF = true;
    bool ejecting = false;
    int allianceColor = 1; //1 is red, -1 is blue
    int ballArray[2] = {0,0};
    bool cycleDelay = false;
  } // namespace Drive {
} // namespace User_Control {



void User_Control::BallTracking::Control(void){
  int currentColor = 0;
  bool keep = true;
  Color1.setLightPower(100, percentUnits::pct);
  while(true){
    cycleDelay = false;
    while(Controller.ButtonA.pressing()){
      ejecting = false;
      sendingUpF = false;
      sendingUpE = false;
    }
    if(Controller.ButtonR2.pressing()){
      ejecting = false;
      sendingUpF = false;
      sendingUpE = false;
      while(Controller.ButtonR2.pressing()){
        ejecting = false;
        
        if(BottomTracker.value(percentUnits::pct) < 69){
          cycleDelay = true;
          ejecting = false;
          while(Color1.value() > 32 && Color1.value() < 155 && Controller.ButtonR2.pressing()){
            task::sleep(10);
          }
          if(Color1.value() < 32 && Color1.value() > 1){
            currentColor = 1;
          }
          else if(Color1.value() > 155){
            currentColor = -1;
          }
          else{
            currentColor = 0;
          }
          if(currentColor == allianceColor * (-1)){
            ejecting = true;
          }
          else{
            ejecting = false;
          }
          cycleDelay = false;
          while(BottomTracker.value(percentUnits::pct) < 69 && ejecting){
            task::sleep(10);
          }
          if(ejecting)
            task::sleep(100);
        }
        
        else{
          cycleDelay = false;
          ejecting = false;
        }
        task::sleep(10);
      }
    }
    if(TopTracker.value(percentUnits::pct) < 67){
      ballArray[1] = 1;
    }
    else{
      ballArray[1] = 0;
    }
    if(BottomTracker.value(percentUnits::pct) < 69){
      ballArray[0] = 1;
    }
    else{
      ballArray[0] = 0;
    }


    if(ballArray[0] == 1){
      task::sleep(100);
      if(Color1.value() < 32 && Color1.value() > 1){
        currentColor = 1;
      }
      else if(Color1.value() > 155){
        currentColor = -1;
      }
      else{
        currentColor = 0;
      }
    }
    else{
      currentColor = 0;
    }


    if(currentColor == allianceColor * (-1)){
      keep = false;
    }
    else{
      keep = true;
    }


    if(ballArray[0] == 1 && ballArray[1] == 0 && keep){
      sendingUpF = true;
      ejecting = false;
      while(ballArray[1] == 0){
        if(TopTracker.value(percentUnits::pct) < 67){
          ballArray[1] = 1;
        }
        if(Controller.ButtonA.pressing() || Controller.ButtonR2.pressing()){
          break;
        }
        task::sleep(10);
      }
    }
    if(!keep){
      sendingUpF = false;
      ejecting = true;
      while(ballArray[0] == 1){
        if(BottomTracker.value(percentUnits::pct) > 67){
          ballArray[0] = 0;
        }
        if(Controller.ButtonA.pressing()){
          break;
        }
        task::sleep(10);
      }
    }
    else{
      ejecting = false;
    }
    if(ballArray[0] == 0){
      sendingUpE = true;
    }
    else{
      sendingUpE = false;
    }
    if(ballArray[1] == 1){
      sendingUpF = false;
    }
    // red ~ 20
    //empty ~ 80
    //blue ~200
    task::sleep(10);//don't hog the CPU
  }//while(true){
}//void User_Control::Intake::Control(void){