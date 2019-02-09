#include <EEPROM.h>

void save_config(Program *item_list)
{
  for(int i = 0 ; i < PROGRAMS_NUMBER ; i++){
    EEPROM.put(100 + i*EEPROM_ELEMENT_SIZE, item_list[i]);
  }
}

void read_config(Program *item_list)
{
  for(int i = 0 ; i < PROGRAMS_NUMBER ; i++){
    EEPROM.get(100 + i*EEPROM_ELEMENT_SIZE, item_list[i]);
  }
}
