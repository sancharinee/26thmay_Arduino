#include<LiquidCrystal.h>
LiquidCrystal lcd(13,12,11,10,9,8);
const byte buzzer=7,menu=3,plus=1,minus=2;
volatile bool in_menu=1;
byte sec=0,minutes=0,hours=0;
byte alarm_sec=0,alarm_minutes=0,alarm_hours=0;
unsigned long millis_out=0;
unsigned long millis_out_delay=0;

void setup() {
  pinMode(buzzer,OUTPUT);
  pinMode(menu,INPUT);
  pinMode(plus,INPUT);
  pinMode(minus,INPUT);
  lcd.begin(16,2);
  attachInterrupt(digitalPinToInterrupt(menu),menu_status,RISING);
}

void millis_delay(int sec){
  millis_out_delay=millis()/1000;
  while(1){
    if(millis_out_delay+sec==(millis()/1000)) break;
  }
}

void buzzer_settings(int duration,int duty_cycle,int time_period){
  int counter=0;
  while(counter<=duration){
    if(in_menu) {
      in_menu=!in_menu;
      break;
    }
    tone(buzzer,1000);
    millis_delay((time_period*duty_cycle)/100);
    noTone(buzzer);
    millis_delay(time_period*(100-duty_cycle)/100); 
    counter+=time_period;
  }
}

void alarm_buzzer(){
  if(alarm_hours==hours and alarm_minutes==minutes and alarm_sec==sec and millis_out>1000){
    lcd.setCursor(0,0);
    lcd.print("Alarm ON");
    buzzer_settings(60,50,2);
  }  
}

void menu_status(){
  in_menu=!in_menu;
}
void clock_display(){
  if(!in_menu){
    lcd.setCursor(0,0);
    if(millis()>=millis_out){
      sec=millis()/1000;
      sec=sec%60;
      if(sec==0 and millis_out!=0){
        sec=0;
        minutes++;
        lcd.clear();
        if(minutes>=60){
          minutes=0;
          hours++;
          lcd.clear();
          if(hours>=24){
            hours=0;
            lcd.clear();
          }
        }
      }
    if(hours<=9){
      lcd.print("0"); 
    }
    lcd.print(hours);
    lcd.print(":");
    if(minutes<=9){
      lcd.print("0");
    }
    lcd.print(minutes);
    lcd.print(":");
    if(sec<=9){
      lcd.print("0");
    }
    lcd.print(sec);
    millis_out+=1000;
    delay(500); 
    alarm_buzzer();
    }
  }     
}

void update_menu_display(){
  lcd.setCursor(0,0);
  if(alarm_hours<=9){
      lcd.print("0"); 
    }
    lcd.print(alarm_hours);
    lcd.print(":");
    if(alarm_minutes<=9){
      lcd.print("0");
    }
    lcd.print(alarm_minutes);
    lcd.print(":");
    if(alarm_sec<=9){
      lcd.print("0");
    }
    lcd.print(alarm_sec);
}


void menu_display(){
  if(in_menu){
    alarm_sec=0,alarm_minutes=0,alarm_hours=0;
    update_menu_display();
    for(int i=1;i<=7;i+=3){
      lcd.setCursor(i,1);
      lcd.print("=");
      if(i==1){
        while(in_menu){
        if(digitalRead(plus)) {
          alarm_hours++;
          if(alarm_hours>=24) alarm_hours=0;
        }
        delay(125);
        if(digitalRead(minus)){
          alarm_hours--;
          if(alarm_hours>200) alarm_hours=23;
        }
        delay(125);
        lcd.setCursor(0,0);
        update_menu_display();
        }
        lcd.setCursor(i,1);
        lcd.print(" ");
        continue;
      }
      if(i==4){
        while(!in_menu){
        if(digitalRead(plus)) {
          alarm_minutes++;
          if(alarm_minutes>=60) alarm_minutes=0;
        }
        delay(125);
        if(digitalRead(minus)){
          alarm_minutes--;
          if(alarm_minutes>200) alarm_minutes=59;
        }
        delay(125);
        lcd.setCursor(0,0);
        update_menu_display();
        }
        lcd.setCursor(i,1);
        lcd.print(" ");
        continue;
      }
      if(i==7){
        while(in_menu){
        if(digitalRead(plus)) {
          alarm_sec++;
          if(alarm_sec>=60) alarm_sec=0;
        }
        delay(125);
        if(digitalRead(minus)){
          alarm_sec--;
          if(alarm_sec>200) alarm_sec=59;
        }
        delay(125);
        lcd.setCursor(0,0);
        update_menu_display();
        }
        lcd.setCursor(i,1);
        lcd.print(" ");
        continue;
        in_menu=0;
      }   
  }
  }
}

void loop() {
  clock_display();
  menu_display(); 
}  
