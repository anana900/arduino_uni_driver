#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const uint8_t SWITCH_PORT = A7;
const int NAME_LENGTH = 8;
const int CONDITION_SIZE = 8;
const int PROGRAMS_NUMBER = 4;
const int DISPLAY_COLUMNS = 20;
const int DISPLAY_ROWS = 4;
const char condition_title[DISPLAY_COLUMNS] = "WS P1 P2 W1 W2 To";

class Lcd{
  public:
  Lcd():lcd_x(0), lcd_y(0), code('0'){}
  char code;
  int lcd_x;
  int lcd_y;
};

class Switch{ 
  public:
  Lcd lcd_cursor;
  void  setup_switch(){pinMode(SWITCH_PORT, INPUT);}
  
  void update_cursor(int x, int y){
    lcd.setCursor(x, y);
    lcd.blink();
  }
  
  void decode_switch(int state){
    lcd_cursor.code = '0';
    if(state > 150 && state <= 200 && lcd_cursor.lcd_x<DISPLAY_COLUMNS-1){
      ++lcd_cursor.lcd_x;
      lcd_cursor.code = 'P';
      update_cursor(lcd_cursor.lcd_x, lcd_cursor.lcd_y);
    } else if (state > 300 && state <= 350 && lcd_cursor.lcd_y<DISPLAY_ROWS-1){
      ++lcd_cursor.lcd_y;
      lcd_cursor.code = 'G';
      update_cursor(lcd_cursor.lcd_x, lcd_cursor.lcd_y);
    } else if (state > 450 && state <= 550 && lcd_cursor.lcd_x>0){
      --lcd_cursor.lcd_x;
      lcd_cursor.code = 'L';
      update_cursor(lcd_cursor.lcd_x, lcd_cursor.lcd_y);
    } else if (state > 650 && state <= 800){
      lcd_cursor.code = 'E';
      update_cursor(lcd_cursor.lcd_x, lcd_cursor.lcd_y);
    } else if (state > 950 && state <= 1024 && lcd_cursor.lcd_y>0){
      --lcd_cursor.lcd_y;
      lcd_cursor.code = 'D';
      update_cursor(lcd_cursor.lcd_x, lcd_cursor.lcd_y);
    }
  }
  
};

class Condition
{
  enum state{
    active = 'A',
    none = '-',
    one = 100,
    two = 200,
    three = 300,
    off = '0',
    on = '1',
  };
  
  state condition_status;
  state p1;
  state p2;
  state wy1;
  state wy2;
  int timeout_wy1;
  int timeout_wy2;
  public: 
  Condition() : condition_status(none), p1(none), p2(none), wy1(none), wy2(none), timeout_wy1(0), timeout_wy2(0){}
  ~Condition(){}
  char get_condition_status(){return condition_status;}
  int get_p1(){return p1;}
  int get_p2(){return p2;}
  int get_wy1(){return wy1;}
  int get_wy2(){return wy2;}
  int get_timeout_wy1(){return timeout_wy1;}
  int get_timeout_wy2(){return timeout_wy2;}
};

class Program : Condition
{
  char program_name[NAME_LENGTH];
  bool program_status;
  Condition program_list[CONDITION_SIZE];
  public:
  Program(){}
  void setup_program(){}
  void loop_program(){
    lcd.print(condition_title);
    for(int condition_i = 0 ; condition_i < DISPLAY_ROWS - 1 ; condition_i++){
        lcd.setCursor(0, condition_i+1);
        lcd.print(condition_i+1);
        lcd.print(program_list[condition_i].get_condition_status());
        lcd.print(" ");
        lcd.print(program_list[condition_i].get_p1());
        lcd.print(" ");
        lcd.print(program_list[condition_i].get_p2());
        lcd.print(" ");
        lcd.print(program_list[condition_i].get_wy1());
        lcd.print(" ");
        lcd.print(program_list[condition_i].get_wy2());
        lcd.print(" ");
        lcd.print(program_list[condition_i].get_timeout_wy1());
        lcd.print(" ");
        lcd.print(program_list[condition_i].get_timeout_wy2());     
    }
  }
};

void save_to_eeprom(){}
void read_from_eeprom(){}

void menu_1_print(){
  // read eeprom
  int eeprom_size = 1;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dodaj Program");
  for(int i = 1 ; i < DISPLAY_ROWS ; i++){
    if(0) {  // if eeprom contains
      lcd.print("");
    } else {
      lcd.setCursor(0, i);
      lcd.print(" - - - - - - - - -");
    } 
  }
}

void menu_add_program(){
  lcd.blink();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Program setup...");
}

void select_menu(Lcd &lcdpos){
  if(lcdpos.lcd_x >= 0 && lcdpos.lcd_x < 14 && 
     lcdpos.lcd_y == 0 && 
     lcdpos.code == 'E'){
     menu_add_program();
  }
}

Switch buttons;
Program* program_list = new Program[PROGRAMS_NUMBER];

void setup() {
  Serial.begin(9600);
  lcd.begin(DISPLAY_COLUMNS, DISPLAY_ROWS);
  buttons.setup_switch();
  //program_list[0].loop_program();
  menu_1_print();
}

int button_state = 0;
long button_last_debounce = 0;
int button_debounce_delay = 150;
  
void loop() 
{
  button_state = analogRead(SWITCH_PORT);
  if ((millis() - button_last_debounce) > button_debounce_delay) {
    if(button_state != 0){
      buttons.decode_switch(analogRead(SWITCH_PORT));
      button_last_debounce = millis();
    }
  }
  
  select_menu(buttons.lcd_cursor);
}
