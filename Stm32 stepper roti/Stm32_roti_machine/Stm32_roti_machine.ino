

#include <LiquidCrystal.h>

#include <EEPROM.h>

const int stepPin = PC14;
const int ledpulse = PC13;
const int dirPin = 2;
const int enPin = 8;
const int STOPPER_PIN = PB13;
const int START_PIN = PC15;
int stepper = 296;
int cycle_delay = 0;
int VAL1 = 0;
int VAL2 = 0;
int stepper_speed = 0;
int select_roti = 0;
int select_delay = 0;
int L1 = 0;
int L2 = 0;
int L3 = 0;
int Roti = 0;
int elapsed = 0;
int saveaddr = 0;
uint Holdaddr = 0x10;

unsigned long previousMillis = 0;
const long interval = 60000;



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
  pinMode(START_PIN, INPUT);

  digitalWrite(enPin, LOW);


  //  Status = EEPROM.read(saveaddr, &SAVEDATA);
  //select_roti = EEPROM.read(saveaddr);

  uint16 Status;
  uint16 HoldDATA;
  Status = EEPROM.read(Holdaddr, &HoldDATA);
  select_roti = HoldDATA;

  //select_roti = SAVEDATA;

  lcd.begin(16, 2);
  // Print a message to the LCD.

  // lcd.print("hello, world!");
}

void loop() {
  // put your main code here, to run repeatedly:

  //lcd.setCursor(0, 1);

  current_up = debounce(last_up, roti_up);         //Debounce for Up button
  current_sel = debounce(last_sel, delay_up);      //Debounce for Select  button
  current_down = debounce(last_down, roti_down);   //Debounce for Down button
  current_eep = debounce(last_eep, delay_down);   //Debounce for Down button




  DataSet();
  //lcd.clear();

  digitalWrite(ledpulse, HIGH);

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    uint16 Status;
    Status = EEPROM.update(Holdaddr, select_roti);
  }

  else {
  }

  if (VAL2 == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print("H");
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("L");
  }

  Start();

  stepper = stepper_speed;


  // if (digitalRead(START_PIN) == HIGH)
  //  {
  //    VAL2 = 0;
  //    VAL1 = 0;
  //  }
  //
  if (VAL2 == 1)
 {
    if (VAL1 == 0)
    {
      for (int x = 0; x < 11000; x++)

      { //previously 800

        digitalWrite(stepPin, HIGH); digitalWrite(ledpulse, LOW);
        delayMicroseconds(180);
        digitalWrite(stepPin, LOW); digitalWrite(ledpulse, HIGH);
        delayMicroseconds(180);
        // Serial.println(x);
        Start();

        if ((digitalRead(STOPPER_PIN) == HIGH))
        {
          x = 11000;
          VAL1 = VAL1 + 1;
          Serial.println("WW");
        }



      }

      //    lcd.setCursor(3,0);
      //    lcd.print("Sensor Problem");
      //     lcd.setCursor(3,0);
      //    lcd.print("Homing Not Done");
      // VAL1 = VAL1 + 1;
      //VAL2 = VAL2 + 1;

      delay(1000);
      Serial.println("EE");
    }

Serial.println("TT");
    for (int x = 0; x < L1; x++)

    { //previously 800

      for (int y = 0; y < L2; y++)
      {

        digitalWrite(stepPin, HIGH); digitalWrite(ledpulse, LOW);
        delayMicroseconds(stepper);
        digitalWrite(stepPin, LOW); digitalWrite(ledpulse, HIGH);
        delayMicroseconds(stepper);
      }

      stepper = stepper - 5;


      Start();


    }

    for (int y = 0; y < L3; y++)
    {

      digitalWrite(stepPin, HIGH); digitalWrite(ledpulse, LOW);
      delayMicroseconds(stepper);
      digitalWrite(stepPin, LOW); digitalWrite(ledpulse, HIGH);
      delayMicroseconds(stepper);
      Start();

    }

    Serial.println(stepper);
    for (int x = 0; x < 125; x++)

    { //previously 800

      for (int y = 0; y < 32; y++)
      {

        digitalWrite(stepPin, HIGH); digitalWrite(ledpulse, LOW);
        delayMicroseconds(stepper);
        digitalWrite(stepPin, LOW); digitalWrite(ledpulse, HIGH);
        delayMicroseconds(stepper);
        Start();
      }

      stepper = stepper + 1;
      Start();

    }

    for (int y = 0; y < 1000; y++)
    {

      digitalWrite(stepPin, HIGH); digitalWrite(ledpulse, LOW);
      delayMicroseconds(stepper);
      digitalWrite(stepPin, LOW); digitalWrite(ledpulse, HIGH);
      delayMicroseconds(stepper);
      Start();


    }

    Start();
    DataSet();
    delay(cycle_delay);
    //delay(1600);
    Serial.println(select_roti);
    stepper = stepper_speed;
    Serial.println(stepper);
    Serial.println(L1);
    Serial.println(L2);
    Serial.println(L3);
    Serial.println(Roti);
    //stepper=296;

  }
}







