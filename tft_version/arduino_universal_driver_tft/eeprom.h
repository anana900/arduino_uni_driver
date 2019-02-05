#include <EEPROM.h>
/*
void _eepromReadConfig(){
  for(int port=0 ; port<8; port++){
    temp[2][port] = EEPROM.read(32 + port);
    temp[3][port] = EEPROM.read(40 + port);
    temp[4][port] = EEPROM.read(48 + port);
    temp[5][port] = EEPROM.read(56 + port);
  }
  global_temp_unit_set = EEPROM.read(64);
  global_sound_set = EEPROM.read(65);
  global_alarm_set = EEPROM.read(66);
  global_colors_set = EEPROM.read(67);
}
*/

//void save_config(Program item)
//{
//  for(int i=1 ; i<=PROGRAMS_NUMBER ; i++){
//    EEPROM.put(100 + i*EEPROM_ELEMENT_SIZE, item);
 // }
//   EEPROM.write(32 + port, tempAlarm);
//  temp[2][port] = tempAlarm;
//}

/*
void saveGlobal(int unit, int sound, int alarm, int color){

   EEPROM.write(64, unit);
  global_temp_unit_set = unit;

  EEPROM.write(65, sound);
  global_sound_set = sound;

  EEPROM.write(66, alarm);
  global_alarm_set = alarm;

  EEPROM.write(67, color);
  global_colors_set = color;
}

void _eepromReset(){
  for(int port=0;port<SENSORS_NUMBER;port++){
    savePort(port, 0, 299, 1, 1);
  }
  saveGlobal(0,0,0,1);
}

*/
