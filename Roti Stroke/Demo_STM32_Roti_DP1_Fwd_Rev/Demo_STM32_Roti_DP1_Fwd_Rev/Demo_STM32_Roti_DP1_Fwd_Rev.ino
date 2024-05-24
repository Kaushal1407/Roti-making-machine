#include <LiquidCrystal.h>

#include <EEPROM.h>

const int stepPin = PB15;
const int ledpulse = PC13;
const int revPin = PB14;
const int dirPin = 2;
const int enPin = 8;
const int STOPPER_PIN = PB13;
const int START_PIN = PC15;
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
int L4 = 0;
int L5 = 0;
int L6 = 0;
int L7 = 0;
int L8 = 0;
int L9 = 0;
int L10 = 0;
int L11 = 0;
int L12 = 0;
int L13 = 0;
int L14 = 0;
int Roti = 0;
int fix_delay = 0;
int rev_delay = 0;
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
  pinMode(revPin, OUTPUT);
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
  // put your main code here, to run repeatedly:

  //lcd.setCursor(0, 1);

  current_up = debounce(last_up, roti_up);         //Debounce for Up button
  current_sel = debounce(last_sel, delay_up);      //Debounce for Select  button
  current_down = debounce(last_down, roti_down);   //Debounce for Down button
  current_eep = debounce(last_eep, delay_down);   //Debounce for Down button

//Select=digitalRead(START_PIN);
// Serial.println(millis());


  DataSet();

//if ( Select==HIGH)
//{
//  digitalWrite(ledpulse, LOW);
//
//delay(3000);
//addz=1;
//
//  }
//
//  if(addz==1)
//  {
//     select_roti++;
//  lcd.clear();
//  sd++;
//  addz=0;
//   Serial.println(select_roti);
//   Serial.println(sd);
//  }
//  


 
  
  //lcd.clear();
  



  digitalWrite(ledpulse, HIGH);

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    uint16 Status;
    uint16 Status2;
    Status = EEPROM.update(Holdaddr, select_roti);
     Status2 = EEPROM.update(pressaddr, sub_menu);
     //digitalWrite(ledpulse, LOW);
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

   delay(100);
      Serial.println("EE");
    }

     if (VAL1 == 1)
    {
      for (int p = 0; p < 5000; p++)

      { //previously 800

        digitalWrite(stepPin, HIGH); digitalWrite(ledpulse, LOW);
        delayMicroseconds(180);
        digitalWrite(stepPin, LOW); digitalWrite(ledpulse, HIGH);
        delayMicroseconds(180);
        // Serial.println(p);
        Start();

      



      }

   delay(100);
    VAL1 = VAL1 + 1;
      Serial.println("55EE");
      Serial.println(VAL1);
    }



      if (VAL1 == 2)
    {
      for (int q = 0; q < 11000; q++)

      { //previously 800

        digitalWrite(stepPin, HIGH); digitalWrite(ledpulse, LOW);
        delayMicroseconds(180);
        digitalWrite(stepPin, LOW); digitalWrite(ledpulse, HIGH);
        delayMicroseconds(180);
        // Serial.println(q);
        Start();

        if ((digitalRead(STOPPER_PIN) == HIGH))
        {
          q = 11000;
          VAL1 = VAL1 + 1;
          Serial.println("6666");
        }



      }

   delay(1000);
      Serial.println("66EE");
    }
