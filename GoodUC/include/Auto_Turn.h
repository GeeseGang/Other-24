#include <cmath> 

namespace Auto {
  namespace Turn {

    void TurnSpecific(double ITarget, double IPower);

    void Auto_Turn_Control(void);

    extern double Target;
    extern double Power;
    extern bool Enabled;

    extern double Robot_Turn_Constant;
    extern double kP;
    extern double kD;


  }
}
