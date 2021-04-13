#include "vex.h"
namespace Auto {

  namespace Movement {
    
    const double Tiles_per_tic = 0.001;
    /*
      OK SO YOU DONT FORGET:
      MAKING IT BIGGER MAKES IT GO LESS FAR
      MAKING IT SMALLER MAKES IT GO FURTHER
      AAAAAAAAAAA
    */
    void Auto_Move( double In_Target, double In_Power);
    extern double Target;
    extern double Power;
    extern bool Enabled;
    extern double init_Error;
    void Auto_Control();
    extern double Error;
    extern double kp;
    extern double kd;

  }// end of Movement
}//end of Auto