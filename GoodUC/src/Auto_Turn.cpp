#include "vex.h"
#include "Auto_Turn.h"

using namespace std; 

namespace Auto {
  namespace Turn {
    double Target =0;
    double Power =0;
    bool Enabled = false;
    double Correction=0;
    double Global_Expected_Heading=0;
    double Robot_Turn_Constant = 0.05;//og 0.05
    double kP =0.7;//og 0.65
    double kD = sqrt(4*kP*Robot_Turn_Constant);
  }
}

void Auto::Turn::TurnSpecific(double ITarget, double IPower) {
     
     Target = ITarget+Correction;
     Power = IPower;
     Enabled= true;
     Brain.Screen.printAt(10,20, "I got here!");
}

void Auto::Turn::Auto_Turn_Control() {
   
   double Error, prevError;
   double Error_Sign;
   int Counter;
   int holding=0;
  
   

   while(true) {
     
    Brain.Screen.printAt(100,150, "Global Heading: %2f", Gyro.orientation(orientationType::yaw, rotationUnits::deg));
    Brain.Screen.printAt(100, 170, "Expected Heading: %2f", Global_Expected_Heading);
    Brain.Screen.printAt(100, 190, "Correction Angle: %2f", Correction);
     if(Enabled) {
     
     Gyro.resetRotation();
     Error=0;
     prevError=Target;
     Error_Sign=0;
     Counter=0;
     holding =0;

     double abs_Target = fabs(Target);

     while(Enabled) {
       double Angle = Gyro.rotation();
       Error = Target- Angle;
       if(Error !=0)
       Error_Sign = (Target)/(fabs(Target));
       
       Brain.Screen.printAt(10,50, "Gyro Val %2f", Angle);
       
       double Velocity = (10)*(Error-prevError);

       if(fabs(Error)<(abs_Target -10)) {
        if(holding==1)
        Counter++;
        else 
        Counter =0;
        if(Counter > 10)
        break;
       } //end of if(fabs(Error))
       
       double R_Power = fabs(kP*Error+kD*Velocity);
       double L_Power = R_Power;
       
       if(Error<1 && Error >-1)
       holding =1;

       if(holding == 1) {
         FrontLeft.stop(brakeType::hold);
         FrontRight.stop(brakeType::hold);
         RearLeft.stop(brakeType::hold);
         RearRight.stop(brakeType::hold);
       }
        if(Error_Sign>0) {
       
       FrontRight.spin(directionType::rev,R_Power, velocityUnits::pct);
       RearRight.spin(directionType::rev,R_Power, velocityUnits::pct);
       FrontLeft.spin(directionType::fwd,L_Power, velocityUnits::pct);
       RearLeft.spin(directionType::fwd,L_Power, velocityUnits::pct);
       }
       else if (Error_Sign<0) {
       FrontRight.spin(directionType::fwd,R_Power, velocityUnits::pct);
       RearRight.spin(directionType::fwd,R_Power, velocityUnits::pct);
       FrontLeft.spin(directionType::rev,L_Power, velocityUnits::pct);
       RearLeft.spin(directionType::rev,L_Power, velocityUnits::pct);
       }

      vex::task::sleep(10);
      prevError= Error;

     }//end of while(Enabled)
     FrontLeft.stop(brakeType::brake);
     FrontRight.stop(brakeType::brake);
     RearLeft.stop(brakeType::brake);
     RearRight.stop(brakeType::brake);
     Global_Expected_Heading+=Target-Correction;
     //

     /// Global Heading Correction
     if(Global_Expected_Heading>180) {
       Global_Expected_Heading= Global_Expected_Heading-360;
     }
     else if(Global_Expected_Heading<-180) {
       Global_Expected_Heading= Global_Expected_Heading+360;
     }
     Power =0;
     Target =0;
     Enabled = false;

     }// end of if(Enabled)
      
      Correction = Global_Expected_Heading-Gyro.orientation(orientationType::yaw, rotationUnits::deg);
     vex::task::sleep(20);

   }//end of while(true)

}// end of Auto::Turn::Auto_Turn_Control()