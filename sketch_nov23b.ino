#include <GyverTM1637.h>

/* Code by kommunist448,
   with love.
                          */

#define CLK_1 2
#define DIO_1 3
#define BTN_1 4
#define BTN_2 5
#define BTN_3 9
#define BTN_4 8
#define CLK_2 6
#define DIO_2 7
#define zoomPin 10

int MIN = 0;
int SEC = 0;
int MIN1 = 0;
int SEC1 = 0;
int finishMin = 0;
int finishSec = 0;

bool bt1 = false;
bool bt2 = false;
bool configMode = true;

GyverTM1637 disp1(CLK_1, DIO_1);
GyverTM1637 disp2(CLK_2, DIO_2);


void setup() {
  pinMode(BTN_1, INPUT);
  pinMode(BTN_2, INPUT);
  pinMode(BTN_3, INPUT);
  pinMode(BTN_4, INPUT);
  pinMode(zoomPin, OUTPUT);
  disp1.clear();
  disp1.brightness(7);
  disp1.clear(); 
  digitalRead(BTN_1); 
  digitalRead(BTN_2);
  disp2.clear();
  disp2.brightness(7);
  disp2.clear(); 
}

void loop(){  
  clockBtn();
  selectMode();
  chessClock();
}

void chessClock() {
  if (configMode == false){
    disp1.displayClock(MIN, SEC);
    disp1.point(1);
    disp2.displayClock(MIN1, SEC1);
    disp2.point(1);
  if (MIN1 != 0 || SEC1 != 0) {
    if (bt1 == true) {
      if (MIN != 0) {
        SEC--;
        delay(1000);
        if (SEC == -1) {
          SEC = 59;
          MIN--;
    }
  }
  else {
    SEC--;
    delay(1000);
    if (MIN == 0 && SEC == 0) {
      disp1.displayClock(finishMin, finishSec);
      digitalWrite(zoomPin, HIGH);
      delay(500);
      digitalWrite(zoomPin, LOW);
      clockPoint2();
    }
  }
  }
  else {
   disp1.displayClock(MIN, SEC);
  }
 }
 if (MIN != 0 || SEC != 0){
 if (bt2 == true){
  if(MIN1 != 0){
    SEC1--;
    delay(1000);
    if (SEC1 == -1){
      SEC1 = 59;
      MIN1--;
    }
  }
  else {
    SEC1--;
    delay(1000);
    if (MIN1 == 0 && SEC1 == 0){
      disp2.displayClock(finishMin, finishSec);
      digitalWrite(zoomPin, HIGH);
      delay(500);
      digitalWrite(zoomPin, LOW);
      clockPoint2();
    }
  }
 }
 else{
  disp2.displayClock(MIN1, SEC1);
 }
 }
}
}
void clockPoint1(){
  disp1.point(1);
  delay(1000);
  disp1.point(0);
  delay(1000);
  disp1.point(1);
}
void clockPoint2(){
  disp2.point(1);
  delay(1000);
  disp2.point(0);
  delay(1000);
  disp2.point(1);
}
void clockBtn() {
  if (digitalRead(BTN_4) == HIGH){
      SEC = SEC + 30;
      delay(200);
    }
  if (digitalRead(BTN_3) == HIGH){
    configMode = false;
  }
if (digitalRead(BTN_1) == HIGH){
    bt1 = true;
    bt2 = false;
  }
  if (digitalRead(BTN_2) == HIGH){
    bt1 = false;
    bt2 = true;
  }
}
void selectMode() {
  disp1.displayClock(MIN, SEC);
  if (configMode == true) {
    
    if (SEC == 60){
      SEC = 0;
      MIN++;
    }
    MIN1 = MIN;
    SEC1 = SEC;
  }
}
