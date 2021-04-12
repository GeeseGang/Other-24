#include "UC_BallTracking.h"
#include "Auto_Intake_Functions.h"

#if !defined(THREADS_HEADER)
#define THREADS_HEADER

namespace User_Control {
  void Setup_Threads(void);
} // namespace User_Control {

namespace Auto {
  void Setup_Threads(void);
} // namespace Auto {

#endif