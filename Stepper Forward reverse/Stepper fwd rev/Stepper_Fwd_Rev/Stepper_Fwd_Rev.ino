#include <LiquidCrystal.h>

#include <EEPROM.h>

const int stepPin = PA8;
const int ledpulse = PC13;
const int M1dirPin = PA9;
const int M2dirPin = PB15;
const int stepPinM2 = PB14;
const int enPin = 8;
const int STOPPER_PIN = PB12;
const int START_PIN = PA7;
int stepper = 296;
int cycle_delay = 0;
int VAL1 = 0;
int VAL2 = 0;
int M2cycle = 0;
int M2Select = 0;
int timedelay = 0;
int timedelay2 = 0;
int stepper_speed = 0;
int M1_stepper_speed = 0;
int stepper_speed_map = 0;
int select_roti = 0;
int select_delay = 0;
int sub_menu = 0;
int L1 = 0;
int L2 = 0;
int L3 = 0;

int acc_stepper = 400;
int acc_M2_stepper=400;
int cap1 = 0;
int cap2 = 0;
int cap3 = 0;
int Motor2 = 0;
int Roti = 0;
int count = 0;
int M1FWD = 0;
int M1REV = 0;
int M2Start = 0;
int startby = 0;
int elapsed = 0;
int saveaddr = 0;
uint Holdaddr = 0x10;
uint pressaddr = 0x12;
uint speedaddr = 0x18;
uint M1speedaddr = 0x20;

bool stopper = 0;

unsigned long previousMillis = 0;
const long interval = 5000;

unsigned long previousMillis2 = 0;
const long M2interval = 60000;

unsigned long previousMillis3 = 0;
unsigned long previousMillis5 = 0;

int Select = 0;
int addz = 0;
int sd = 0;



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


