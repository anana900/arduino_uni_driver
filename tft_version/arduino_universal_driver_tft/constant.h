#define PORT1 A0
#define PORT2 A1
#define OUT1 2        //4
#define OUT2 6        //5
#define SOUND 2
#define STMPE_CS 8    // CS Touch SPI
#define SD_CS_PIN 7   //CS SD card
#define TFT_DC 9      //CD LCD SPI
#define TFT_CS 10     //CS LCD SPI
#define LCD_LIGHT 3
#define BACKGROUND_COLOR_B 0x0000  //default backgrount color
#define TEXT_COLOR_W 0xFFFF        //default text color
#define RED_COLOR 0xF800
#define GREEN_COLOR 0x07E0
#define BLUE_COLOR 0x001F
#define CYAN_COLOR 0x07FF
#define MAGENTA_COLOR 0xF81F
#define YELLOW_COLOR 0xFFE0

int global_alarm_set,
    global_sound_set=1,
    global_temp_unit_set,
    global_colors_set,
    global_backlight_set=1;
    
const byte PROGRAM_NAME_LENGTH = 10;
const byte CONDITION_SIZE = 8;
const byte PROGRAMS_NUMBER = 4;
String program_name[PROGRAMS_NUMBER] = {"PROGRAM 1", "PROGRAM 2", "PROGRAM 3", "PROGRAM 4"};
const byte ALPHABET[25] = {'_','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','R','S','T','U','W','X','Y','Z'};
const int EEPROM_ELEMENT_SIZE = 143;
const String DA______SH = "----------";

// enum state is corelated with sstate array of strings
const String sstate[] = {"0", "100", "200", "300", "-", "A", "OFF", "ON", "Error"};
enum state
{
    none = 4,
    active = 5,
    off = 6,
    on = 7,
    error = 8,
    ok = 9,
    zero = 0,
    one = 1,
    two = 2,
    three = 3
};
