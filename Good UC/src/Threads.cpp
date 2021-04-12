#include "vex.h"
#include "Threads.h"
#include "Auto_Movement.h"
#include "Auto_Turn.h"
#include "UC_Drive.h"
#include "UC_Intake.h"
#include "UC_Flywheel.h"
#include "UC_BallTracking.h"
#include "UC_Rollers.h"
#include "UC_Ejector.h"
#include "Autonomous.h"

void User_Control::Setup_Threads(void) {

  thread UC_Drive        = thread( Drive::Control );
  thread UC_BallTracking = thread(BallTracking::Control);
  thread UC_Flywheel     = thread(Flywheel::Control);
  thread UC_Intake       = thread(Intake::Control);
  thread UC_Rollers      = thread(Rollers::Control);
  thread UC_Ejector      = thread(Ejector::Control);
  
  while (Competition.isEnabled() == true && Competition.isDriverControl() == true)
    task::sleep(20);

  UC_Drive       .interrupt();
  UC_BallTracking.interrupt();
  UC_Flywheel    .interrupt();
  UC_Intake      .interrupt();
  UC_Rollers     .interrupt();
  UC_Ejector     .interrupt();

}//void User_Control::Setup_Threads(void) {

void Auto::Setup_Threads(void){

  vex::thread A_Movement = vex::thread(Auto::Movement::Auto_Control);
  vex::thread A_Turn = vex::thread(Auto::Turn::Auto_Turn_Control);

  while(Competition.isEnabled()==true && Competition.isAutonomous() == true)
  vex::task::sleep(20);

  A_Movement.interrupt();
  A_Turn.interrupt();

  RearRight  .stop(brakeType::coast);
  RearLeft  .stop(brakeType::coast);
  FrontLeft  .stop(brakeType::coast);
  FrontRight  .stop(brakeType::coast);
  TopLeft .stop(brakeType::coast);
  TopRight.stop(brakeType::coast);

}//void Auto::Setup_Threads(void){