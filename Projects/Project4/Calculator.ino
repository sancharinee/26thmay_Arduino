#include<Keypad.h>
#include<LiquidCrystal.h>
#include<Wire.h>
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
char keys[4][4] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'c','0','=','+'},
};

byte row[4] = {9, 8, 7, 6};
byte col[4] = {5, 4, 3, 2};

Keypad mykeypad =Keypad(makeKeymap(keys), row, col, 4, 4);

boolean firstNumState = true;
String firstNum = "";
String secondNum = "";
float result = 0.0;
char calc = ' ';

void setup() {
  lcd.begin(16,2);
}

void loop() {
  char k = mykeypad.getKey();
  if(k != NO_KEY && (k =='1' || k =='2' || k =='3' || k =='4' || k =='5' || k =='6' || k =='7' || k =='8' || k =='9' || k =='0'))
  {
    if(firstNumState == true){
      firstNum = firstNum + k;
      lcd.print(k);
    }
    else{
      secondNum = secondNum + k;
      lcd.print(k);
    }
  }
  if(k != NO_KEY && (k =='+' || k =='-' || k =='*' || k =='/')){
    if(firstNumState == true){
      calc=k;
      firstNumState = false;
      lcd.print(calc);
    }
  }
  if(k != NO_KEY && k == '='){
      if(calc == '+'){
        result = firstNum.toFloat() + secondNum.toFloat();
    }
    if(calc == '-'){
      result = firstNum.toFloat() - secondNum.toFloat();
    }
    if(calc == '*'){
      result = firstNum.toFloat() * secondNum.toFloat();
    }
    if(calc == '/'){
      result = firstNum.toFloat() / secondNum.toFloat();
    }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(firstNum);
  lcd.print(calc);
  lcd.print(secondNum);
  lcd.setCursor(0, 1);
  lcd.print("=");
  lcd.print(result);
  firstNumState = true;
}
if(k != NO_KEY && k == 'c'){
  lcd.clear();
  firstNum = "";
  secondNum = "";
  result = 0;
}
}
