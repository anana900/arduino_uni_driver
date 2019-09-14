#define PORT1 A6
#define PORT2 A7
#define OUT1 5
#define OUT2 6
#define SOUND 4
#define STMPE_CS 10
#define TFT_DC 9
#define TFT_CS 7
#define TFT_RESET 8
#define BACKGROUND_COLOR_B 0x0000  //default background color
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
String program_name[PROGRAMS_NUMBER] = {"PROGRAM   1", "PROGRAM   2", "PROGRAM   3", "PROGRAM   4"};
const int EEPROM_ELEMENT_SIZE = 143;
const String DA______SH = "----------";

// enum state is corelated with sstate array of strings
const String sstate[] = {"0", "B", "C", "CB", "-", "A", "OFF", "ON", "Error"};
enum state
{
    none = 4,
    active = 5,
    off = 6,
    on = 7,
    error = 8,
    zero = 0,
    one = 1,
    two = 2,
    three = 3
};