byte Arrow[] = {
  B01000,
  B00100,
  B00010,
  B11111,
  B11111,
  B00010,
  B00100,
  B01000
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // initialize the serial port:
  Serial.println("Ready to go!!!");
  pinMode(stepPin, OUTPUT);
  pinMode(stepPinM2, OUTPUT);
  pinMode(ledpulse, OUTPUT);
  pinMode(M1dirPin, OUTPUT);
  pinMode(M2dirPin, OUTPUT);
  pinMode(STOPPER_PIN, INPUT_PULLUP);
  pinMode(START_PIN, INPUT_PULLUP);

  digitalWrite(enPin, LOW);



  //  Status = EEPROM.read(saveaddr, &SAVEDATA);
  //select_roti = EEPROM.read(saveaddr);

  uint16 Status;
  uint16 Status2;
  uint16 Status3;
  uint16 Status4;
  uint16 HoldDATA;
  uint16 PressDATA;
  uint16 SpeedDATA;
  uint16 M1SpeedDATA;
  Status = EEPROM.read(Holdaddr, &HoldDATA);
  Status2 = EEPROM.read(pressaddr, &PressDATA);
  Status3 = EEPROM.read(speedaddr, &SpeedDATA);
  Status4 = EEPROM.read(M1speedaddr, &M1SpeedDATA);
  M2cycle = HoldDATA;
  timedelay = PressDATA;
  stepper_speed = SpeedDATA;
  M1_stepper_speed = M1SpeedDATA;


  //select_roti = SAVEDATA;

  lcd.begin(16, 2);
  lcd.createChar(1, Arrow);

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







  digitalWrite(ledpulse, HIGH);

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    uint16 Status;
    uint16 Status2;
    uint16 Status3;
    uint16 Status4;
    Status = EEPROM.update(Holdaddr, M2cycle);
    Status2 = EEPROM.update(pressaddr, timedelay);
    Status3 = EEPROM.update(speedaddr, stepper_speed);
    Status4 = EEPROM.update(M1speedaddr, M1_stepper_speed);
    //digitalWrite(ledpulse, LOW);
  }

  else {
  }



  unsigned long currentMillis5 = millis();
  if (currentMillis5 - previousMillis5 >= 300) {
    previousMillis5 = currentMillis5;

    lcd.clear();
  }


  if (VAL2 == 0) {
    lcd.setCursor(1, 0);
    lcd.print("Motor 1:");
    lcd.setCursor(1, 1);
    lcd.print("Motor 2:");
    lcd.setCursor(0, 0);
    lcd.write(byte(1));
  }



  if (VAL2 == 1) {
    lcd.setCursor(1, 0);
    lcd.print("Motor 1:");
    lcd.setCursor(1, 1);
    lcd.print("Motor 2:");
    lcd.setCursor(0, 1);
    lcd.write(byte(1));
    lcd.setCursor(15, 0);
    lcd.print(VAL2);

  }
  if (VAL2 == 2) {
    lcd.setCursor(1, 0);
    lcd.print("Motor 1:");
    lcd.setCursor(1, 1);
    lcd.print("Motor 2:");

  }
  if (VAL2 == 3) {
    lcd.setCursor(1, 0);
    lcd.print("Motor 1:");
    lcd.setCursor(1, 1);
    lcd.print("Motor 2:");
    lcd.setCursor(15, 0);
    lcd.print(VAL2);
    lcd.setCursor(0, 0);
    lcd.write(byte(1));

  }
  if (VAL2 == 4) {
    lcd.setCursor(1, 0);
    lcd.print("Motor 1:");
    lcd.setCursor(1, 1);
    lcd.print("Motor 2:");
    lcd.setCursor(15, 0);
    lcd.print(VAL2);
  }
  if (VAL2 == 5) {
    lcd.setCursor(1, 0);
    lcd.print("Motor 1:");
    lcd.setCursor(1, 1);
    lcd.print("Motor 2:");
    lcd.setCursor(15, 0);
    lcd.print(VAL2);
    lcd.setCursor(0, 1);
    lcd.write(byte(1));
  }

  stepper_speed_map = map(stepper_speed, 0, 100, 500, 100);

  Start();
  cycle();
  Motor1Forward();

  Motor1REV();
  Motor2para();
  Motor2Start();




  //stepper = stepper_speed;
  startcycle();



  // if (digitalRead(START_PIN) == HIGH)
  //  {
  //    VAL2 = 0;
  //    VAL1 = 0;
  //  }
  //

}


