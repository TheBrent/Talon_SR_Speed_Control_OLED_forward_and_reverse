#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

Servo leftPWM;
Servo rightPWM;

int calPot = 6;
int calPotVal;
int rfPot = 0;
int rfPotVal;
int rrPot = 1;
int rrPotVal;
int lfPot = 2;
int lfPotVal;
int lrPot = 3;
int lrPotVal;

int rfPin = 5;
int rrPin = 4;
int lfPin = 3;
int lrPin = 2;

int rf;
int rr;
int lf;
int lr;

int calPWMVal;
int rPWMSpeed;
int lPWMSpeed;

float rfSpeed;
float rrSpeed;
float lfSpeed;
float lrSpeed;

void setup() {
  leftPWM.attach(11);
  rightPWM.attach(10);
  pinMode(rfPin, INPUT_PULLUP);
  pinMode(rrPin, INPUT_PULLUP);
  pinMode(lfPin, INPUT_PULLUP);
  pinMode(lrPin, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

}

void loop() {
  calPotVal = analogRead(calPot);
  rfPotVal = analogRead(rfPot);
  rrPotVal = analogRead(rrPot);
  lfPotVal = analogRead(lfPot);
  lrPotVal = analogRead(lrPot);
  rf = digitalRead(rfPin);
  rr = digitalRead(rrPin);
  lf = digitalRead(lfPin);
  lr = digitalRead(lrPin);

  calPWMVal = map(calPotVal, 0, 1023, 70, 110);
  rfSpeed = rfPotVal/1023.00;
  rrSpeed = -rrPotVal/1023.00;
  lfSpeed = lfPotVal/1023.00;
  lrSpeed = -lrPotVal/1023.00;

  if(rf==rr) {
    rPWMSpeed = calPWMVal;
  } else if(rf==0) {
    rPWMSpeed = map(90*rfSpeed, 0, 90, calPWMVal, 180);
  } else if(rr==0) {
    rPWMSpeed = map(90*rrSpeed, -90, 0, 0, calPWMVal); 
  }

  if(lf==lr) {
    lPWMSpeed = calPWMVal;
  } else if(lf==0) {
    lPWMSpeed = map(90*lfSpeed, 0, 90, calPWMVal, 180);
  } else if(lr==0) {
    lPWMSpeed = map(90*lrSpeed, -90, 0, 0, calPWMVal);
  }

  rightPWM.write(rPWMSpeed);
  leftPWM.write(lPWMSpeed);
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("cal:");
  display.println(calPWMVal);
  display.print("lrs:");
  display.print(lrSpeed);
  display.print(" lfs:");
  display.println(lfSpeed);
  display.print("rrs:");
  display.print(rrSpeed);
  display.print(" rfs:");
  display.println(rfSpeed);
  display.print("lpwm:");
  display.print(lPWMSpeed);
  display.print(" rpwm:");
  display.print(rPWMSpeed);
  display.display();

  delayMicroseconds(1500);
}
