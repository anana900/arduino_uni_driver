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
  Condition() : condition_status(none), p1(none), p2(none), wy1(none), wy2(none), timer(0){}
  ~Condition(){}
  bool timer_lock = false;
  unsigned long timer_actual;
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
  bool stop_program(unsigned long working_time);
  state analog_port_convert(int);
  void update_wy(state p1, state p2);
  bool get_program_status(){return program_status;}
  void set_program_status(bool set_status){program_status = set_status;}
};

void Program::execute_program()
{
  unsigned long working_time_start = millis(); 
  while(program_status)
  {
    if(stop_program(millis()-working_time_start)) break;
    state port_value = none;
    for(int i = 0 ; i < CONDITION_SIZE ; i++)
    {
      if(active == condition_list[i].get_condition_status())
      {
        
        if(none != condition_list[i].get_p1())
        {
          port_value = Program::analog_port_convert(analogRead(PORT1));
          if(port_value == condition_list[i].get_p1())
          {
            Program::update_wy(condition_list[i].get_wy1(), condition_list[i].get_wy2());
          }
        }
        if(none != condition_list[i].get_p2())
        {
          port_value = Program::analog_port_convert(analogRead(PORT2));
          if(port_value == condition_list[i].get_p2())
          {
            Program::update_wy(condition_list[i].get_wy1(), condition_list[i].get_wy2());
          }
        }
        if(0 != condition_list[i].get_timeout() && none == condition_list[i].get_p1() && none == condition_list[i].get_p2())
        {
          if(false == condition_list[i].timer_lock){
            condition_list[i].timer_lock = true;
            condition_list[i].timer_actual = millis();
          }
          Program::update_wy(condition_list[i].get_wy1(), condition_list[i].get_wy2());
          while(true == condition_list[i].timer_lock && millis()/100 - condition_list[i].timer_actual/100 <= (condition_list[i].get_timeout()*10)){
            if(stop_program(millis()- working_time_start)) break;
          }
          condition_list[i].timer_lock = false;
        }
      }
    }
  }
}

state Program::analog_port_convert(int value)
{
  if(value < 50)
  {
    return zero;
  } 
  else if(value > 300 && value < 400)
  {
    return one;
  } 
  else if (value > 500 && value < 600)
  {
    return two;
  } 
  else if (value > 700 && value < 800)
  {
    return three;
  } 
  else if(value > 1020) 
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
