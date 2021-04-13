#include "vex.h"
#include "Auto_Intake_Functions.h"
#include "UC_BallTracking.h"
namespace Auto {
  namespace Intake {
    int blue_Counter=0;
    int eject_Counter=0;
    int red_Counter=0;
    int ballArray[2]={0,0};
    int val =0;
    int onRed=1;
    bool ballEntered =false;
  }
}

int Auto::Intake::get_Ball_Status(int pos) {
  updateArray();
  task::sleep(10);
  if(ballArray[pos]==1)
  return 1;
  else
  return 0;
}// end of get_Ball_Status()
int Auto::Intake::getOpenSlot() {
  for(int i=1; i>=0; i--) {
     if(ballArray[i]==0)
     {
       Brain.Screen.printAt(100,170, "openSlot: %2d", i);
       return i;
     }
  }


return -1;
}//end of getOpenSlot()

int Auto::Intake::getFilledSlot() {
  for(int i =1; i>=0; i--) {
    if(ballArray[i]==1)
    {
      return i;
    }
  }
  return -1;
}

void Auto::Intake::updateArray() {

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


void Auto::Intake::Intake_On(int pow) {
  IntakeRight.spin(directionType::fwd,pow, velocityUnits::pct);
  IntakeLeft.spin(directionType::fwd,pow, velocityUnits::pct);
}// end of Intake_On(int pow)

void Auto::Intake::Stop_Intakes() {
  IntakeRight.stop(brakeType::brake);
  IntakeLeft.stop(brakeType::brake);
}// end of Stop_Intakes()

void Auto::Intake::Shoot_Index() {
  Auto::Intake::updateArray();
  task::sleep(10);
  int x = Auto::Intake::get_Ball_Status(0);

  if(x==0) { // 2nd array pos is empty but first is full
    FlywheelMotor.spin(directionType::fwd, 100, velocityUnits::pct);
    task::sleep(450);
    
  }
  
  else if(x==1) { // 2nd and 1st array pos are full
    FlywheelMotor.spin(directionType::fwd, 100, velocityUnits::pct);
    task::sleep(400);
    FlywheelMotor.stop(brakeType::coast);
    while(TopTracker.value(percentUnits::pct)>65) {
      IntakeRight.spin(directionType::fwd, 10, velocityUnits::pct);
      IntakeLeft.spin(directionType::fwd, 10, velocityUnits::pct);
      FlywheelMotor.spin(directionType::fwd, 5, velocityUnits::pct);
      BottomRollers.spin(directionType::fwd, 80, velocityUnits::pct);
      EjectorMotor.spin(directionType::fwd, 80, velocityUnits::pct);
      task::sleep(10);
    }
  }// end of else if(x==1)
  Stop_Intakes();
  FlywheelMotor.stop(brakeType::coast);
  BottomRollers.stop(brakeType::brake);
  EjectorMotor.stop(brakeType::brake);
}// end of Shoot_Index()

void Auto::Intake::Shoot_Index_No_Intake() {
  Auto::Intake::updateArray();
  task::sleep(10);
  int x = Auto::Intake::get_Ball_Status(0);

  if(x==0) { // 2nd array pos is empty but first is full
    FlywheelMotor.spin(directionType::fwd, 100, velocityUnits::pct);
    task::sleep(450);
    
  }
  
  else if(x==1) { // 2nd and 1st array pos are full
    FlywheelMotor.spin(directionType::fwd, 100, velocityUnits::pct);
    task::sleep(400);
    FlywheelMotor.stop(brakeType::coast);
    while(TopTracker.value(percentUnits::pct)>65) {
      IntakeRight.spin(directionType::fwd, -50, velocityUnits::pct);
  IntakeLeft.spin(directionType::fwd, -50, velocityUnits::pct);
      FlywheelMotor.spin(directionType::fwd, 5, velocityUnits::pct);
      BottomRollers.spin(directionType::fwd, 70, velocityUnits::pct);
      EjectorMotor.spin(directionType::fwd, 70, velocityUnits::pct);
      task::sleep(10);
    }
  }// end of else if(x==1)
  IntakeRight.spin(directionType::fwd, -50, velocityUnits::pct);
  IntakeLeft.spin(directionType::fwd, -50, velocityUnits::pct);
  FlywheelMotor.stop(brakeType::coast);
  BottomRollers.stop(brakeType::brake);
  EjectorMotor.stop(brakeType::brake);
}// end of Shoot_Index()

void Auto::Intake::Goal_Cycle_Intake(int target_shot, int target_eject) {
  int Target_S = target_shot;
  int Target_E = target_eject;
  int counter =0;
  if(Target_S ==1) {
   // Auto::Intake::Shoot_Index();
    FlywheelMotor.spin(directionType::fwd, 100, velocityUnits::pct);
    while(counter<Target_E) {
    IntakeRight.spin(directionType::fwd, 80, velocityUnits::pct);
    IntakeLeft.spin(directionType::fwd, 80, velocityUnits::pct);
    BottomRollers.spin(directionType::fwd, 80, velocityUnits::pct);
    EjectorMotor.spin(directionType::fwd, 90, velocityUnits::pct);
    
    if(Color1.isNearObject())
    {
      counter++;
      
      while(Color1.isNearObject() && counter<Target_E)  // prev while statment: while(TopTracker.value(perecentUnits::pct)>67 && counter<Target_E)
      task::sleep(10);
      FlywheelMotor.stop(brakeType::brake);
      
    }
    task::sleep(10);
    }// end of while(counter<Target_E)
  }// end of if(Target_S==1)
  else if(Target_S ==2) {
    //Shoot_Index();
    FlywheelMotor.spin(directionType::fwd, 100, velocityUnits::pct);
    task::sleep(250);
    BottomRollers.spin(directionType::fwd, 90, velocityUnits::pct);
    EjectorMotor.spin(directionType::fwd,  90, velocityUnits::pct);
    while(TopTracker.value(percentUnits::pct)>60)
    task::sleep(10);
    while(counter<Target_E) {
    IntakeRight.spin(directionType::fwd, 100, velocityUnits::pct);
    IntakeLeft.spin(directionType::fwd, 100, velocityUnits::pct);
    
    
    if(Color1.isNearObject())
    {
      counter++;
     // while(TopTracker.value(percentUnits::pct)>65)
     // task::sleep(10); 
      
      while(Color1.isNearObject() && counter<Target_E) // prev while statment: while(TopTracker.value(percentUnits::pct)>67 && counter<Target_E)
      task::sleep(10);
      FlywheelMotor.stop(brakeType::brake);
      
    }
    
    }// end of while(counter<Target_E)
    Stop_Intakes();
    FlywheelMotor.stop(brakeType::brake);
    BottomRollers.stop(brakeType::brake);
    EjectorMotor.stop(brakeType::brake);
    FlywheelMotor.stop(brakeType::coast);
  }// end of else if(Target_S == 2)
    Stop_Intakes();
    BottomRollers.stop(brakeType::brake);
    EjectorMotor.stop(brakeType::brake);
    FlywheelMotor.stop(brakeType::brake);
    counter =0;
}// end of Goal_Cycle_Intake

void Auto::Intake::IntakeTo(int ballnum) {
  if(ballnum==1) {
    while(TopTracker.value(percentUnits::pct)>65) {
    Intake_On(50);
    FlywheelMotor.spin(directionType::fwd, 5, velocityUnits::pct);
    BottomRollers.spin(directionType::fwd, 40, velocityUnits::pct);
    EjectorMotor.spin(directionType::fwd, 20, velocityUnits::pct);
    task::sleep(10);
    }// end of while(TopTracker.value())
  }// end of if(ballnum==1)
  else if(ballnum ==2) {
    while(TopTracker.value(percentUnits::pct)>65) {
    FlywheelMotor.spin(directionType::fwd, 5, velocityUnits::pct);
    Intake_On(80);
    BottomRollers.spin(directionType::fwd, 80, velocityUnits::pct);
    EjectorMotor.spin(directionType::fwd, 20, velocityUnits::pct);
    task::sleep(10);
    }// end of while(TopTracker.value())
    FlywheelMotor.stop(brakeType::hold);
    EjectorMotor.stop(brakeType::hold);
    while(BottomTracker.value(percentUnits::pct)>65) {
    Intake_On(80);
    BottomRollers.spin(directionType::fwd, 80, velocityUnits::pct);
    //EjectorMotor.spin(directionType::fwd, 20, velocityUnits::pct);
    task::sleep(10);
    }
  }// end of else if(ballnum==2)
  //Stop_Intakes();
  Intake_On(80);
  BottomRollers.stop(brakeType::brake);
  EjectorMotor.stop(brakeType::brake);
  FlywheelMotor.stop(brakeType::brake);

    
}// end of IntakeTo

void Auto::Intake::EjectTo(int ballnum) {
  int counter =0;
  if(ballnum==1) {
    while(BottomTracker.value(percentUnits::pct)>65) {
    //FlywheelMotor.spin(directionType::rev, 10, velocityUnits::pct);
    task::sleep(100);
    Intake_On(-100);
    BottomRollers.spin(directionType::fwd, 70, velocityUnits::pct);
    EjectorMotor.spin(directionType::rev, 70, velocityUnits::pct);
    task::sleep(10);
    }// end of while(D1.isObjectDetected())
  }// end of if(ballnum==1)
  else if(ballnum ==2) {
    while(counter<ballnum) {
    //FlywheelMotor.spin(directionType::rev,10,velocityUnits::pct);
    Intake_On(-100);
    BottomRollers.spin(directionType::fwd, 70, velocityUnits::pct);
    EjectorMotor.spin(directionType::rev, 70, velocityUnits::pct);
    if(BottomTracker.value(percentUnits::pct)<65) {
    counter++;
    while(BottomTracker.value(percentUnits::pct)<65)
    task::sleep(10);
    }// end of if(D1.isObjectDetected())
   }// end of while(counter<ballnum)
    
  }// end of else if(ballnum==2)
  Stop_Intakes();
  BottomRollers.stop(brakeType::brake);
  EjectorMotor.stop(brakeType::brake);
  FlywheelMotor.stop(brakeType::brake);
}// end of EjectTo

void Auto::Intake::All_Roller_Stop() {
 FlywheelMotor.stop(brakeType::brake);
 EjectorMotor.stop(brakeType::brake);
 BottomRollers.stop(brakeType::brake);
}// end of All_Roller_Stop

void Auto::Intake::OutTake_Eject() {
  //FlywheelMotor.spin(directionType::rev, 30, velocityUnits::pct);
  EjectorMotor.spin(directionType::rev, 50, velocityUnits::pct);
  BottomRollers.spin(directionType::fwd, 50, velocityUnits::pct);
  Intake_On(-50);
}

void Auto::Intake::Flywheel_Eject() {
  FlywheelMotor.spin(directionType::rev, 30, velocityUnits::pct);
  EjectorMotor.spin(directionType::rev, 50, velocityUnits::pct);
  BottomRollers.spin(directionType::fwd, 50, velocityUnits::pct);
  Intake_On(-50);
  }

