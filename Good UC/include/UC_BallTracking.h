#if !defined(UC_BALLTRACKING_HEADER)
#define UC_BALLTRACKING_HEADER

namespace User_Control {
  namespace BallTracking {
    void Control(void);
    extern bool sendingUpE;
    extern bool sendingUpF;
    extern bool ejecting;
    extern int allianceColor; //1 is red, -1 is blue
    extern int ballArray[2];
  } // namespace Drive {
} // namespace User_Control {

#endif