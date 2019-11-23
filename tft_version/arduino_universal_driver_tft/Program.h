class Condition
{
  private:
  state condition_status;
  state p1;
  state p2;
  state wy1;
  state wy2;
  unsigned int timer;
  
  public:
  Condition() : condition_status(none), p1(none), p2(none), wy1(none), wy2(none), timer(0) {}
  ~Condition(){}
  bool timer_lock = false;
  unsigned long timer_actual;
  unsigned long turn_off_time_start;
  state get_condition_status(){return condition_status;}
  state get_p1(){return p1;}
  state get_p2(){return p2;}
  state get_wy1(){return wy1;}
  state get_wy2(){return wy2;}
  unsigned get_timeout(){return timer;}
  void set_condition_status(state x){condition_status = x;}
  void set_p1(state x){p1 = x;}
  void set_p2(state x){p2 = x;}
  void set_wy1(state x){wy1 = x;}
  void set_wy2(state x){wy2 = x;}
  void set_timeout(unsigned x){timer = x;}
  void reset_condition();
};

void Condition::reset_condition()
{
   set_condition_status(none);
   set_p1(none);
   set_p2(none);
   set_wy1(none);
   set_wy2(none);
   set_timeout(0);
}

class Program
{
  private:
  bool program_status;
  
  public:
  Program() : program_status(false){}
  ~Program(){};
  Condition condition_list[CONDITION_SIZE];
  void execute_program();
  bool stop_program(unsigned long working_time, bool force_stop = false);
  state analog_port_convert(int);
  void update_wy(state p1, state p2);
  bool get_program_status(){return program_status;}
  void set_program_status(bool set_status){program_status = set_status;}
};

void Program::execute_program()
{
  unsigned long working_time_start = millis();
  state port_value_p1 = none;
  state port_value_p2 = none;
  bool prepare_timers = true;
  
  while(program_status)
  {
    /*
     * Stop the program by clicking on STOP button.
     */
    if(stop_program(millis()-working_time_start)) break;
    
    if(prepare_timers)
    {
      for(int i = 0 ; i < CONDITION_SIZE ; i++)
      {
        condition_list[i].turn_off_time_start = millis();
      }
      prepare_timers = false;
    }
    
    for(int i = 0 ; i < CONDITION_SIZE ; i++)
    {
      if(active == condition_list[i].get_condition_status())
      {
        port_value_p1 = Program::analog_port_convert(analogRead(PORT1));
        port_value_p2 = Program::analog_port_convert(analogRead(PORT2));

        /*
         * Mode1. Drive the output only if port 1 is active.
         */
        if(none != condition_list[i].get_p1() && none == condition_list[i].get_p2())
        {
          //Serial.println("Port 1");
          if(port_value_p1 == condition_list[i].get_p1())
          {
            Program::update_wy(condition_list[i].get_wy1(), condition_list[i].get_wy2());
          }
          else 
          {
            condition_list[i].turn_off_time_start = millis();
          }
        }

        /*
         * Mode1. Drive the output only if port 2 is active.
         */
        if(none != condition_list[i].get_p2() && none == condition_list[i].get_p1())
        {
          //Serial.println("Port 2");
          if(port_value_p2 == condition_list[i].get_p2())
          {
            Program::update_wy(condition_list[i].get_wy1(), condition_list[i].get_wy2());
          }
          else 
          {
            condition_list[i].turn_off_time_start = millis();
          }
        }

        /*
         * Mode1. Drive the output only if port 1 and port 2 are active.
         */
        if(none != condition_list[i].get_p1() && none != condition_list[i].get_p2())
        {
          //Serial.println("Port 1 oraz Port 2");
          if(port_value_p1 == condition_list[i].get_p1() && port_value_p2 == condition_list[i].get_p2())
          {
            Program::update_wy(condition_list[i].get_wy1(), condition_list[i].get_wy2());
          }
          else 
          {
            condition_list[i].turn_off_time_start = millis();
          }
        }

        /*
         * Mode2. Drive the output based only on timer. Ports are disabled and not reading.
         */
        if(0 != condition_list[i].get_timeout() && none == condition_list[i].get_p1() && none == condition_list[i].get_p2())
        {
          //Serial.println("Czasowka");
          if(false == condition_list[i].timer_lock)
          {
            condition_list[i].timer_lock = true;
            condition_list[i].timer_actual = millis();
          }
          Program::update_wy(condition_list[i].get_wy1(), condition_list[i].get_wy2());
          while(true == condition_list[i].timer_lock && millis()/100 - condition_list[i].timer_actual/100 <= (condition_list[i].get_timeout()*10))
          {
            /*
             * Stop the program by clicking on STOP button.
             */
            if(stop_program(millis()- working_time_start)) break;
          }
          condition_list[i].timer_lock = false;
        }

        /*
         * Mode3. Run like Mode1 and additionaly set time guards for every instruction separatelly.
         */
        if(0 != condition_list[i].get_timeout() && (none != condition_list[i].get_p1() || none != condition_list[i].get_p2()))
        {
          //Serial.println("Czasowka i Port 1 oraz Port 2");
          if(millis()/100 - condition_list[i].turn_off_time_start/100 >= (condition_list[i].get_timeout()*10))
          {
            set_program_status(false);
            /*
             * Stop the program by force parameter (timeout).
             */
            stop_program(millis()- working_time_start, true);
            break;
          }
        }
      }
    }
  }
}

state Program::analog_port_convert(int value)
{
//|   C     B     voltage    digital |
//|----------------------------------|
//|   0     -     1v         200     |
//|   1     -     0v         0       |
//|   -     0     2v         400     |
//|   -     1     0v         0       |
//|   0     0     2.67v      550     |
//|   1     0     1.77v      360     |
//|   0     1     0.45v      90      |
//|   1     1     0v         0       |
//|----------------------------------|

  //Serial.println(value);
  if(value <= 70)
  {
    return three; 
  } 
  else if(value > 70 && value <= 140)
  {
    return one;
  } 
  else if ((value > 140 && value <= 180) ||
           (value > 220 && value <= 340))
  {
    return two;
  } 
  else if ((value > 340 && value <= 380) ||
           (value > 420 && value <= 600))
  {
    return zero;
  }
  else if (value > 180 && value <= 220)
  {
    return one;
  }
  else if (value > 380 && value <= 420)
  {
    return two;
  }
  else if(value > 600) 
  {
   return error; 
  }
}

void Program::update_wy(state wy1, state wy2)
{
  if(none != wy1)
  {
     if(off == wy1)
     {
      digitalWrite(OUT1, HIGH);
     }
     else if(on == wy1 ) 
     {
      digitalWrite(OUT1, LOW);
     }
     else 
     {
      //error
     }
  }
  if(none != wy2)
  {
     if(off == wy2)
     {
      digitalWrite(OUT2, HIGH);
     } 
     else if(on == wy2 ) 
     {
      digitalWrite(OUT2, LOW);
     } 
     else 
     {
      //error
     }
  }
}
