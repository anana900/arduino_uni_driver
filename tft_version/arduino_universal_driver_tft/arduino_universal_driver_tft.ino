#include <SPI.h>
#include "constant.h"
#include "Program.h"
Program* program_list = new Program[PROGRAMS_NUMBER];
#include "tft.h"
#include "eeprom.h"

void printButton(int x, int y, int width, int height, uint16_t buttonColor, String text = "", int tx = 0, int ty = 0, int textSize = 1, uint16_t textColor = TEXT_COLOR_W, boolean customf = false);

TS_Point getPoint24();

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

void save_to_eeprom(){}
void read_from_eeprom(){}

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