void DataSet()
{
  if (last_up == LOW && current_up == HIGH) { //Up button pressed
    select_roti = select_roti + 1;
    lcd.clear();
  }
  else {
  }
  last_up = current_up;

  if (last_down == LOW && current_down == HIGH) { //Up button pressed

    select_roti = select_roti - 1;
    lcd.clear();

  }
  else {
  }
  last_down = current_down;
  if (select_roti > 17)
  {
    select_roti = 0;
  }
  if (select_roti < 0)
  {
    select_roti = 0;
  }
  switch (select_roti) {


    case 2:    // your hand is on the sensor


      stepper_speed = 320;
      cycle_delay = 1100;
      L1 = 40;
      L2 = 25;
      L3 = 4000;
      Roti = 1000;
      lcd.setCursor(3, 0);
      lcd.print("Roti");
      lcd.setCursor(9, 0);
      lcd.print("Cyc Delay");
      lcd.setCursor(3, 1);
      lcd.print(1000);
      lcd.setCursor(11, 1);
      lcd.print(cycle_delay / 1000.0);




      break;



      case 1:    // your hand is on the sensor


      stepper_speed = 295;
      cycle_delay = 1100;
      L1 = 40;
      L2 = 25;
      L3 = 4000;
      Roti = 1100;
      lcd.setCursor(3, 0);
      lcd.print("Roti");
      lcd.setCursor(9, 0);
      lcd.print("Cyc Delay");
      lcd.setCursor(3, 1);
      lcd.print(1100);
      lcd.setCursor(11, 1);
      lcd.print(cycle_delay / 1000.0);




      break;



      case 0:    // your hand is on the sensor


      stepper_speed = 275;
      cycle_delay = 1100;
      L1 = 40;
      L2 = 25;
      L3 = 4000;
      Roti = 1200;
      lcd.setCursor(3, 0);
      lcd.print("Roti");
      lcd.setCursor(9, 0);
      lcd.print("Cyc Delay");
      lcd.setCursor(3, 1);
      lcd.print(1200);
      lcd.setCursor(11, 1);
      lcd.print(cycle_delay / 1000.0);




      break;

      

    case 7:    // your hand is on the sensor

     // stepper_speed = 270;
      stepper_speed = 320;
      cycle_delay = 1500;
      L1 = 40;
      L2 = 25;
      L3 = 4000;
      Roti = 915;
      lcd.setCursor(3, 0);
      lcd.print("Roti");
      lcd.setCursor(9, 0);
      lcd.print("Cyc Delay");
      lcd.setCursor(3, 1);
      lcd.print(900);
      lcd.setCursor(11, 1);
      lcd.print(cycle_delay / 1000.0);

      break;

    case 6:    // your hand is on the sensor

      //stepper_speed = 277;
      stepper_speed = 328;
      cycle_delay = 1400;
      L1 = 40;
      L2 = 25;
      L3 = 4000;
      Roti = 914;
      lcd.setCursor(3, 0);
      lcd.print("Roti");
      lcd.setCursor(9, 0);
      lcd.print("Cyc Delay");
      lcd.setCursor(3, 1);
      lcd.print(900);
      lcd.setCursor(11, 1);
      lcd.print(cycle_delay / 1000.0);

      break;

    case 5:    // your hand is on the sensor

     //stepper_speed = 283;
     stepper_speed = 334;
      cycle_delay = 1300;
      L1 = 40;
      L2 = 25;
      L3 = 4000;
      Roti = 913;
      lcd.setCursor(3, 0);
      lcd.print("Roti");
      lcd.setCursor(9, 0);
      lcd.print("Cyc Delay");
      lcd.setCursor(3, 1);
      lcd.print(900);
      lcd.setCursor(11, 1);
      lcd.print(cycle_delay / 1000.0);

      break;


    case 4:    // your hand is on the sensor

      //stepper_speed = 288;
      stepper_speed = 340;
      cycle_delay = 1200;
      L1 = 40;
      L2 = 25;
      L3 = 4000;
      Roti = 912;
      lcd.setCursor(3, 0);
      lcd.print("Roti");
      lcd.setCursor(9, 0);
      lcd.print("Cyc Delay");
      lcd.setCursor(3, 1);
      lcd.print(900);
      lcd.setCursor(11, 1);
      lcd.print(cycle_delay / 1000.0);

      break;

    case 3:    // your hand is on the sensor

      //stepper_speed = 292;
      stepper_speed = 345;
      cycle_delay = 1100;
      L1 = 40;
      L2 = 25;
      L3 = 4000;
      Roti = 911;
      lcd.setCursor(3, 0);
      lcd.print("Roti");
      lcd.setCursor(9, 0);
      lcd.print("Cyc Delay");
      lcd.setCursor(3, 1);
      lcd.print(900);
      lcd.setCursor(11, 1);
      lcd.print(cycle_delay / 1000.0);

      break;


    case 12:    // your hand is on the sensor

      //stepper_speed = 296;
      stepper_speed = 360;
      cycle_delay = 1500;
      L1 = 40;
      L2 = 25;
      L3 = 4000;
      Roti = 815;
      lcd.setCursor(3, 0);
      lcd.print("Roti");
      lcd.setCursor(9, 0);
      lcd.print("Cyc Delay");
      lcd.setCursor(3, 1);
      lcd.print(800);
      lcd.setCursor(11, 1);
      lcd.print(cycle_delay / 1000.0);

      break;

    case 11:    // your hand is on the sensor

      //stepper_speed = 296;
      stepper_speed = 360;
      cycle_delay = 1400;
      L1 = 40;
      L2 = 35;
      L3 = 3600;
      Roti = 814;
      lcd.setCursor(3, 0);
      lcd.print("Roti");
      lcd.setCursor(9, 0);
      lcd.print("Cyc Delay");
      lcd.setCursor(3, 1);
      lcd.print(800);
      lcd.setCursor(11, 1);
      lcd.print(cycle_delay / 1000.0);

      break;

    case 10:    // your hand is on the sensor

     // stepper_speed = 296;
     stepper_speed = 360;
      cycle_delay = 1300;
      L1 = 40;
      L2 = 45;
      L3 = 3200;
      Roti = 813;
      lcd.setCursor(3, 0);
      lcd.print("Roti");
      lcd.setCursor(9, 0);
      lcd.print("Cyc Delay");
      lcd.setCursor(3, 1);
      lcd.print(800);
      lcd.setCursor(11, 1);
      lcd.print(cycle_delay / 1000.0);

      break;

    case 9:    // your hand is on the sensor

      //stepper_speed = 296;
      stepper_speed = 360;
      cycle_delay = 1200;
      L1 = 40;
      L2 = 57;
      L3 = 2720;
      Roti = 812;
      lcd.setCursor(3, 0);
      lcd.print("Roti");
      lcd.setCursor(9, 0);
      lcd.print("Cyc Delay");
      lcd.setCursor(3, 1);
      lcd.print(800);
      lcd.setCursor(11, 1);
      lcd.print(cycle_delay / 1000.0);

      break;


    case 8:    // your hand is on the sensor

     // stepper_speed = 296;
     stepper_speed = 360;
      cycle_delay = 1100;
      L1 = 40;
      L2 = 67;
      L3 = 2320;
      Roti = 811;
      lcd.setCursor(3, 0);
      lcd.print("Roti");
      lcd.setCursor(9, 0);
      lcd.print("Cyc Delay");
      lcd.setCursor(3, 1);
      lcd.print(800);
      lcd.setCursor(11, 1);
      lcd.print(cycle_delay / 1000.0);

      break;


    case 13:    // your hand is on the sensor

      //stepper_speed = 296;
      stepper_speed = 373;
      cycle_delay = 1100;
      L1 = 38;
      L2 = 131;
      L3 = 22;
      Roti = 711;
      lcd.setCursor(3, 0);
      lcd.print("Roti");
      lcd.setCursor(9, 0);
      lcd.print("Cyc Delay");
      lcd.setCursor(3, 1);
      lcd.print(700);
      lcd.setCursor(11, 1);
      lcd.print(cycle_delay / 1000.0);

      break;


    case 14:    // your hand is on the sensor

      stepper_speed = 373;
      cycle_delay = 1200;
      L1 = 40;
      L2 = 125;
      L3 = 0;
      Roti = 712;
      lcd.setCursor(3, 0);
      lcd.print("Roti");
      lcd.setCursor(9, 0);
      lcd.print("Cyc Delay");
      lcd.setCursor(3, 1);
      lcd.print(700);
      lcd.setCursor(11, 1);
      lcd.print(cycle_delay / 1000.0);

      break;


    case 15:    // your hand is on the sensor

      stepper_speed = 373;
      cycle_delay = 1300;
      L1 = 40;
      L2 = 115;
      L3 = 400;
      Roti = 713;
      lcd.setCursor(3, 0);
      lcd.print("Roti");
      lcd.setCursor(9, 0);
      lcd.print("Cyc Delay");
      lcd.setCursor(3, 1);
      lcd.print(700);
      lcd.setCursor(11, 1);
      lcd.print(cycle_delay / 1000.0);

      break;

    case 16:    // your hand is on the sensor

      stepper_speed = 373;
      cycle_delay = 1400;
      L1 = 40;
      L2 = 105;
      L3 = 800;
      Roti = 714;
      lcd.setCursor(3, 0);
      lcd.print("Roti");
      lcd.setCursor(9, 0);
      lcd.print("Cyc Delay");
      lcd.setCursor(3, 1);
      lcd.print(700);
      lcd.setCursor(11, 1);
      lcd.print(cycle_delay / 1000.0);

      break;

    case 17:    // your hand is on the sensor

      stepper_speed = 373;
      cycle_delay = 1500;
      L1 = 40;
      L2 = 95;
      L3 = 1200;
      Roti = 715;
      lcd.setCursor(3, 0);
      lcd.print("Roti");
      lcd.setCursor(9, 0);
      lcd.print("Cyc Delay");
      lcd.setCursor(3, 1);
      lcd.print(700);
      lcd.setCursor(11, 1);
      lcd.print(cycle_delay / 1000.0);

      break;

  }
}



void Start()
{
  if (last_sel == LOW && current_sel == HIGH) { //Up button pressed
    VAL2 = VAL2 + 1;
    lcd.setCursor(0, 0);
    lcd.print(VAL2);

  }
  else {
  }
  last_sel = current_sel;

  if (VAL2 > 2)
  {
    VAL2 = 0;
    VAL1 = 0;
  }
}
