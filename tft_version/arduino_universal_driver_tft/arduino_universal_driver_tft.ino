#include <SPI.h>
#include "constant.h"
#include "Program.h"
Program* program_list = new Program[PROGRAMS_NUMBER];
#include "eeprom.h"
#include "tft.h"

void setup() 
{
  Serial.begin(9600);
  tft.begin();
  while (!ts.begin()) 
  {
    soundClic(5000);
    delay(5000);
    Serial.println("Couldn't start touchscreen controller");
    //while (1);
  }

  ///////TMP SETTINGS FOR DEVELOPMENT BOARD BEGIN//////////
  tft.setRotation(3);
  pinMode(SOUND, OUTPUT);
  pinMode(6, OUTPUT);  // relay
  pinMode(LCD_LIGHT, OUTPUT);
  digitalWrite(SOUND, 0); //zmienilem na 1 z 0
  analogWrite(LCD_LIGHT, 255);
  //analogReference(INTERNAL);
  ///////TMP SETTINGS FOR DEVELOPMENT BOARD END//////////

  /*
   * This function is run only once when saving configuration into the EEPROM.
   * save_config(program_list);
  */

//save_config(program_list);
  read_config(program_list);
  menu_program_00_print();
}

void loop() 
{
  for(int i=0 ; i < PROGRAMS_NUMBER ; i++){
      program_list[i].execute_program();
  }

  if (ts.touched()) {
    soundClic();
    menu_program_00_update();
  }
}
