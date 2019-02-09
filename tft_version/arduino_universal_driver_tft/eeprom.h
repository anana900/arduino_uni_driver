#include <EEPROM.h>

void save_config(Program *item_list)
{
  Serial.println("Save to ram.");
  for(int i = 0 ; i < PROGRAMS_NUMBER ; i++){
    EEPROM.put(100 + i*EEPROM_ELEMENT_SIZE, item_list[i]);
    Serial.println(100 + i*EEPROM_ELEMENT_SIZE);
  }
}

void read_config(Program *item_list)
{
  Serial.println("Read from ram.");
  for(int i = 0 ; i < PROGRAMS_NUMBER ; i++){
    EEPROM.get(100 + i*EEPROM_ELEMENT_SIZE, item_list[i]);
    Serial.println(100 + i*EEPROM_ELEMENT_SIZE);
  }
}
