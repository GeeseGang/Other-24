namespace Auto {
  namespace Intake {
    /// star indicates methods that will move on to next line of code when used
    /// IntakeTo should be run after calling Auto_Movement Function since calling it first will wait for balls to be indexed before moving on to next line.
    /// ex IntakeTo(2);
    ///    Auto_Move(1,80);
    ///    while(Auto::Movement::Enabled)
    ///    task::sleep(10);


    void Intake_On(int pow);// turn on ONLY intakes at given power *
    void Stop_Intakes();// stops intakes
    void Shoot_Index();// shoots a ball and depending on how many are inside, idexes accordingly
    void Goal_Cycle_Intake(int target_shot, int target_eject);// shoot desired balls and intake desired number of enemy blue balls
    void IntakeTo(int ballnum);// turn on intakes until number balls are picked up and properly indexed 
    void OutTake_Eject(); // ejection of balls via outTake *
    void EjectTo(int ballnum); // remove enemy balls via ejection until distance sensor picks up given number of balls
    void All_Roller_Stop(); //brakes all roller motors
    void Shoot_Index_No_Intake(); //shooting without intakes
    void Flywheel_Eject(); //outtakes with flywheel
    extern int ballArray[2];
    void Indexer(void);
    void goalTopper(void);
    int getOpenSlot();
    int getFilledSlot();
    void updateArray();
    extern bool Eject;
    void Sorting();
    int get_Ball_Status(int pos);
    // variables
    extern int blue_Counter;
    extern int red_Counter;
    extern int eject_Counter;
    
  }
}