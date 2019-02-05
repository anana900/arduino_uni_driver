#define PORT1 A0
#define PORT2 A1
#define OUT1 2//4
#define OUT2 6//5
const byte PROGRAM_NAME_LENGTH = 10;
const byte CONDITION_SIZE = 8;
const byte PROGRAMS_NUMBER = 4;
const byte ALPHABET[25] = {'_','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','R','S','T','U','W','X','Y','Z'};
const int EEPROM_ELEMENT_SIZE = 143;
String sstate[] = {"0", "100", "200", "300", "-", "A", "OFF", "ON", "Error"};

#define SOUND 2
#define STMPE_CS 8 // CS Touch SPI
#define SD_CS_PIN 7 //CS SD card
#define TFT_DC 9  //CD LCD SPI
#define TFT_CS 10 //CS LCD SPI
#define LCD_LIGHT 3
#define LONG_CLICK_DELAY 1500
#define SHORT_CLICK_DELAY 200
#define ARROW_DISPLAY_DELAY 6000
#define BACKGROUND_COLOR_B 0x0000//ILI9341_BLACK  //default backgrount color
#define TEXT_COLOR_W 0xFFFF//ILI9341_WHITE  //default text color
#define RED_COLOR 0xF800//ILI9341_RED
#define GREEN_COLOR 0x07E0//ILI9341_GREEN

/*
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
*/


#define TEMP_MIN 0
#define TEMP_MAX 400
#define AC_RESOLUTION 750
#define SENSORS_NUMBER 8  //number of sensors supported by device
#define ARROW_X_POSITION 40 //main temperature panel x position of arrow
#define TEMPERATURE_X_POSITION 90 //main temperature panel x position of temperature
#define CHAR_CLEANER 0xDA // special 0xFFFF character for clear function
#define DEGREE 0x21 //degree character, 0xDE - TODO implement 8bit font with full characters set
#define TXT_DZWIEK_ON "Dzwiek ON"
#define TXT_DZWIEK_OFF "Dzwiek OFF"
#define TXT_POMIAR_ON "Pomiar ON"
#define TXT_POMIAR_OFF "Pomiar OFF"
#define TXT_ALARM_ON "Alarm ON"
#define TXT_ALARM_OFF "Alarm OFF"
#define TXT_RELAY_ON "Wyjscie ON"
#define TXT_RELAY_OFF "Wyjscie OFF"
#define TXT_OK "OK"
#define TXT_ANULUJ "Anuluj"

int global_alarm_set,
    global_sound_set=1,
    global_temp_unit_set,
    global_colors_set,
    global_backlight_set=1;

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
