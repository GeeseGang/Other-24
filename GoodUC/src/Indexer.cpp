#include "vex.h"
#include "Indexer.h"
#include "Auto_Intake_Functions.h"

namespace Driver {
  namespace Intake {
  int ballArray[2]={0,0};
  int val =0;
  int onRed=1;
  bool ballEntered =false;
  }
}

int Driver::Intake::get_Ball_Status(int pos) {
  updateArray();
  task::sleep(10);
  if(ballArray[pos]==1)
  return 1;
  else
  return 0;
}// end of get_Ball_Status()
int Driver::Intake::getOpenSlot() {
  for(int i=1; i>=0; i--) {
     if(ballArray[i]==0)
     {
       Brain.Screen.printAt(100,170, "openSlot: %2d", i);
       return i;
     }
  }

  
return -1;
}//end of getOpenSlot()

int Driver::Intake::getFilledSlot() {
  for(int i =1; i>=0; i--) {
    if(ballArray[i]==1)
    {
      return i;
    }
  }
  return -1;
}

void Driver::Intake::updateArray() {

  if(BottomTracker.value(percentUnits::pct)<69)
  {
    ballArray[0]=1;
  }
  else 
  {
    ballArray[0]=0;
  }
  if(TopTracker.value(percentUnits::pct)<67)
  {
    ballArray[1]=1;
  }
  else 
  {
    ballArray[1]=0;
  }

}// end of updateArray()

void Driver::Intake::Indexer() {
  while(true) {
     Brain.Screen.printAt(100, 130, "BottomTracker value: %2d", BottomTracker.value(percentUnits::pct));
     Brain.Screen.printAt(100, 150, "TopTracker value: %2d", TopTracker.value(percentUnits::pct));
    if(Controller.ButtonL1.pressing()) {
      
      IntakeRight.spin(directionType::fwd, 100, velocityUnits::pct);
      IntakeLeft.spin(directionType::fwd, 100, velocityUnits::pct);
      
      
      while(Controller.ButtonL1.pressing()) {
       updateArray();
       val =getOpenSlot();
    
        if(val ==1 ) {
          while(TopTracker.value(percentUnits::pct)> 65 && Controller.ButtonL1.pressing()) {

            IntakeRight.spin(directionType::fwd, 100, velocityUnits::pct);
            IntakeLeft.spin(directionType::fwd, 100, velocityUnits::pct);
            BottomRollers.spin(directionType::fwd, 100, velocityUnits::pct);
            FlywheelMotor.spin(directionType::fwd, 20, velocityUnits::pct);
            EjectorMotor.spin(directionType::fwd, 100, velocityUnits::pct);
          }
          FlywheelMotor.stop(brakeType::hold);
          EjectorMotor.stop(brakeType::hold);
          BottomRollers.stop(brakeType::hold);
        }// end of val ==1

        else if(val==0) {
          while(BottomTracker.value(percentUnits::pct)> 69 && Controller.ButtonL1.pressing()) {
           BottomRollers.spin(directionType::fwd, 100, velocityUnits::pct);
           IntakeRight.spin(directionType::fwd, 100, velocityUnits::pct);
           IntakeLeft.spin(directionType::fwd, 100, velocityUnits::pct);
           EjectorMotor.spin(directionType::fwd, 100, velocityUnits::pct);
          }
          FlywheelMotor.stop(brakeType::hold);
          EjectorMotor.stop(brakeType::hold);
          BottomRollers.stop(brakeType::hold);
        }// end of val==0

        else {
        IntakeRight.spin(directionType::fwd, 100, velocityUnits::pct);
        IntakeLeft.spin(directionType::fwd, 100, velocityUnits::pct);
        FlywheelMotor.stop(brakeType::hold);
        EjectorMotor.stop(brakeType::hold);
        BottomRollers.stop(brakeType::hold);
        } 
       
       
        task::sleep(10);
      }//end of while(Controller.ButtonR1.pressing())

      IntakeRight.stop(brakeType::coast);
      IntakeLeft.stop(brakeType::coast);
      BottomRollers.stop(brakeType::coast);
      FlywheelMotor.stop(brakeType::hold);
      EjectorMotor.stop(brakeType::coast);
    }// end of if(Controller.ButtonR1.pressing())

    Controller.ButtonR1.pressed(Driver::Intake::goalTopper);
    updateArray();
    task::sleep(10);
  /*if(Controller.ButtonL1.pressing()) {
    while(Controller.ButtonL1.pressing()) {
   Auto::Intake::Intake_On(100);
   
    }
   Auto::Intake::Stop_Intakes();
  
  */
   
  }//end of while(true)
 
}//end of Indexer()

void Driver::Intake::goalTopper() {
 updateArray();
 int val2 = getFilledSlot();
 
 if(val2 ==1) {                                                          // assume that as soon as one ball leaves another will come in, if not the case, just press R1 to push it up
    FlywheelMotor.spin(directionType::fwd, 100, velocityUnits::pct);
    task::sleep(500);
    
 } // end of val2==1

 else if(val2==0) {
   while(TopTracker.value(percentUnits::pct)>67) {
      BottomRollers.spin(directionType::fwd, 80, velocityUnits::pct);
      //TopRoller.spin(directionType::fwd, 50, velocityUnits::pct);
      EjectorMotor.spin(directionType::fwd, 80, velocityUnits::pct);
      task::sleep(10);
   }
 }// end of val2==0

 BottomRollers.stop(brakeType::coast);
 EjectorMotor.stop(brakeType::coast);
 FlywheelMotor.stop(brakeType::brake);
}// end of goalTopper()