void startcycle()
{
  switch (VAL2)
  {


    case 0:

      if (last_up == LOW && current_up == HIGH)
      {


        M1FWD = M1FWD + 1;
      }
      else {
      }
      last_up = current_up;

      if (M1FWD > 1)
      {
        M1FWD = 0;

      }

      // Serial.print("M1 forward:");
      // Serial.println(M1FWD);

      if (M1FWD == 1)
      {

        lcd.setCursor(10, 0);
        lcd.print("FWD");


        for (int x = 0; x < 40; x++)

        {

          for (int y = 0; y < 25; y++)
          {

            digitalWrite(stepPin, HIGH); digitalWrite(ledpulse, LOW);
            delayMicroseconds(acc_stepper);
            digitalWrite(stepPin, LOW); digitalWrite(ledpulse, HIGH);
            delayMicroseconds(acc_stepper);
          }

          acc_stepper = acc_stepper - 5;

          if (acc_stepper < M1_stepper_speed)
          {
            acc_stepper = M1_stepper_speed;
          }

          //Serial.print("stepper pulse:");
          //Serial.println(acc_stepper);
          Start();


        }

        for (int x = 0; x < 10000; x++)

        { //previously 800

          digitalWrite(stepPin, HIGH); digitalWrite(ledpulse, LOW);
          delayMicroseconds(M1_stepper_speed);
          digitalWrite(stepPin, LOW); digitalWrite(ledpulse, HIGH);
          delayMicroseconds(M1_stepper_speed);
          // Serial.println(x);




        }
        //delay(1000);
        M1FWD = M1FWD + 1;
        acc_stepper = 400;

      }



      Motor1REV();


      if (M1REV == 1)
      {
        lcd.setCursor(10, 0);
        lcd.print("REV");
        digitalWrite(M1dirPin, HIGH);

        for (int x = 0; x < 40; x++)

        {

          for (int y = 0; y < 25; y++)
          {

            digitalWrite(stepPin, HIGH); digitalWrite(ledpulse, LOW);
            delayMicroseconds(acc_stepper);
            digitalWrite(stepPin, LOW); digitalWrite(ledpulse, HIGH);
            delayMicroseconds(acc_stepper);
          }

          acc_stepper = acc_stepper - 5;

          if (acc_stepper < M1_stepper_speed)
          {
            acc_stepper = M1_stepper_speed;
          }

          //Serial.print("stepper pulse:");
          //Serial.println(acc_stepper);
          Start();


        }

        for (int x = 0; x < 11000; x++)

        {

          digitalWrite(stepPin, HIGH); digitalWrite(ledpulse, LOW);
          delayMicroseconds(M1_stepper_speed);
          digitalWrite(stepPin, LOW); digitalWrite(ledpulse, HIGH);
          delayMicroseconds(M1_stepper_speed);

        }
        digitalWrite(M1dirPin, LOW);
        M1REV = M1REV + 1;

      }


      M2Start = 0;
      break;



    case 1:





      if (last_up == LOW && current_up == HIGH) \

      {
        M2Start = M2Start + 1;


      }

      else {
      }
      last_up = current_up;

      if (M2Start > 1)
      {
        M2Start = 0;

      }
      M1REV = 0;
      M1FWD = 0;
      if (M2Start == 1)
      {

        timedelay2 = timedelay * 1000;


        lcd.setCursor(10, 1);
        lcd.print("FWD");

        for (int x = 0; x < M2cycle; x++)
        {
          while (Motor2 == 0)
          {



            if (cap2 == 0) //writes the millis delay time once
            {
              for (int x = 0; x < 80; x++)

              {

                for (int y = 0; y < 25; y++)
                {

                  digitalWrite(stepPinM2, HIGH); digitalWrite(ledpulse, LOW);
                  delayMicroseconds(acc_M2_stepper);
                  digitalWrite(stepPinM2, LOW); digitalWrite(ledpulse, HIGH);
                  delayMicroseconds(acc_M2_stepper);
                }

                acc_M2_stepper = acc_M2_stepper - 5;

                if (acc_M2_stepper < stepper_speed_map)
                {
                  acc_M2_stepper = stepper_speed_map;
                }

                 Serial.print("M2 stepper pulse:");
          Serial.println(acc_M2_stepper);

              }

              previousMillis3 = millis();//  stepper_speed_map
              cap2 = 1; //
            }


            digitalWrite(stepPinM2, HIGH); digitalWrite(ledpulse, LOW);
            delayMicroseconds(stepper_speed_map);
            digitalWrite(stepPinM2, LOW); digitalWrite(ledpulse, HIGH);
            delayMicroseconds(stepper_speed_map);

            unsigned long currentMillis3 = millis();

            if (currentMillis3 - previousMillis3 >= timedelay2)
            {
              Motor2 = Motor2 + 1;
              cap2 = 0;
            }

          }
          acc_M2_stepper=400;
          delay(2000);
          lcd.setCursor(10, 1);
          lcd.print("REV");


          while (Motor2 == 1)
          {

            timedelay2 = timedelay * 1000;

            if (cap2 == 0) //writes the millis delay time once
            {

               digitalWrite(M2dirPin, HIGH);

               for (int x = 0; x < 80; x++)

              {

                for (int y = 0; y < 25; y++)
                {

                  digitalWrite(stepPinM2, HIGH); digitalWrite(ledpulse, LOW);
                  delayMicroseconds(acc_M2_stepper);
                  digitalWrite(stepPinM2, LOW); digitalWrite(ledpulse, HIGH);
                  delayMicroseconds(acc_M2_stepper);
                }

                acc_M2_stepper = acc_M2_stepper - 5;

                if (acc_M2_stepper < stepper_speed_map)
                {
                  acc_M2_stepper = stepper_speed_map;
                }

                 Serial.print("M2 stepper pulse:");
          Serial.println(acc_M2_stepper);

              }


              
              previousMillis3 = millis();//
              cap2 = 1; //
             
            }

            digitalWrite(stepPinM2, HIGH); digitalWrite(ledpulse, LOW);
            delayMicroseconds(stepper_speed_map);
            digitalWrite(stepPinM2, LOW); digitalWrite(ledpulse, HIGH);
            delayMicroseconds(stepper_speed_map);

            unsigned long currentMillis3 = millis();

            if (currentMillis3 - previousMillis3 >= timedelay2)
            {


              digitalWrite(M2dirPin, LOW);
              //

              Motor2 = Motor2 - 1;
              cap2 = 0;
              count = count + 1;

              lcd.setCursor(14, 1);
              lcd.print(count);

            }



          }
          acc_M2_stepper=400;
          delay(1000);
          lcd.setCursor(10, 1);
          lcd.print("FWD");


        }
        //VAL2 = 0;
        count = 0;
        M2Start = 0;
      }



      break;






  }




}





