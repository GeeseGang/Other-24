#include "vex.h"
#include "UC_Drive.h"
#include "Auto_Intake_Functions.h"
/*
  The commented out parts are to test out different responsivities on the drive, between quadratic, logarithmic, and linear.
  Personal preference
*/
void User_Control::Drive::Control(void) {
  double FWD_Power;
  double TURN_Power;
  double averageTemp;
  double slugCorrection;
  while(true) {
    
    averageTemp = (FrontLeft.temperature(temperatureUnits::fahrenheit) + FrontRight.temperature(temperatureUnits::fahrenheit) + RearRight.temperature(temperatureUnits::fahrenheit) + RearLeft.temperature(temperatureUnits::fahrenheit) + TopRight.temperature(temperatureUnits::fahrenheit) + FrontLeft.temperature(temperatureUnits::fahrenheit))/6;
    if(averageTemp > 100){
      slugCorrection = fabs(1 + (0.053 * (averageTemp - 121)));
    }
    else{
      slugCorrection = 1;
    }
    if(!(slugCorrection > 0.95 && slugCorrection < 2.5)){
      slugCorrection = 1;
    }
    FWD_Power  = 0.0001* Controller.Axis3.position(vex::percentUnits::pct)* Controller.Axis3.position(vex::percentUnits::pct) * Controller.Axis3.position(vex::percentUnits::pct);
    TURN_Power = 0.005*slugCorrection* Controller.Axis1.position(vex::percentUnits::pct) * abs(Controller.Axis1.position(vex::percentUnits::pct)); 
    if(!(Controller.ButtonB.pressing())){
      FrontRight.spin(directionType::fwd, FWD_Power - TURN_Power, percentUnits::pct);
      FrontLeft .spin(directionType::fwd, FWD_Power + TURN_Power, percentUnits::pct);
      RearRight .spin(directionType::fwd, FWD_Power - TURN_Power, percentUnits::pct);
      RearLeft  .spin(directionType::fwd, FWD_Power + TURN_Power, percentUnits::pct);
      TopRight  .spin(directionType::fwd, FWD_Power - TURN_Power, percentUnits::pct);
      TopLeft   .spin(directionType::fwd, FWD_Power + TURN_Power, percentUnits::pct);
    }//if(!Controller.ButtonR2.pressing()){

    else{
      while(Controller.ButtonB.pressing()){
        FrontRight   .stop(brakeType::hold);
        FrontLeft    .stop(brakeType::hold);
        RearRight    .stop(brakeType::hold);
        RearLeft     .stop(brakeType::hold);
        TopLeft     .stop(brakeType::hold);
        TopLeft      .stop(brakeType::hold);
        task::sleep(25);
      }
      FrontRight   .stop(brakeType::coast);
      FrontLeft    .stop(brakeType::coast);
      RearRight    .stop(brakeType::coast);
      RearLeft     .stop(brakeType::coast);
      TopLeft      .stop(brakeType::coast);
      TopLeft      .stop(brakeType::coast);
    }//else{
    
    //double whatBroke[] = {FwdL->current(percentUnits::pct), TopR->current(percentUnits::pct),
      //                    RearL->current(percentUnits::pct),   RearR->current(percentUnits::pct),
        //                  TopLeft.current(percentUnits::pct),   FwdR->current(percentUnits::pct)};
      
    task::sleep(10);//Don't hog the CPU
  } // while(true) {
} // void User_Control::Drive::Control(void) {
