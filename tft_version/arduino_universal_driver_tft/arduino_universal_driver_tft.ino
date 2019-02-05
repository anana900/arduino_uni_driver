#include <SPI.h>
#include "constant.h"
#include "Program.h"
Program* program_list = new Program[PROGRAMS_NUMBER];
#include "tft.h"
#include "eeprom.h"

void printButton(int x, int y, int width, int height, uint16_t buttonColor, String text = "", int tx = 0, int ty = 0, int textSize = 1, uint16_t textColor = TEXT_COLOR_W, boolean customf = false);

TS_Point getPoint24();
/*
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
  bool timer_lock = false;
  unsigned long timer_actual;
  Condition() : condition_status(none), p1(none), p2(none), wy1(none), wy2(none), timer(0){}
  ~Condition(){}
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
  static int program_counter;
  //char program_name[PROGRAM_NAME_LENGTH];
  bool program_status;
  public:
  Program()
  {
    program_status = false;
    program_name.concat(program_counter);
    program_counter++;
  }
  String program_name = "PROGRAM ";
  Condition condition_list[CONDITION_SIZE];
  void execute_program();
  bool stop_program(unsigned long working_time);
  state analog_port_convert(int);
  void update_wy(state p1, state p2);
  bool get_program_status(){return program_status;}
  void set_program_status(bool set_status){program_status = set_status;}
};

int Program::program_counter = 1;
*/
bool Program::stop_program(unsigned long working_time)
{
  if(ts.touched()){
    TS_Point action = getPoint24();
    if (action.y > 85 && action.x > 2*(tft.width()/3))
    {
    Program::update_wy(off, off);
    printButton(200, 26, (tft.width()/3)+15, 30, BACKGROUND_COLOR_B, "----------", 200, 46, 1, TEXT_COLOR_W, true);
    printButton(200, 52, (tft.width()/3)+15, 30, BACKGROUND_COLOR_B, "----------", 200, 72, 1, TEXT_COLOR_W, true);
    return true;
    }
  } else {
    printButton(200, 26, (tft.width()/3)+15, 30, BACKGROUND_COLOR_B, "W1: "+String(digitalRead(OUT1))+" W2: "+String(digitalRead(OUT2)), 200, 46, 1, TEXT_COLOR_W, true);
    printButton(200, 52, (tft.width()/3)+15, 30, BACKGROUND_COLOR_B, String(working_time/1000)+" s", 200, 72, 1, TEXT_COLOR_W, true);
  }
  return false;
}
/*
void Program::execute_program()
{
 // unsigned long timer_sum = 0;
  unsigned long working_time_start = millis();
//  unsigned long common_timer = millis();
  // unsigned long wait_time = 0;
  // initiate here counters  
  while(program_status)
  {
    if(stop_program(millis()-working_time_start)) break;
   // common_timer = millis();
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
          while(true == condition_list[i].timer_lock && millis() - condition_list[i].timer_actual <= (condition_list[i].get_timeout()*1000)){
            if(stop_program(millis()-working_time_start)) break;
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
      digitalWrite(OUT1, LOW);
     }
     else if(on == wy1 ) 
     {
      digitalWrite(OUT1, HIGH);
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
      digitalWrite(OUT2, LOW);
     } 
     else if(on == wy2 ) 
     {
      digitalWrite(OUT2, HIGH);
     } 
     else 
     {
      //error
     }
  }
}
*/
void save_to_eeprom(){}
void read_from_eeprom(){}

//Program* program_list = new Program[PROGRAMS_NUMBER];

/*
TS_Point getPoint24()
{
  TS_Point tmpP, p = ts.getPoint();
  //p.x = map(p.x, 0, 3800, 0, tft.height());
  //p.y = map(p.y, 0, 4000,  tft.width(), 0);
  p.y = map(p.y, 220, 3880, tft.height(), 0);
  p.x = map(p.x, 200, 3650, tft.width(), 0);
  //tmpP.x=p.x;
  //p.x = p.y;
  //p.y = tmpP.x;
  Serial.print(p.x);
  Serial.print(" ");
  Serial.println(p.y);
  return p;
}

void prepareText(unsigned x, unsigned y, int textSize = 1, uint16_t textColor = TEXT_COLOR_W, boolean customf = false)
{
  tft.setCursor(x, y);
  tft.setTextSize(textSize);
  tft.setTextColor(textColor);
  if(customf) 
  {
    tft.setFont(&CUSTOM_FONT);
  } 
  else 
  {
    tft.setFont();
  }
}

void printButton(int x, int y, int width, int height, uint16_t buttonColor, String text = "", int tx = 0, int ty = 0, int textSize = 1, uint16_t textColor = TEXT_COLOR_W, boolean customf = false)
{
   tft.drawRect(x, y, width, height, buttonColor);
   tft.fillRect(x, y, width, height, buttonColor);
   prepareText(tx, ty, textSize, textColor, customf);
   tft.print(text);
}

void soundClic(int timer = 10)
{
  if(global_sound_set == 1)
  {
    digitalWrite(SOUND, 1);
    delay(timer);
    digitalWrite(SOUND, 0);
  }
}
*/