void DataSet()
{

  if (last_sel == LOW && current_sel == HIGH) { //Up button pressed
    VAL2 = VAL2 + 1;
    lcd.setCursor(0, 0);
    lcd.print(VAL2);

  }
  else {
  }
  last_sel = current_sel;
  if (VAL2 > 14)
  {
    VAL2 = 9;

  }



  Serial.println(VAL2);
  switch (VAL2) {






    case 9:

      // lcd.clear();




      lcd.setCursor(1, 0);
      lcd.print("Set Parameter");
      break;


    case 10:

      // lcd.clear();
      lcd.setCursor(0, 1);
      lcd.write(byte(1));



      lcd.setCursor(1, 0);
      lcd.print("Number of cycle");

      if (current_up == HIGH && VAL2 == 10)
      {

        unsigned long currentMillis2 = millis();

        if (currentMillis2 - previousMillis2 >= 300)
        {



          M2cycle = M2cycle + 1;
          previousMillis2 = currentMillis2;


        }
      }


      if (current_down == HIGH && VAL2 == 10)
      {

        unsigned long currentMillis2 = millis();

        if (currentMillis2 - previousMillis2 >= 300)
        {



          M2cycle = M2cycle - 1;
          previousMillis2 = currentMillis2;


        }
      }
      if (M2cycle < 1)
      {
        M2cycle = 0;
      }
      lcd.setCursor(5, 1);
      lcd.print(M2cycle);
      lcd.setCursor(10, 1);
      lcd.print("");








      break;



    case 11:






      //lcd.clear();


      lcd.setCursor(0, 1);
      lcd.write(byte(1));



      lcd.setCursor(1, 0);
      lcd.print("Fwd Rev Time");


      if (current_up == HIGH && VAL2 == 11)
      {

        unsigned long currentMillis2 = millis();

        if (currentMillis2 - previousMillis2 >= 300)
        {



          timedelay = timedelay + 1;
          previousMillis2 = currentMillis2;

        }
      }


      if (current_down == HIGH && VAL2 == 11)
      {

        unsigned long currentMillis2 = millis();

        if (currentMillis2 - previousMillis2 >= 300)
        {



          timedelay = timedelay - 1;
          previousMillis2 = currentMillis2;

        }
      }
      if (timedelay < 1)
      {
        timedelay = 0;
      }
      lcd.setCursor(5, 1);
      lcd.print(timedelay);
      lcd.setCursor(10, 1);
      lcd.print("Sec");



      break;



    case 12:

      lcd.setCursor(0, 1);
      lcd.write(byte(1));



      lcd.setCursor(1, 0);
      lcd.print("Motor:2 Speed");


      if (current_up == HIGH && VAL2 == 12)
      {

        unsigned long currentMillis2 = millis();

        if (currentMillis2 - previousMillis2 >= 100)
        {



          stepper_speed = stepper_speed + 1;
          previousMillis2 = currentMillis2;

        }
      }


      if (current_down == HIGH && VAL2 == 12)
      {

        unsigned long currentMillis2 = millis();

        if (currentMillis2 - previousMillis2 >= 100)
        {



          stepper_speed = stepper_speed - 1;
          previousMillis2 = currentMillis2;

        }
      }
      if (stepper_speed < 1)
      {
        stepper_speed = 0;
      }
      if (stepper_speed > 100)
      {
        stepper_speed = 100;
      }
      lcd.setCursor(5, 1);
      lcd.print(stepper_speed);
      lcd.setCursor(10, 1);
      lcd.print(stepper_speed_map);


      break;


    case 14:




      lcd.setCursor(1, 0);
      lcd.print("Press Down BTN");
      lcd.setCursor(1, 1);
      lcd.print("3 sec To Exit");




      if (current_down == HIGH && VAL2 == 14)
      {


        if (cap3 == 0) //writes the fan millis delay time once
        {
          previousMillis2 = millis();// fixed fan delay time
          cap3 = 1; //disable the capture of the initial time used to delay the fan
        }

        unsigned long currentMillis2 = millis();

        if (currentMillis2 - previousMillis2 >= 3000)
        {
          VAL2 = 1;
          startby = 0;

        }
      }


      break;




    case 13:

      lcd.setCursor(0, 1);
      lcd.write(byte(1));



      lcd.setCursor(1, 0);
      lcd.print("Motor:1 Speed");


      if (current_up == HIGH && VAL2 == 13)
      {

        unsigned long currentMillis2 = millis();

        if (currentMillis2 - previousMillis2 >= 100)
        {



          M1_stepper_speed = M1_stepper_speed + 1;
          previousMillis2 = currentMillis2;

        }
      }


      if (current_down == HIGH && VAL2 == 13)
      {

        unsigned long currentMillis2 = millis();

        if (currentMillis2 - previousMillis2 >= 100)
        {



          M1_stepper_speed = M1_stepper_speed - 1;
          previousMillis2 = currentMillis2;

        }
      }
      if (M1_stepper_speed < 1)
      {
        M1_stepper_speed = 0;
      }

      lcd.setCursor(5, 1);
      lcd.print(M1_stepper_speed);



      break;





  }


}