Serial.println(VAL2);
Serial.println("TT");
digitalWrite(revPin, HIGH);

    for (int x = 0; x < L1; x++)
    

    { 

      for (int y = 0; y < L2; y++)
      {

        digitalWrite(stepPin, HIGH); digitalWrite(ledpulse, LOW);
        delayMicroseconds(stepper);
        digitalWrite(stepPin, LOW); digitalWrite(ledpulse, HIGH);
        delayMicroseconds(stepper);
      }

      stepper = stepper - 3;


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
    for (int x = 0; x < L4; x++)

    { 

      for (int y = 0; y < L5; y++)
      {

        digitalWrite(stepPin, HIGH); digitalWrite(ledpulse, LOW);
        delayMicroseconds(stepper);
        digitalWrite(stepPin, LOW); digitalWrite(ledpulse, HIGH);
        delayMicroseconds(stepper);
        Start();
      }

      stepper = stepper + 2;
      Start();

    }


    Start();
    DataSet();
    delay(fix_delay);
    Serial.println(select_roti);
    stepper = stepper_speed;
    Serial.println("cycle1");
    Serial.println(stepper);
    Serial.println(L1);
    Serial.println(L2);
    Serial.println(L3);
    Serial.println(Roti);



   for (int x = 0; x < L6; x++)

    {

      for (int y = 0; y < L7; y++)
      {

        digitalWrite(stepPin, HIGH); digitalWrite(ledpulse, LOW);
        delayMicroseconds(stepper);
        digitalWrite(stepPin, LOW); digitalWrite(ledpulse, HIGH);
        delayMicroseconds(stepper);
      }

      stepper = stepper - 5;


      Start();


    }

    for (int y = 0; y < L8; y++)
    {

      digitalWrite(stepPin, HIGH); digitalWrite(ledpulse, LOW);
      delayMicroseconds(stepper);
      digitalWrite(stepPin, LOW); digitalWrite(ledpulse, HIGH);
      delayMicroseconds(stepper);
      Start();

    }

    Serial.println(stepper);
    for (int x = 0; x < L9; x++)

    { //previously 800

      for (int y = 0; y < L10; y++)
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

    for (int y = 0; y < L11; y++)
    {

      digitalWrite(stepPin, HIGH); digitalWrite(ledpulse, LOW);
      delayMicroseconds(stepper);
      digitalWrite(stepPin, LOW); digitalWrite(ledpulse, HIGH);
      delayMicroseconds(stepper);
      Start();


    }

    Start();
    DataSet();
    digitalWrite(revPin, LOW);
    delay(rev_delay);
    Serial.println(select_roti);
    stepper = stepper_speed;
    Serial.println("cycle2");
    Serial.println(stepper);
    Serial.println(L1);
    Serial.println(L2);
    Serial.println(L3);
    Serial.println(Roti);



   for (int x = 0; x < L12; x++)

    {

      for (int y = 0; y < L13; y++)
      {

        digitalWrite(stepPin, HIGH); digitalWrite(ledpulse, LOW);
        delayMicroseconds(stepper);
        digitalWrite(stepPin, LOW); digitalWrite(ledpulse, HIGH);
        delayMicroseconds(stepper);
      }

      stepper = stepper - 1;


      Start();


    }

    for (int y = 0; y < L14; y++)
    {

      digitalWrite(stepPin, HIGH); digitalWrite(ledpulse, LOW);
      delayMicroseconds(stepper);
      digitalWrite(stepPin, LOW); digitalWrite(ledpulse, HIGH);
      delayMicroseconds(stepper);
      Start();

    }



    Start();
    DataSet();
    //digitalWrite(revPin, LOW);
    delay(cycle_delay);
    Serial.println(select_roti);
    stepper = stepper_speed;
    Serial.println("cycle2");
    Serial.println(stepper);
    Serial.println(L1);
    Serial.println(L2);
    Serial.println(L3);
    Serial.println(Roti);
   

  }
}