/*
void menu_program_01_print_buttons(Program &program){
  printButton(0, 0, 30, 30, TEXT_COLOR_W, "W", 7, 15, 1, BACKGROUND_COLOR_B, true);
  printButton(30, 0, 30, 30, 0x07FF, "S", 37, 21, 1, BACKGROUND_COLOR_B, true);
  printButton(60, 0, 60, 30, 0xF000, "TStop", 65, 21, 1, TEXT_COLOR_W, true);
  printButton(120, 0, 55, 30, 0xEEE0, "P1", 127, 21, 1, BACKGROUND_COLOR_B, true);
  printButton(175, 0, 55, 30, 0xEEE0, "P2", 182, 21, 1, BACKGROUND_COLOR_B, true);
  printButton(230, 0, 45, 30, 0x0B62, "W1", 237, 21, 1, TEXT_COLOR_W, true);
  printButton(275, 0, 45, 30, 0x0B62, "W2", 280, 21, 1, TEXT_COLOR_W, true);
  printButton(0, 200, tft.width(), 40, BACKGROUND_COLOR_B, "KASUJ", 10, 230, 1, 0xF000, true);
  printButton(tft.width()/3, 200, tft.width()/3, 40, BACKGROUND_COLOR_B, "ANULUJ", 120, 230, 1, TEXT_COLOR_W, true);
  printButton(2*tft.width()/3, 200, tft.width()/3, 40, BACKGROUND_COLOR_B, "ZAPISZ", 240, 230, 1, TEXT_COLOR_W, true);
}

void menu_program_01_print_conditions(Program &program){
  for(int i = 0 ; i < CONDITION_SIZE/2 ; i++)  // To see more conditions ('warunkow' W) slider implementation is necessary.
  {
    int y_button = 40*(i+1);
    int y_text = y_button+18;
    printButton(0, y_button, 30, 30, BACKGROUND_COLOR_B, String(i+1), 7, y_text, 1, TEXT_COLOR_W, true);
    printButton(30, y_button, 30, 30, BACKGROUND_COLOR_B, String(sstate[program.condition_list[i].get_condition_status()]), 37, y_text, 1, TEXT_COLOR_W, true);
    printButton(60, y_button, 60, 30, BACKGROUND_COLOR_B, String(program.condition_list[i].get_timeout()), 70, y_text, 1, TEXT_COLOR_W, true);
    printButton(120, y_button, 55, 30, BACKGROUND_COLOR_B, String(sstate[program.condition_list[i].get_p1()]), 127, y_text, 1, TEXT_COLOR_W, true);
    printButton(175, y_button, 55, 30, BACKGROUND_COLOR_B, String(sstate[program.condition_list[i].get_p2()]), 182, y_text, 1, TEXT_COLOR_W, true);
    printButton(230, y_button, 45, 30, BACKGROUND_COLOR_B, String(sstate[program.condition_list[i].get_wy1()]), 237, y_text, 1, TEXT_COLOR_W, true);
    printButton(275, y_button, 45, 30, BACKGROUND_COLOR_B, String(sstate[program.condition_list[i].get_wy2()]), 280, y_text, 1, TEXT_COLOR_W, true);
  }
}

void menu_program_01_print(Program &program)
{
  tft.fillScreen(BACKGROUND_COLOR_B);

  menu_program_01_print_buttons(program);
  menu_program_01_print_conditions(program);
  menu_program_01_update(program);
} // void menu_program_01_print(Program &program)

void menu_program_01_update(Program &program)
{
  while(1)
  {
    if(ts.touched())
    {
  
  TS_Point action = getPoint24();
  int item = -1;
  if(action.y > 40 && action.y < 60 && item == -1)
  {
      item = 0;
  } 
  else if(action.y > 80 && action.y < 100 && item == -1)
  {
      item = 1;
  } 
  else if(action.y > 120 && action.y < 140 && item == -1)
  {
      item = 2;
  } 
  else if(action.y > 160 && action.y < 180 && item == -1)
  {
      item = 3;
  } // if
  
  if(item >= 0)
  {
    unsigned timeout = 0;
    if(action.x > 30 && action.x < 60)
    {
      if(none == program.condition_list[item].get_condition_status())
      {
        program.condition_list[item].set_condition_status(active);
      } 
      else 
      {
        program.condition_list[item].set_condition_status(none);
      } // if
    printButton(30, 40*(item+1), 30, 30, BACKGROUND_COLOR_B, String(sstate[program.condition_list[item].get_condition_status()]), 37, 40*(item+1)+18, 1, TEXT_COLOR_W, true);
    } 
    else if(action.x > 65 && action.x < 115)
    {
      unsigned current_timeout = program.condition_list[item].get_timeout();
      if(600 <= current_timeout) 
      {
        program.condition_list[item].set_timeout(0);
        delay(1000);
      } 
      else if(600 > current_timeout && 60 < current_timeout)
      {
        timeout = current_timeout + 30;
        program.condition_list[item].set_timeout(timeout);
      } 
      else if(60 > current_timeout && 30 < current_timeout)
      {
        timeout = current_timeout + 2;
        program.condition_list[item].set_timeout(timeout);
      } 
      else 
      {
        timeout = current_timeout + 1;
        program.condition_list[item].set_timeout(timeout);
      } // if
    printButton(60, 40*(item+1), 60, 30, BACKGROUND_COLOR_B, String(program.condition_list[item].get_timeout()), 70, 40*(item+1)+18, 1, TEXT_COLOR_W, true);
    }
    else if(action.x > 125 && action.x < 170)
    {
      if(none == program.condition_list[item].get_p1())
      {
        program.condition_list[item].set_p1(zero);
      } 
      else if(zero == program.condition_list[item].get_p1())
      {
        program.condition_list[item].set_p1(one);
      } 
      else if(one == program.condition_list[item].get_p1())
      {
        program.condition_list[item].set_p1(two);
      } 
      else if(two == program.condition_list[item].get_p1())
      {
        program.condition_list[item].set_p1(three);
      } 
      else if(three == program.condition_list[item].get_p1())
      {
        program.condition_list[item].set_p1(none);
      } // if
    printButton(120, 40*(item+1), 55, 30, BACKGROUND_COLOR_B, String(sstate[program.condition_list[item].get_p1()]), 127, 40*(item+1)+18, 1, TEXT_COLOR_W, true);
    } 
    else if(action.x > 180 && action.x < 225)
    {
      if(none == program.condition_list[item].get_p2())
      {
        program.condition_list[item].set_p2(zero);
      } 
      else if(zero == program.condition_list[item].get_p2())
      {
        program.condition_list[item].set_p2(one);
      } 
      else if(one == program.condition_list[item].get_p2())
      {
        program.condition_list[item].set_p2(two);
      } 
      else if(two == program.condition_list[item].get_p2())
      {
        program.condition_list[item].set_p2(three);
      } 
      else if(three == program.condition_list[item].get_p2())
      {
        program.condition_list[item].set_p2(none);
      } // if
    printButton(175, 40*(item+1), 55, 30, BACKGROUND_COLOR_B, String(sstate[program.condition_list[item].get_p2()]), 182, 40*(item+1)+18, 1, TEXT_COLOR_W, true);
    } 
    else if(action.x > 235 && action.x < 270)
    {
      if(none == program.condition_list[item].get_wy1())
      {
        program.condition_list[item].set_wy1(on);
      } 
      else if(on == program.condition_list[item].get_wy1())
      {
        program.condition_list[item].set_wy1(off);
      } 
      else if(off == program.condition_list[item].get_wy1())
      {
        program.condition_list[item].set_wy1(none);
      } // if
    printButton(230, 40*(item+1), 45, 30, BACKGROUND_COLOR_B, String(sstate[program.condition_list[item].get_wy1()]), 237, 40*(item+1)+18, 1, TEXT_COLOR_W, true);
    } 
    else if(action.x > 280 && action.x < 315)
    {
      if(none == program.condition_list[item].get_wy2())
      {
        program.condition_list[item].set_wy2(on);
      } 
      else if(on == program.condition_list[item].get_wy2())
      {
        program.condition_list[item].set_wy2(off);
      } 
      else if(off == program.condition_list[item].get_wy2())
      {
        program.condition_list[item].set_wy2(none);
      } // if
    printButton(275, 40*(item+1), 45, 30, BACKGROUND_COLOR_B, String(sstate[program.condition_list[item].get_wy2()]), 280, 40*(item+1)+18, 1, TEXT_COLOR_W, true);
    } // if
  } // if

  if(action.x > 0 && action.x < tft.width()/3 && action.y > 200)
  {
    printButton(0, 200, tft.width()/2, 40, BACKGROUND_COLOR_B, "ANULUJ", 10, 230, 1, 0xF000, true);
    printButton(tft.width()/2, 200, tft.width()/2, 40, BACKGROUND_COLOR_B, "POTWIERDZ KASUJ", (tft.width()/2), 230, 1, 0xF000, true);
    while(1){
      if(ts.touched())
      {
        action = getPoint24();
        if(action.x < tft.width()/2 && action.y > 200){            
          menu_program_01_print_buttons(program);
          break;
        } else if(action.x > tft.width()/2 && action.y > 200){
          for(int item = 0 ; item < CONDITION_SIZE ; item++)
          {
            program.condition_list[item].reset_condition();
          }
          menu_program_01_print_conditions(program);
          menu_program_01_print_buttons(program);
          break;
        }
        delay(300);
      }
    }
  }
  else if(action.x > tft.width()/3 && action.x < 2*(tft.width()/3) && action.y > 200)
  {
    // go to main menu
    menu_program_00_print();
    break;
  }
  else if(action.x > 2*(tft.width()/3) && action.y > 200)
  {
    // save to eeprom
    // go to main menu
    menu_program_00_print();
    break;
  }  
    }
    delay(150);
  }
  delay(150);
  Serial.println("KONIEC menu_program_01_update");
} // void menu_program_01_update(Program &program)

void menu_program_00_print()
{
  tft.fillScreen(BACKGROUND_COLOR_B);
  tft.drawLine(0, 85, tft.width(), 85, TEXT_COLOR_W);
  tft.drawLine(85, 0, 85, 85, TEXT_COLOR_W);

  prepareText(1, 1, 1, TEXT_COLOR_W, false); // THIS LINE IS NECESSARY TO AVOID FORNT SHITFING
  prepareText(2, 30, 3, TEXT_COLOR_W, true);
  tft.print("B");
  prepareText(42, 55, 3, TEXT_COLOR_W, true);
  tft.print("R");
  prepareText(2, 75, 1, TEXT_COLOR_W, false);
  tft.print("b o t r o b i");

  prepareText(1, 1, 1, TEXT_COLOR_W, true); // THIS LINE IS NECESSARY TO AVOID FORNT SHITFING
  printButton(86, 0, 2*(tft.width()/3), 30, BACKGROUND_COLOR_B, "Program:", 90, 20, 1, TEXT_COLOR_W, true);
  printButton(86, 26, 2*(tft.width()/3), 30, BACKGROUND_COLOR_B, "Status:", 90, 46, 1, TEXT_COLOR_W, true);
  printButton(86, 52, 2*(tft.width()/3), 30, BACKGROUND_COLOR_B, "Czas Pracy:", 90, 72, 1, TEXT_COLOR_W, true);
  printButton(200, 0, (tft.width()/3)+15, 30, BACKGROUND_COLOR_B, "----------", 200, 20, 1, TEXT_COLOR_W, true);
  printButton(200, 26, (tft.width()/3)+15, 30, BACKGROUND_COLOR_B, "----------", 200, 46, 1, TEXT_COLOR_W, true);
  printButton(200, 52, (tft.width()/3)+15, 30, BACKGROUND_COLOR_B, "----------", 200, 72, 1, TEXT_COLOR_W, true);
  for(int item = 0 ; item < PROGRAMS_NUMBER ; item++)
  {
    int y_position = 40*(item+1)+50;
    printButton(0, y_position, 2*(tft.width()/3), 40, BACKGROUND_COLOR_B, program_list[item].program_name, 5, y_position+18, 1, TEXT_COLOR_W, true);
    if(false == program_list[item].get_program_status())
    {
      printButton(2*(tft.width()/3), y_position, tft.width()/3, 40, BACKGROUND_COLOR_B, "Start", 2*(tft.width()/3)+20, y_position+25, 2, GREEN_COLOR, true);
    }
    else
    {
      printButton(2*(tft.width()/3), y_position, tft.width()/3, 40, BACKGROUND_COLOR_B, "Stop", 2*(tft.width()/3)+20, y_position+25, 2, RED_COLOR, true);
    }
  }
  //menu_program_00_update();
}  // void menu_program_00_print(Program &program)

void menu_program_00_update()
{
      TS_Point action = getPoint24();
      int item = -1;
      if(action.y > 80 && action.y < 120 && item == -1)
      {
          item = 0;
      } 
      else if(action.y > 120 && action.y < 160 && item == -1)
      {
          item = 1;
      } 
      else if(action.y > 160 && action.y < 200 && item == -1)
      {
          item = 2;
      } 
      else if(action.y > 200 && action.y < 240 && item == -1)
      {
          item = 3;
      } // if
      
      if(action.x < 85 && action.y < 85)
      {
        // noop
      }else if(action.x >= 85 && action.y < 85) 
      {
        // noop
      }
      else if(action.x < 2*(tft.width()/3)) 
      {
        menu_program_01_print(program_list[item]);
  //      break;
      }
      else if(action.x > 2*(tft.width()/3)) 
      {
        if(item >= 0){
          for(int i=0 ;i < 4 ; i++){
            int y_position = 40*(i+1)+50;
            if(item != i){
              if(true == program_list[i].get_program_status()){
                program_list[i].set_program_status(false);
                printButton(2*(tft.width()/3), y_position, tft.width()/3, 40, BACKGROUND_COLOR_B, "Start", 2*(tft.width()/3)+20, y_position+25, 2, GREEN_COLOR, true);
              } else {
                // noop
              }
            } else {
              if(true == program_list[i].get_program_status()){
                program_list[i].set_program_status(false);
                printButton(2*(tft.width()/3), y_position, tft.width()/3, 40, BACKGROUND_COLOR_B, "Start", 2*(tft.width()/3)+20, y_position+25, 2, GREEN_COLOR, true);
              } else {
                program_list[i].set_program_status(true);
                printButton(2*(tft.width()/3), y_position, tft.width()/3, 40, BACKGROUND_COLOR_B, "Stop", 2*(tft.width()/3)+20, y_position+25, 2, RED_COLOR, true);
              }
            }
          }
        
          if(true == program_list[item].get_program_status()){
            printButton(200, 0, (tft.width()/3)+15, 30, BACKGROUND_COLOR_B, program_list[item].program_name, 200, 20, 1, TEXT_COLOR_W, true);
          } else {
            printButton(200, 0, (tft.width()/3)+15, 30, BACKGROUND_COLOR_B, "----------", 200, 20, 1, TEXT_COLOR_W, true);
          }
          Serial.print("Program 1: ");Serial.println(program_list[0].get_program_status());
          Serial.print("Program 2: ");Serial.println(program_list[1].get_program_status());
          Serial.print("Program 3: ");Serial.println(program_list[2].get_program_status());
          Serial.print("Program 4: ");Serial.println(program_list[3].get_program_status());
    //      break;
        }
      } else if(action.x > 85 && action.y < 85){
        // noop
    //    break;
      }
 //   }
//  }
delay(500);
}  //  void menu_program_00_update(Program &program)

*/

void setup() 
{
  Serial.begin(9600);
  tft.begin();
  if (!ts.begin()) 
  {
    Serial.println("Couldn't start touchscreen controller");
    while (1);
  }

  /////////////////
  tft.setRotation(3);
  pinMode(SOUND, OUTPUT);
  pinMode(6, OUTPUT);  // relay
  pinMode(LCD_LIGHT, OUTPUT);
  digitalWrite(SOUND, 0); //zmienilem na 1 z 0
  analogWrite(LCD_LIGHT, 255);
  analogReference(INTERNAL);
  ///////////////////
  // read eeprom here 
  menu_program_00_print();
}

//bool shortPressStatus = false;
//bool longPressStatus = false;
//bool programActive = false;
//unsigned long shortPressTimer = 0;
//unsigned long longPressTimer = 0;
//unsigned long currentTimer = 0;

void loop() 
{
  for(int i=0 ; i < PROGRAMS_NUMBER ; i++){
      program_list[i].execute_program();
  }

  if (ts.touched()) {
    menu_program_00_update();
  }
  Serial.print("program size: ");Serial.println(sizeof(program_list[0]));
}
