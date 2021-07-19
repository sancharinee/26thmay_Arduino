#include<LiquidCrystal.h>
LiquidCrystal lcd(13,12,11,10,1,0);
const char IRDownPin=2,IRUpPin=3;
byte carCount=0;

void setup(){
  pinMode(IRDownPin,INPUT);
  pinMode(IRUpPin,INPUT);
  lcd.begin(16,2);
}

void carEntering(){
  lcd.setCursor(0,0);
  lcd.print("Car is entering");
}

void carExiting(){
  lcd.setCursor(0,0);
  lcd.print("Car is exiting");
}

void carEntered(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Car entered");
}

void carExited(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Car exited");
}

void displayCarCount(){
  lcd.setCursor(0,0);
  lcd.print("Car count = ");
  lcd.print(carCount);
}

void loop(){
  displayCarCount();
  if(digitalRead(IRDownPin)){
    lcd.clear();
    while(digitalRead(IRUpPin) or digitalRead(IRDownPin)) carEntering();
    carEntered();
    delay(500);
    carCount++;
    lcd.clear();
    displayCarCount();
  }
  if(digitalRead(IRUpPin)){
    lcd.clear();
    while(digitalRead(IRUpPin) or digitalRead(IRDownPin)) carExiting();
    carExited();
    delay(500);
    carCount--;
    lcd.clear();
    displayCarCount();
  }
}