void DataSet()
{

 // if(current_up == HIGH)

  
 //Serial.println(sd);
  
  if (last_up == LOW && current_up == HIGH) { //Up button pressed
    select_roti = select_roti + 1;
    lcd.clear();
  }
  else {
  }
  last_up = current_up;

  if (last_down == LOW && current_down == HIGH) { //Up button pressed

   // select_roti = select_roti - 1;
     sub_menu=sub_menu+1;
    lcd.clear();

  }
  else {
  }
  last_down = current_down;
  if (select_roti > 3)
  {
    select_roti = 0;
  }
  if (select_roti < 0)
  {
    select_roti = 0;
  }
  Serial.println(select_roti);
  switch (select_roti) {



    case 0:   


      if (sub_menu > 4)
                    {
                      sub_menu = 0;
                    }
                   if (sub_menu < 0)
                    {
                      sub_menu = 0;
                    }

          switch(sub_menu) {
    
            
                  

                  case 0:

                      stepper_speed = 310;
                      cycle_delay = 500;
                      L1 = 40;
                      L2 = 25;
                      L3 = 500;
                      L4 = 50;
                      L5 = 10;
                      L6 = 25;
                      L7 = 20;
                      L8 = 0;
                      L9 = 125;
                      L10 = 4;
                      L11 = 0;
                      L12 = 100;
                      L13 = 20;
                      L14 = 1000;
                      fix_delay = 2000;
                      rev_delay = 500;
                      Roti = 505;
                      lcd.setCursor(2, 0);
                      lcd.print("Stroke");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(1);
                      lcd.setCursor(11, 1);
                      lcd.print(1);

                      break;



                    case 1:    

                      stepper_speed = 300;
                      cycle_delay = 700;
                      L1 = 40;
                      L2 = 25;
                      L3 = 500;
                      L4 = 50;
                      L5 = 10;
                      L6 = 25;
                      L7 = 20;
                      L8 = 0;
                      L9 = 125;
                      L10 = 4;
                      L11 = 0;
                      L12 = 100;
                      L13 = 20;
                      L14 = 1000;
                      fix_delay = 2000;
                      rev_delay = 500;
                      Roti = 507;
                      lcd.setCursor(2, 0);
                      lcd.print("Stroke");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(1);
                      lcd.setCursor(11, 1);
                      lcd.print(2);

                      break;



                    case 2:   

                      stepper_speed = 290;
                      cycle_delay = 900;
                      L1 = 40;
                      L2 = 25;
                      L3 = 500;
                      L4 = 50;
                      L5 = 10;
                      L6 = 25;
                      L7 = 20;
                      L8 = 0;
                      L9 = 125;
                      L10 = 4;
                      L11 = 0;
                      L12 = 100;
                      L13 = 20;
                      L14 = 1000;
                      fix_delay = 2000;
                      rev_delay = 500;
                      Roti = 509;
                      lcd.setCursor(2, 0);
                      lcd.print("Stroke");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(1);
                      lcd.setCursor(11, 1);
                      lcd.print(3);

                      break;



                    case 3:    

                      stepper_speed = 280;
                      cycle_delay = 1100;
                      L1 = 40;
                      L2 = 25;
                      L3 = 500;
                      L4 = 50;
                      L5 = 10;
                      L6 = 25;
                      L7 = 20;
                      L8 = 0;
                      L9 = 125;
                      L10 = 4;
                      L11 = 0;
                      L12 = 100;
                      L13 = 20;
                      L14 = 1000;
                      fix_delay = 2000;
                      rev_delay = 500;
                      Roti = 511;
                      lcd.setCursor(2, 0);
                      lcd.print("Stroke");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(1);
                      lcd.setCursor(11, 1);
                      lcd.print(4);

                      break;



                    case 4:    

                      stepper_speed = 270;
                      cycle_delay = 1300;
                      L1 = 40;
                      L2 = 25;
                      L3 = 500;
                      L4 = 50;
                      L5 = 10;
                      L6 = 25;
                      L7 = 20;
                      L8 = 0;
                      L9 = 125;
                      L10 = 4;
                      L11 = 0;
                      L12 = 100;
                      L13 = 20;
                      L14 = 1000;
                      fix_delay = 2000;
                      rev_delay = 500;
                      Roti = 513;
                      lcd.setCursor(2, 0);
                      lcd.print("Stroke");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(1);
                      lcd.setCursor(11, 1);
                      lcd.print(5);

                      break;
                      }

                 break;
    



    case 1:  

          if (sub_menu > 4)
                    {
                      sub_menu = 0;
                    }
                   if (sub_menu < 0)
                    {
                      sub_menu = 0;
                    }

          switch(sub_menu) {
    
            
                  

                  case 0:  

                      stepper_speed = 310;
                      cycle_delay = 500;
                      L1 = 40;
                      L2 = 25;
                      L3 = 500;
                      L4 = 50;
                      L5 = 10;
                      L6 = 25;
                      L7 = 20;
                      L8 = 500;
                      L9 = 125;
                      L10 = 4;
                      L11 = 0;
                      L12 = 100;
                      L13 = 20;
                      L14 = 1500;
                      fix_delay = 2000;
                      rev_delay = 100;
                      Roti = 505;
                      lcd.setCursor(2, 0);
                      lcd.print("Stroke");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(2);
                      lcd.setCursor(11, 1);
                      lcd.print(1);

                      break;



                    case 1:    

                      stepper_speed = 300;
                      cycle_delay = 700;
                      L1 = 40;
                      L2 = 25;
                      L3 = 500;
                      L4 = 50;
                      L5 = 10;
                      L6 = 25;
                      L7 = 20;
                      L8 = 500;
                      L9 = 125;
                      L10 = 4;
                      L11 = 0;
                      L12 = 100;
                      L13 = 20;
                      L14 = 1500;
                      fix_delay = 2000;
                      rev_delay = 100;
                      Roti = 507;
                      lcd.setCursor(2, 0);
                      lcd.print("Stroke");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(2);
                      lcd.setCursor(11, 1);
                      lcd.print(2);

                      break;



                    case 2:   

                      stepper_speed = 290;
                      cycle_delay = 900;
                      L1 = 40;
                      L2 = 25;
                      L3 = 500;
                      L4 = 50;
                      L5 = 10;
                      L6 = 25;
                      L7 = 20;
                      L8 = 500;
                      L9 = 125;
                      L10 = 4;
                      L11 = 0;
                      L12 = 100;
                      L13 = 20;
                      L14 = 1500;
                      fix_delay = 2000;
                      rev_delay = 100;
                      Roti = 509;
                      lcd.setCursor(2, 0);
                      lcd.print("Stroke");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(2);
                      lcd.setCursor(11, 1);
                      lcd.print(3);

                      break;



                    case 3:    

                      stepper_speed = 280;
                      cycle_delay = 1100;
                      L1 = 40;
                      L2 = 25;
                      L3 = 500;
                      L4 = 50;
                      L5 = 10;
                      L6 = 25;
                      L7 = 20;
                      L8 = 500;
                      L9 = 125;
                      L10 = 4;
                      L11 = 0;
                      L12 = 100;
                      L13 = 20;
                      L14 = 1500;
                      fix_delay = 2000;
                      rev_delay = 100;
                      Roti = 511;
                      lcd.setCursor(2, 0);
                      lcd.print("Stroke");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(2);
                      lcd.setCursor(11, 1);
                      lcd.print(4);

                      break;



                    case 4:    

                      stepper_speed = 270;
                      cycle_delay = 1300;
                      L1 = 40;
                      L2 = 25;
                      L3 = 500;
                      L4 = 50;
                      L5 = 10;
                      L6 = 25;
                      L7 = 20;
                      L8 = 500;
                      L9 = 125;
                      L10 = 4;
                      L11 = 0;
                      L12 = 100;
                      L13 = 20;
                      L14 = 1500;
                      fix_delay = 2000;
                      rev_delay = 100;
                      Roti = 513;
                      lcd.setCursor(2, 0);
                      lcd.print("Stroke");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(2);
                      lcd.setCursor(11, 1);
                      lcd.print(5);

                      break;
                      }

                 break;



    case 2:  

     if (sub_menu > 4)
                    {
                      sub_menu = 0;
                    }
                   if (sub_menu < 0)
                    {
                      sub_menu = 0;
                    }

          switch(sub_menu) {
    
            
                  

                  case 0:  

                       
                       stepper_speed = 310;
                      cycle_delay = 500;
                      L1 = 40;
                      L2 = 25;
                      L3 = 500;
                      L4 = 50;
                      L5 = 10;
                      L6 = 25;
                      L7 = 20;
                      L8 = 1000;
                      L9 = 125;
                      L10 = 4;
                      L11 = 0;
                      L12 = 100;
                      L13 = 20;
                      L14 = 2000;
                      fix_delay = 1700;
                      rev_delay = 100;
                      Roti = 505;
                      lcd.setCursor(2, 0);
                      lcd.print("Stroke");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(3);
                      lcd.setCursor(11, 1);
                      lcd.print(1);

                      break;



                    case 1:    

                      stepper_speed = 300;
                      cycle_delay = 700;
                      L1 = 40;
                      L2 = 25;
                      L3 = 500;
                      L4 = 50;
                      L5 = 10;
                      L6 = 25;
                      L7 = 20;
                      L8 = 1000;
                      L9 = 125;
                      L10 = 4;
                      L11 = 0;
                      L12 = 100;
                      L13 = 20;
                      L14 = 2000;
                      fix_delay = 1700;
                      rev_delay = 100;
                      Roti = 507;
                      lcd.setCursor(2, 0);
                      lcd.print("Stroke");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(3);
                      lcd.setCursor(11, 1);
                      lcd.print(2);

                      break;



                    case 2:   

                      stepper_speed = 290;
                      cycle_delay = 900;
                      L1 = 40;
                      L2 = 25;
                      L3 = 500;
                      L4 = 50;
                      L5 = 10;
                      L6 = 25;
                      L7 = 20;
                      L8 = 1000;
                      L9 = 125;
                      L10 = 4;
                      L11 = 0;
                      L12 = 100;
                      L13 = 20;
                      L14 = 2000;
                      fix_delay = 1700;
                      rev_delay = 100;
                      Roti = 509;
                      lcd.setCursor(2, 0);
                      lcd.print("Stroke");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(3);
                      lcd.setCursor(11, 1);
                      lcd.print(3);

                      break;



                    case 3:    

                      stepper_speed = 280;
                      cycle_delay = 1100;
                      L1 = 40;
                      L2 = 25;
                      L3 = 500;
                      L4 = 50;
                      L5 = 10;
                      L6 = 25;
                      L7 = 20;
                      L8 = 1000;
                      L9 = 125;
                      L10 = 4;
                      L11 = 0;
                      L12 = 100;
                      L13 = 20;
                      L14 = 2000;
                      fix_delay = 1700;
                      rev_delay = 100;
                      Roti = 511;
                      lcd.setCursor(2, 0);
                      lcd.print("Stroke");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(3);
                      lcd.setCursor(11, 1);
                      lcd.print(4);

                      break;



                    case 4:    

                      stepper_speed = 270;
                      cycle_delay = 1300;
                      L1 = 40;
                      L2 = 25;
                      L3 = 500;
                      L4 = 50;
                      L5 = 10;
                      L6 = 25;
                      L7 = 20;
                      L8 = 1000;
                      L9 = 125;
                      L10 = 4;
                      L11 = 0;
                      L12 = 100;
                      L13 = 20;
                      L14 = 2000;
                      fix_delay = 1700;
                      rev_delay = 100;
                      Roti = 513;
                      lcd.setCursor(2, 0);
                      lcd.print("Stroke");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(3);
                      lcd.setCursor(11, 1);
                      lcd.print(5);

                      break;
                      }

                 break;



    case 3:  

     if (sub_menu > 4)
                    {
                      sub_menu = 0;
                    }
                   if (sub_menu < 0)
                    {
                      sub_menu = 0;
                    }

          switch(sub_menu) {
    
            
                  

                      case 0:  

                       
                       stepper_speed = 310;
                      cycle_delay = 500;
                      L1 = 40;
                      L2 = 25;
                      L3 = 500;
                      L4 = 50;
                      L5 = 10;
                      L6 = 25;
                      L7 = 20;
                      L8 = 2000;
                      L9 = 125;
                      L10 = 4;
                      L11 = 0;
                      L12 = 100;
                      L13 = 20;
                      L14 = 3000;
                      fix_delay = 1000;
                      rev_delay = 100;
                      Roti = 505;
                      lcd.setCursor(2, 0);
                      lcd.print("Stroke");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(4);
                      lcd.setCursor(11, 1);
                      lcd.print(1);

                      break;



                    case 1:    

                      stepper_speed = 300;
                      cycle_delay = 700;
                      L1 = 40;
                      L2 = 25;
                      L3 = 500;
                      L4 = 50;
                      L5 = 10;
                      L6 = 25;
                      L7 = 20;
                      L8 = 2000;
                      L9 = 125;
                      L10 = 4;
                      L11 = 0;
                      L12 = 100;
                      L13 = 20;
                      L14 = 3000;
                      fix_delay = 1000;
                      rev_delay = 100;
                      Roti = 507;
                      lcd.setCursor(2, 0);
                      lcd.print("Stroke");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(4);
                      lcd.setCursor(11, 1);
                      lcd.print(2);

                      break;



                    case 2:   

                      stepper_speed = 290;
                      cycle_delay = 900;
                      L1 = 40;
                      L2 = 25;
                      L3 = 500;
                      L4 = 50;
                      L5 = 10;
                      L6 = 25;
                      L7 = 20;
                      L8 = 2000;
                      L9 = 125;
                      L10 = 4;
                      L11 = 0;
                      L12 = 100;
                      L13 = 20;
                      L14 = 3000;
                      fix_delay = 1000;
                      rev_delay = 100;
                      Roti = 509;
                      lcd.setCursor(2, 0);
                      lcd.print("Stroke");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(4);
                      lcd.setCursor(11, 1);
                      lcd.print(3);

                      break;



                    case 3:    

                      stepper_speed = 280;
                      cycle_delay = 1100;
                      L1 = 40;
                      L2 = 25;
                      L3 = 500;
                      L4 = 50;
                      L5 = 10;
                      L6 = 25;
                      L7 = 20;
                      L8 = 2000;
                      L9 = 125;
                      L10 = 4;
                      L11 = 0;
                      L12 = 100;
                      L13 = 20;
                      L14 = 3000;
                      fix_delay = 1000;
                      rev_delay = 100;
                      Roti = 511;
                      lcd.setCursor(2, 0);
                      lcd.print("Stroke");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(4);
                      lcd.setCursor(11, 1);
                      lcd.print(4);

                      break;



                    case 4:    

                      stepper_speed = 270;
                      cycle_delay = 1300;
                      L1 = 40;
                      L2 = 25;
                      L3 = 500;
                      L4 = 50;
                      L5 = 10;
                      L6 = 25;
                      L7 = 20;
                      L8 = 2000;
                      L9 = 125;
                      L10 = 4;
                      L11 = 0;
                      L12 = 100;
                      L13 = 20;
                      L14 = 3000;
                      fix_delay = 1000;
                      rev_delay = 100;
                      Roti = 513;
                      lcd.setCursor(2, 0);
                      lcd.print("Stroke");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(4);
                      lcd.setCursor(11, 1);
                      lcd.print(5);

                      break;
                      }

                 break;
    

    case 4:  

     if (sub_menu > 4)
                    {
                      sub_menu = 0;
                    }
                   if (sub_menu < 0)
                    {
                      sub_menu = 0;
                    }

          switch(sub_menu) {
    
            
                  

                  case 0:  

                       
                      stepper_speed = 325;
                      cycle_delay = 500;
                      L1 = 0;
                      L2 = 0;
                      L3 = 0;
                      L4 = 0;
                      L5 = 0;
                      L6 = 0;
                      L7 = 40;
                      L8 = 25;
                      L9 = 4000;
                      L10 = 125;
                      L11 = 32;
                      L12 = 1000;
                      fix_delay = 0;
                      Roti = 905;
                      lcd.setCursor(2, 0);
                      lcd.print("Roti");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(900);
                      lcd.setCursor(11, 1);
                      lcd.print(1);

                      break;



                      case 1:    

                        
                      stepper_speed = 315;
                      cycle_delay = 700;
                      L1 = 0;
                      L2 = 0;
                      L3 = 0;
                      L4 = 0;
                      L5 = 0;
                      L6 = 0;
                      L7 = 40;
                      L8 = 25;
                      L9 = 4000;
                      L10 = 125;
                      L11 = 32;
                      L12 = 1000;
                      fix_delay = 0;
                      Roti = 907;
                      lcd.setCursor(2, 0);
                      lcd.print("Roti");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(900);
                      lcd.setCursor(11, 1);
                      lcd.print(2);

                      break;



                      case 2:    

                         
                      stepper_speed = 305;
                      cycle_delay = 900;
                      L1 = 0;
                      L2 = 0;
                      L3 = 0;
                      L4 = 0;
                      L5 = 0;
                      L6 = 0;
                      L7 = 40;
                      L8 = 25;
                      L9 = 4000;
                      L10 = 125;
                      L11 = 32;
                      L12 = 1000;
                      fix_delay = 0;
                      Roti = 909;
                      lcd.setCursor(2, 0);
                      lcd.print("Roti");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(900);
                      lcd.setCursor(11, 1);
                      lcd.print(3);
                      
                      break;



                      case 3:    

                            
                      stepper_speed = 295;
                      cycle_delay = 1100;
                      L1 = 0;
                      L2 = 0;
                      L3 = 0;
                      L4 = 0;
                      L5 = 0;
                      L6 = 0;
                      L7 = 40;
                      L8 = 25;
                      L9 = 4000;
                      L10 = 125;
                      L11 = 32;
                      L12 = 1000;
                      fix_delay = 0;
                      Roti = 911;
                      lcd.setCursor(2, 0);
                      lcd.print("Roti");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(900);
                      lcd.setCursor(11, 1);
                      lcd.print(4);
                      
                      break;


    
                      case 4:    

                              
                      stepper_speed = 285;
                      cycle_delay = 1300;
                      L1 = 0;
                      L2 = 0;
                      L3 = 0;
                      L4 = 0;
                      L5 = 0;
                      L6 = 0;
                      L7 = 40;
                      L8 = 25;
                      L9 = 4000;
                      L10 = 125;
                      L11 = 32;
                      L12 = 1000;
                      fix_delay = 0;
                      Roti = 913;
                      lcd.setCursor(2, 0);
                      lcd.print("Roti");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(900);
                      lcd.setCursor(11, 1);
                      lcd.print(5);

                      break;
                              }

                        break;


    case 5:  

     if (sub_menu > 3)
                    {
                      sub_menu = 0;
                    }
                   if (sub_menu < 0)
                    {
                      sub_menu = 0;
                    }

          switch(sub_menu) {
    
            
                  

                  case 0:  

                       
                      stepper_speed = 303;
                      cycle_delay = 500;
                      L1 = 0;
                      L2 = 0;
                      L3 = 0;
                      L4 = 0;
                      L5 = 0;
                      L6 = 0;
                      L7 = 40;
                      L8 = 25;
                      L9 = 4000;
                      L10 = 125;
                      L11 = 32;
                      L12 = 1000;
                      fix_delay = 0;
                      Roti = 1005;
                      lcd.setCursor(2, 0);
                      lcd.print("Roti");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(1000);
                      lcd.setCursor(11, 1);
                      lcd.print(1);

                      break;



                      case 1:    

                        
                      stepper_speed = 294;
                      cycle_delay = 700;
                      L1 = 0;
                      L2 = 0;
                      L3 = 0;
                      L4 = 0;
                      L5 = 0;
                      L6 = 0;
                      L7 = 40;
                      L8 = 25;
                      L9 = 4000;
                      L10 = 125;
                      L11 = 32;
                      L12 = 1000;
                      fix_delay = 0;
                      Roti = 1007;
                      lcd.setCursor(2, 0);
                      lcd.print("Roti");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(1000);
                      lcd.setCursor(11, 1);
                      lcd.print(2);

                      break;



                      case 2:    

                         
                      stepper_speed = 285;
                      cycle_delay = 900;
                      L1 = 0;
                      L2 = 0;
                      L3 = 0;
                      L4 = 0;
                      L5 = 0;
                      L6 = 0;
                      L7 = 40;
                      L8 = 25;
                      L9 = 4000;
                      L10 = 125;
                      L11 = 32;
                      L12 = 1000;
                      fix_delay = 0;
                      Roti = 1009;
                      lcd.setCursor(2, 0);
                      lcd.print("Roti");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(1000);
                      lcd.setCursor(11, 1);
                      lcd.print(3);
                      
                      break;



                      case 3:    

                            
                      stepper_speed = 276;
                      cycle_delay = 1100;
                      L1 = 0;
                      L2 = 0;
                      L3 = 0;
                      L4 = 0;
                      L5 = 0;
                      L6 = 0;
                      L7 = 40;
                      L8 = 25;
                      L9 = 4000;
                      L10 = 125;
                      L11 = 32;
                      L12 = 1000;
                      fix_delay = 0;
                      Roti = 1011;
                      lcd.setCursor(2, 0);
                      lcd.print("Roti");
                      lcd.setCursor(8, 0);
                      lcd.print("Pressure");
                      lcd.setCursor(2, 1);
                      lcd.print(1000);
                      lcd.setCursor(11, 1);
                      lcd.print(4);
                      
                      break;

                              }

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
