
#include <LiquidCrystal.h>

#include <EEPROM.h>

const int stepPin = PC14;
const int ledpulse = PC13;
const int dirPin = 2;
const int enPin = 8;
const int STOPPER_PIN = PB12;
const int START_PIN = PA7;
int stepper = 296;
int cycle_delay = 0;
int VAL1 = 0;
int VAL2 = 0;
int VAL5 = 0;
int VAL6 = 0;
int stepper_speed = 0;
int select_roti = 0;
int select_delay = 0;
int sub_menu=0;
int L1 = 0;
int L2 = 0;
int L3 = 0;
int Roti = 0;
int elapsed = 0;
int saveaddr = 0;
uint Holdaddr = 0x10;
uint pressaddr = 0x12;

unsigned long previousMillis = 0;
const long interval = 5000;

unsigned long previousMillis2 = 0;
const long interval2 = 3000;

int Select=0;
int addz=0;
int sd=0;



const int rs = PB9, en = PB8, d4 = PB7, d5 = PB6, d6 = PB5, d7 = PB4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int roti_up = PB1;               //Up/Yes button
int delay_up = PB11;             //Select button
int roti_down = PB10;           //Down/No button
int delay_down = PA10;

boolean current_up = LOW;
boolean last_up = LOW;
boolean current_sel = LOW;
boolean last_sel = LOW;
boolean last_down = LOW;
boolean current_down = LOW;
boolean last_eep = LOW;
boolean current_eep = LOW;


boolean debounce(boolean last, int pin)
{
  boolean current = digitalRead(pin);
  if (last != current)
  {
    delay(5);
    current = digitalRead(pin);
  }
  return current;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // initialize the serial port:
  Serial.println("Ready to go!!!");
  pinMode(stepPin, OUTPUT);
  pinMode(ledpulse, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  pinMode(STOPPER_PIN, INPUT_PULLUP);
  pinMode(START_PIN, INPUT_PULLUP);

  digitalWrite(enPin, LOW);


  //  Status = EEPROM.read(saveaddr, &SAVEDATA);
  //select_roti = EEPROM.read(saveaddr);

  uint16 Status;
  uint16 Status2;
  uint16 HoldDATA;
  uint16 PressDATA;
  Status = EEPROM.read(Holdaddr, &HoldDATA);
  Status2 = EEPROM.read(pressaddr, &PressDATA);
  select_roti = HoldDATA;
  sub_menu = PressDATA;
  

  //select_roti = SAVEDATA;

  lcd.begin(16, 2);
  // Print a message to the LCD.

  // lcd.print("hello, world!");
}

void loop() {


for (int x = 0; x < 11000; x++)

      { //previously 800

        digitalWrite(stepPin, HIGH); digitalWrite(ledpulse, LOW);
        delayMicroseconds(180);
        digitalWrite(stepPin, LOW); digitalWrite(ledpulse, HIGH);
        delayMicroseconds(180);
        // Serial.println(x);
        //Start();

        if ((digitalRead(STOPPER_PIN) == HIGH))
        {
          x = 11000;
          VAL1 = VAL1 + 1;
          Serial.println("WW");
          Serial.println(x);
        }



      }







}
