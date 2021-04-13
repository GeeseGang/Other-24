#include "Auto_Movement.h"
#include <cmath>

namespace Auto{
namespace Movement {

double Target =0;
double Power =0;
bool Enabled =false;
double max_power =0;
                        //NOTE TO NOT WASTE HOURS:  !!!!KP MAKES A BIG DEAL ON KD, DO NOT TUNE KP WITHOUT TUNING M_CONSTANT AS WELL!!!!
double M_Constant=0.01;    //tuned on both 25 & 99 for 1 tile: 0.265, ... 0.375...0.052
double Kp=230;              //tuned on both 25 & 99 for 1 tile: 153

//from velocity: 0.038
//150

double Kd=2*sqrt(M_Constant*Kp);

double R_Correction = 0;
double L_Correction = 0;
 }
}

void Auto::Movement::Auto_Move(double InputT, double InputP)
{
  Target=InputT;
  Power=InputP;
  Enabled=true;
}

void Auto::Movement::Auto_Control(void)
{
  double abs_Target = fabs(Target);
  double Error=0;
  double init_Error = 0;
  double Error_Sign=0;
  unsigned int Counter =0;
  signed short  Holding=0;

  while(true) {
  
  if(Enabled){

    Left.resetRotation();
    Right.resetRotation();
    
    Error=0;
    
    Error_Sign=0;
    Counter=0;
    Holding =0;
    

    while(Enabled){
     
     double Lval=Left.rotation(rotationUnits::deg);
     double Rval=Right.rotation(rotationUnits::deg);
     double current_Pos = Tiles_per_tic*0.5*(Lval+Rval);
    init_Error = Target;
    Error = Target - current_Pos;
    if(Error!=0)
    Error_Sign = Error/(fabs(Error));
    else
    Error_Sign=0;

    double Velocity = Tiles_per_tic*(-0.5)*(Left.velocity(velocityUnits::dps)+ Right.velocity(velocityUnits::dps));
    Brain.Screen.printAt(1, 3*20, "Error : %5lf", Error);
    Brain.Screen.printAt(1,5*20, "Left : %5lf", Left.rotation(rotationUnits::deg));
    Brain.Screen.printAt(2,7*20, "Right : %5lf", Right.rotation(rotationUnits::deg));
    Brain.Screen.printAt(2, 9*20, "Velocity: %5lf", Velocity);
    Brain.Screen.printAt(2, 11*20, "init: %5lf", init_Error);
    if((fabs(Error)<fabs(abs_Target-0.01)) || ((fabs(Velocity) < 0.065) && (fabs(Error) + 0.2 < fabs(init_Error)))){
     if(fabs(Velocity)<3 || Holding==1)
      Counter++;
     else 
     Counter =0;
     
     if(Counter>10)
     break;
    }
    

     double R_Motor_Power = Kp*Error+Kd*Velocity;
     double L_Motor_Power = R_Motor_Power;

     if(fabs(R_Motor_Power)>Power)
     {
     R_Motor_Power = Power*Error_Sign;
     L_Motor_Power = R_Motor_Power;
     }

     if(R_Motor_Power> max_power)
     {
       max_power=R_Motor_Power;
     }

        double abs_kP_Error = fabs(Kp*Error);
        double Proportional_R_Correction = (abs_kP_Error > Power) ? R_Correction : (abs_kP_Error/(100.))*R_Correction;         // Units : %
        double Proportional_L_Correction = (abs_kP_Error > Power) ? L_Correction : (abs_kP_Error/(100.))*L_Correction; 
        R_Motor_Power+=Proportional_R_Correction;
        L_Motor_Power+=Proportional_L_Correction;
        
        if(fabs(Error)<0.1)
         Holding =0;

        if(Holding==1)
        {
          Brain.Screen.clearScreen();
          Brain.Screen.printAt(2,7*20, "aaaaaa", Right.rotation(rotationUnits::deg));
          FrontLeft.stop(brakeType::hold);
          FrontRight.stop(brakeType::hold);
          RearLeft.stop(brakeType::hold);
          RearRight.stop(brakeType::hold);
          TopRight.stop(brakeType::hold);
          TopLeft.stop(brakeType::hold);
        }
        else{
          R_Motor_Power = R_Motor_Power * 0.12;//made a change here 3-21-2021
          L_Motor_Power = L_Motor_Power * 0.12;
          //If this doesn't work, maybe negative voltage doesn't work the same way that negative velocity does
          //In which case we just do an if/else with motor power > 0, one has directionType::rev instead
          FrontRight.spin(directionType::fwd,R_Motor_Power, voltageUnits::volt);
          RearRight.spin(directionType::fwd,R_Motor_Power,  voltageUnits::volt);
          FrontLeft.spin(directionType::fwd,L_Motor_Power,  voltageUnits::volt);
          RearLeft.spin(directionType::fwd,L_Motor_Power,   voltageUnits::volt);
          TopRight.spin(directionType::fwd,R_Motor_Power,   voltageUnits::volt);
          TopLeft.spin(directionType::fwd,L_Motor_Power,    voltageUnits::volt);
        }
       task::sleep(15);
    }//end of while(Enabled)
    FrontLeft.stop(brakeType::brake);
    FrontRight.stop(brakeType::brake);
    RearLeft.stop(brakeType::brake);
    RearRight.stop(brakeType::brake);
    TopRight.stop(brakeType::brake);
    TopLeft.stop(brakeType::brake);
    Brain.Screen.printAt(100, 150, "Max Power: %2f", max_power);
    Power=0;
    Target=0;
    Enabled =false;


    }//if(Enabled)
    //after break occurs, stop the motors and set Enabled to false so that it exists loop and waits for next Auto_Move() call in program
    
    task::sleep(15);
  }//end of while
  
 
  }// end of method
