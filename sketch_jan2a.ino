/*  V 1.0.0
  By IVIP */
// В этом скетче используется библиотека от российского ютубера "AlexGyver"

// Подключение библиотеки для индикаторов
#include "GyverTM1637.h"
// Подключение контактов
#define CLK_1 2 // Подключение контактов 1 ого индикатора
#define DIO_1 3 // Подключение контактов 1 ого индикатора
#define BTN_1 4 // Подключение кнопки для переключения времени
#define BTN_2 5 // Подключение кнопки для переключения времени
#define BTN_3 9 // Подключение кнопки для настройки игры
#define BTN_4 8 // Подключение кнопки для переключения режима
#define CLK_2 6 // Подключение контактов 2 ого индикатора
#define DIO_2 7 // Подключение контактов 2 ого индикатора
#define zum 10 // Подключение контактов зуммера
#define BTN_5 11 // Подключение кнопки для общей паузы
 //    Все переменные 
int MIN = 0;
int SEC = 0;
int MIN1 = 0;
int SEC1 = 0;
int finish_min = 0;
int finish_sec = 0;
int chess_moves = 0;
bool bt1 = false;
bool bt2 = false;
bool config_mode = true;
bool notBut = true;
GyverTM1637 disp1(CLK_1, DIO_1);
GyverTM1637 disp2(CLK_2, DIO_2);
unsigned long timer1 = 0;
unsigned long timer2 = 0;
// настройка 
void setup(){
  pinMode(BTN_1, INPUT);
  pinMode(BTN_2, INPUT);
  pinMode(BTN_3, INPUT);
  pinMode(BTN_4, INPUT);
  pinMode(BTN_5, INPUT);
  pinMode(zum, OUTPUT);
  disp1.clear();
  disp1.brightness(7);  
  disp1.clear();        
  disp2.clear();        
  disp2.brightness(7);  
  disp2.clear();
  timer1 = millis();
  timer2 = millis();
}
// Все основные функиции
void loop(){
  clockbtn(); // функция для обработки нажатий всех кнопок
  select_mode(); // функция для настройки часов
  chessClock(); // основная функция для таймера
  reset(); // функция для ресета в конце игры
}
// Функция таймера
void chessClock(){
 if (config_mode == false){
  disp1.displayClock(MIN, SEC);
  disp1.point(1);
  disp2.displayClock(MIN1, SEC1);
  disp2.point(1);
  if ((MIN1 != 0 || SEC1 != 0) && notBut == false){
   if (bt1 == true){
    if (MIN != 0){
     if(millis() - timer1 > 1000){
      timer1 = millis();
      SEC--;
     }
     if (SEC == -1){
      SEC = 59;
      MIN--;
     }
    }
  else {
    if (millis() - timer1 > 1000){
      timer1 = millis();
      SEC--;
    }
    if (MIN == 0 && SEC == 0){
      disp1.displayClock(finish_min, finish_sec);
      notBut = true;
      digitalWrite(zum, HIGH);
      delay(500);
      digitalWrite(zum, LOW);
      clockPoint2();
    }
   }
 }
  else{
  disp1.displayClock(MIN, SEC);
  }
 } 

 if ((MIN != 0 || SEC != 0) && notBut == false){
  if (bt2 == true){
   if(MIN1 != 0){
     if(millis() - timer2 > 1000){
      timer2 = millis();
      SEC1--;
     }
     if (SEC1 == -1){
      SEC1 = 59;
      MIN1--;
     }
  }
  else {
   if (millis() - timer2 > 1000){
    timer2 = millis();
    SEC1--;
   }
    if (MIN1 == 0 && SEC1 == 0){
      disp2.displayClock(finish_min, finish_sec);
      notBut = true;
      digitalWrite(zum, HIGH);
      delay(500);
      digitalWrite(zum, LOW);
      clockPoint1();
    }
  }
 }
 else{
  disp2.displayClock(MIN1, SEC1);
 }
  }
 }
}
// Функции мерцания точки
void clockPoint1(){
  for (int i = 0; i < 2; i++){
  disp1.point(1);
  delay(1000);
  disp1.point(0);
  delay(1000);
  disp1.point(1);
  }
}
void clockPoint2(){
  for (int i = 0; i < 2; i++){
  disp2.point(1);
  delay(1000);
  disp2.point(0);
  delay(1000);
  disp2.point(1);
  }
}
// Функция для всех кнопок
void clockbtn() {
  if (digitalRead(BTN_5) == HIGH){
    bt1 = false;
    bt2 = false;
  }
  if (digitalRead(BTN_4) == HIGH){
      SEC = SEC + 30;
      delay(200);
    }
  if (digitalRead(BTN_3) == HIGH){
    config_mode = false;
    notBut = false;
  }
if (digitalRead(BTN_1) == HIGH){
    bt1 = true;
    bt2 = false;
    chess_moves++;
    delay(200);
  }
  if (digitalRead(BTN_2) == HIGH){
    bt1 = false;
    bt2 = true;
    chess_moves++;
    delay(200);
  }
}
// Функция выбора времени
void select_mode(){
  disp1.displayClock(MIN, SEC);
  disp2.displayClock(MIN1, SEC1);
  if (config_mode == true) {
    if (SEC == 60){
      SEC = 0;
      MIN++;
    }
    if (MIN == 60){
      MIN = 0;
      SEC = 0;
    }
    MIN1 = MIN + 0;
    SEC1 = SEC + 0;
  }
}
// Функция перезагрузки
void reset(){
  if (notBut == true){
    if(digitalRead(BTN_1) == HIGH || digitalRead(BTN_2) == HIGH){
      disp1.clear();
      disp2.clear();
      disp1.point(0);
      disp2.point(0);
      disp1.displayInt(chess_moves);
      disp2.displayInt(chess_moves);
      delay(3000);
      MIN = 0;
      SEC = 0;
      MIN1 = 0;
      SEC1 = 0;
      config_mode = true;
      bt1 = false;
      bt2 = false;
      chess_moves = 0;
      
    }
  }
}
