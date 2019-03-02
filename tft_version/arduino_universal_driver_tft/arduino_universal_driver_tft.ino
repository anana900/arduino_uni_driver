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
  }

  tft.setRotation(3);
  pinMode(SOUND, OUTPUT);
  pinMode(OUT1, OUTPUT);  // relay
  pinMode(OUT2, OUTPUT);  // relay
  digitalWrite(OUT1, HIGH);  // relay
  digitalWrite(OUT2, HIGH);  // relay

  /*
   * This function is run only once when uploading the program very first time.
   * save_config(program_list);
  */

  read_config(program_list);
  menu_program_00_print();  
}

void loop() 
{
  for(int i=0 ; i < PROGRAMS_NUMBER ; i++)
  {
      program_list[i].execute_program();
  }

  if (ts.touched())
  {
    soundClic();
    menu_program_00_update();
  }
}
