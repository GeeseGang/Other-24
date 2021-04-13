#include "vex.h"
#include "Autonomous.h"
#include "Auto_Movement.h"
#include "Auto_Turn.h"
#include "Auto_Intake_Functions.h"

void Auto::Test () 

{
  
  /*Gyro.startCalibration();
  while(Gyro.isCalibrating())
  task::sleep(10);
  */
  
  Auto::Movement::Auto_Move(2.1,100);
  while(Auto::Movement::Enabled)
  {
    Auto::Intake::IntakeTo(2);
  }
  task::sleep(100);

  Auto::Movement::Auto_Move(-1.1,60);
  while(Auto::Movement::Enabled)
  {
    Auto::Intake::OutTake_Eject();
  }
  task::sleep(10);
  if(BottomTracker.value(percentUnits::pct) < 67){
    BottomRollers.spin(directionType::fwd, 100, percentUnits::pct);
    EjectorMotor.spin(directionType::fwd, 100, percentUnits::pct);
    task::sleep(350);
    EjectorMotor.spin(directionType::fwd, -100, percentUnits::pct);
    task::sleep(200);
    BottomRollers.stop(brakeType::hold);
    EjectorMotor.stop(brakeType::hold);
  }
  Auto::Turn::TurnSpecific(135, 40);
  while(Auto::Turn::Enabled)
    task::sleep(10);

  // Start of section for 1 ball in robot, 1 ball in front of goal, 2 balls in goal

   Auto::Movement::Auto_Move(1.2,80); //normally 1.25
  while(Auto::Movement::Enabled)
 {
    Auto::Intake::IntakeTo(2);
    Auto::Intake::Intake_On(20);
  }

  Auto::Intake::Shoot_Index();
  Auto::Intake::Shoot_Index();
  Auto::Intake::Shoot_Index();

    // end of section for 1 ball in robot, 1 ball in front of goal, 2 balls in goal

  Auto::Movement::Auto_Move(-1.25,60);
  while(Auto::Movement::Enabled)
  {
    Auto::Intake::Intake_On(20);
  }
  task::sleep(10);
  Auto::Intake::Intake_On(-20);

  Auto::Turn::TurnSpecific(135, 40);
  while(Auto::Turn::Enabled)
    task::sleep(10);

Auto::Movement::Auto_Move(1.5,50);
while(Auto::Movement::Enabled)
    task::sleep(10);

Auto::Turn::TurnSpecific(-90, 40);
while(Auto::Turn::Enabled)
    task::sleep(10);

 //start of 0 balls in robot, 0 balls in front of goal, 2 ball in goal

Auto::Movement::Auto_Move(0.9,60);
while(Auto::Movement::Enabled)
{
  Auto::Intake::IntakeTo(2); 
}

Auto::Intake::Shoot_Index_No_Intake();

//end of 0 balls in robot, 0 balls in front of goal, 2 ball in goal

Auto::Movement::Auto_Move(-1,50);
while(Auto::Movement::Enabled)
{
  Auto::Intake::Flywheel_Eject();
}
task::sleep(10);

Gyro.startCalibration();
  while(Gyro.isCalibrating())
  task::sleep(10);

Auto::Turn::TurnSpecific(270, 40);
 while(Auto::Turn::Enabled)
 task::sleep(10);

Auto::Movement::Auto_Move(1.25,60);
while(Auto::Movement::Enabled)
task::sleep(10);

Auto::Turn::TurnSpecific(-45, 50);
 while(Auto::Turn::Enabled)
 task::sleep(10);

// Start of 1 ball in front, 0 balls in bot, 2 balls in goal

Auto::Movement::Auto_Move(1.45,60); //og is 1.25
  while(Auto::Movement::Enabled)
  {
  Auto::Intake::IntakeTo(2);
  }
  
  Auto::Intake::Shoot_Index_No_Intake();
  Auto::Intake::Shoot_Index_No_Intake();
  task::sleep(10);

  // Start of 1 ball in front, 0 balls in bot, 2 balls in goal

Auto::Movement::Auto_Move(-1.25,60);
  while(Auto::Movement::Enabled)
  task::sleep(10);

  Auto::Intake::Intake_On(-20);


/*Gyro.startCalibration();
  while(Gyro.isCalibrating())
  task::sleep(10);

Auto::Turn::TurnSpecific(90, 50);
while(Auto::Turn::Enabled)
 task::sleep(10);


Auto::Movement::Auto_Move(1.25,60);
while(Auto::Movement::Enabled)
    task::sleep(10);*/

}

void Auto::Tune()

{

  /*Gyro.startCalibration();
  while(Gyro.isCalibrating())
  task::sleep(10);

Auto::Movement::Auto_Move(1,60);
  while(Auto::Movement::Enabled)
  task::sleep(100);

  Auto::Turn::TurnSpecific(-90, 40);
while(Auto::Turn::Enabled)
    task::sleep(10);

    Auto::Movement::Auto_Move(1,60);
  while(Auto::Movement::Enabled)
  task::sleep(100);

  Auto::Turn::TurnSpecific(-90, 40);
while(Auto::Turn::Enabled)
    task::sleep(10);

Auto::Movement::Auto_Move(0.8,60);
while(Auto::Movement::Enabled)
{
  Auto::Intake::IntakeTo(2); 
}

Auto::Intake::Shoot_Index_No_Intake();
Auto::Intake::Shoot_Index_No_Intake();

//end of 1 ball in robot, 0 balls in front of goal, 2 ball in goal

Auto::Movement::Auto_Move(-0.5,50);
while(Auto::Movement::Enabled)
{
  Auto::Intake::Flywheel_Eject();
}
task::sleep(10);

Auto::Turn::TurnSpecific(-90, 40);
while(Auto::Turn::Enabled)
    task::sleep(10);

    Auto::Movement::Auto_Move(1,60);
  while(Auto::Movement::Enabled)
  task::sleep(100);

  Auto::Turn::TurnSpecific(45, 40);
while(Auto::Turn::Enabled)
    task::sleep(10);

    Auto::Movement::Auto_Move(0.8,60);
while(Auto::Movement::Enabled)
{
  Auto::Intake::IntakeTo(2); 
}

Auto::Intake::Shoot_Index_No_Intake();

//end of 0 balls in robot, 0 balls in front of goal, 2 ball in goal

Auto::Movement::Auto_Move(-0.5,50);
while(Auto::Movement::Enabled)
{
  Auto::Intake::Flywheel_Eject();
}
task::sleep(10);


 Auto::Turn::TurnSpecific(-135, 40);
while(Auto::Turn::Enabled)
    task::sleep(10);

    Auto::Movement::Auto_Move(0.8,60);
while(Auto::Movement::Enabled)
{
  Auto::Intake::IntakeTo(1); 
}

Auto::Movement::Auto_Move(-0.5,50);
while(Auto::Movement::Enabled)
task::sleep(10);

Auto::Turn::TurnSpecific(45, 40);
while(Auto::Turn::Enabled)
    task::sleep(10);

    Auto::Movement::Auto_Move(0.5,50);
while(Auto::Movement::Enabled)
task::sleep(10);*/


}

//while(true){
  //Brain.Screen.printAt(10,50, "Gyro Val %2f", Gyro.rotation());
  //task::sleep(20);
  //}
  //Auto::Turn::TurnSpecific(-90, 85);
  //while(Auto::Movement::Enabled){
  //  task::sleep(20);
  //}