void Start()
{
  if (last_sel == LOW && current_sel == HIGH) { //Up button pressed
    VAL2 = VAL2 + 1;
    //    lcd.setCursor(0, 0);
    //    lcd.print(VAL2);

  }
  else {
  }
  last_sel = current_sel;

  if (VAL2 > 1 && startby == 0)
  {
    VAL2 = 0;
    VAL1 = 0;
  }
}


void Motor1Forward()
{

}


void Motor1REV()
{
  if (last_down == LOW && current_down == HIGH)

  {
    M1REV = M1REV + 1;
    //digitalWrite(ledpulse, HIGH);


  }
  else {
  }
  last_down = current_down;

  if (M1REV > 1)
  {
    M1REV = 0;

  }
  Serial.print("M1 Reverse:");
  Serial.println(M1REV);



}


void Motor2para()
{
  if (last_down == LOW && current_down == HIGH) { //Up button pressed
    M2Select = M2Select + 1;
    //    lcd.setCursor(0, 0);
    //    lcd.print(VAL2);

  }
  else {
  }
  last_down = current_down;

  if (M2Select > 1)
  {
    M2Select = 0;

  }
}


void Motor2Start()
{

}


void cycle()
{
  if (current_down == HIGH && VAL2 == 1)
  {


    if (cap1 == 0) //writes the fan millis delay time once
    {
      previousMillis2 = millis();// fixed fan delay time
      cap1 = 1; //disable the capture of the initial time used to delay the fan
    }

    unsigned long currentMillis2 = millis();

    if (currentMillis2 - previousMillis2 >= 3000)
    {




      startby = 1;
      VAL2 = 9;
      cap1 = 0;
    }
    else
    {
    }
  }

}
