#include "vex.h"
#include "UC_BallTracking.h"

namespace User_Control {
  namespace BallTracking {
    bool sendingUpE = true;
    bool sendingUpF = true;
    bool ejecting = false;
    int allianceColor = 1; //1 is red, -1 is blue
    int ballArray[2] = {0,0};
  } // namespace Drive {
} // namespace User_Control {



void User_Control::BallTracking::Control(void){
  int currentColor = 0;
  bool keep = true;
  Color1.setLightPower(10, percentUnits::pct);
  while(true){
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
      if(Color1.value() < 50 && Color1.value() > 1){
        currentColor = 1;
      }
      else if(Color1.value() > 150){
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
        task::sleep(25);
      }
    }
    if(!keep){
      ejecting = true;
      while(ballArray[0] == 1){
        if(BottomTracker.value(percentUnits::pct) > 67){
          ballArray[0] = 0;
        }
        task::sleep(25);
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
    task::sleep(25);//don't hog the CPU
  }//while(true){
}//void User_Control::Intake::Control(void){