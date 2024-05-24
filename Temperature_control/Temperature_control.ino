// this example is public domain. enjoy!
// https://learn.adafruit.com/thermocouple/

#include "max6675.h"
#include "ArduPID.h"




ArduPID myController;




double input;
double output;

// Arbitrary setpoint and gains - adjust these as fit for your project:
double setpoint = 33;
double p = 10;
double i = 1;
double d = 0.5;

int thermoDO = PB5;
int thermoCS = PB4;
int thermoCLK = PB3;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  pinMode(PC14, OUTPUT);
 // pinMode(PC15, PWM);
    pinMode(PC13, OUTPUT);
        pinMode(PA0, PWM);
  Serial.begin(9600);

  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  myController.begin(&input, &output, &setpoint, p, i, d);

   myController.reverse();             // Uncomment if controller output is "reversed"
  // myController.setSampleTime(10);      // OPTIONAL - will ensure at least 10ms have past between successful compute() calls
  myController.setOutputLimits(0, 65535);
  myController.setBias(255.0 / 1.0);
  myController.setWindUpLimits(-10, 10); // Groth bounds for the integral term to prevent integral wind-up
  
  myController.start();
  delay(500);
}

void loop() {
  // basic readout test, just print the current temp
  
   Serial.print("C = "); 
   Serial.println(thermocouple.readCelsius());
//   Serial.print("F = ");
//   Serial.println(thermocouple.readFahrenheit());

    input = thermocouple.readCelsius();

  myController.compute();
  myController.debug(&Serial, "myController", PRINT_INPUT    | // Can include or comment out any of these terms to print
                                              PRINT_OUTPUT   | // in the Serial plotter
                                              PRINT_SETPOINT |
                                              PRINT_BIAS     |
                                              PRINT_P        |
                                              PRINT_I        |
                                              PRINT_D);

int ledFadeValue = map(output, 0, 255, 0, 65535);
    pwmWrite(PA0,ledFadeValue);
Serial.print("OUTPUT = "); 
   Serial.println(ledFadeValue);
int timer1=5000;

 //analogWrite(PA0, timer1);
  
 // analogWrite(PC14, 50); // Replace with plant control signal
 
   // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
   delay(300);
}
