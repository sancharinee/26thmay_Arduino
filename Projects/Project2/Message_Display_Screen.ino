#include<LiquidCrystal.h> //Library for LCD
//LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);// LCD pins at which it is attached to the Arduino

void setup() //method used to run the source for the one time onlys
{
  lcd.begin(16, 2);//LCD order i.e. 16 columns & 2 rows
  lcd.print("Project2");//prints on LCD
  //lcd.setCursor(row,col);
  lcd.setCursor(0,1);//setting cursor on LCD
  lcd.print("Messaage Display Screen");//prints on LCD
  delay(1000);//delay of 1 sec
}
void loop() //method to run the source code repeatedly 
{
 lcd.noDisplay();//turn off the display of LCD
 delay(250);//delay to 0.25 seconds
 lcd.display();//turning on the LCD display
 delay(250); //delay of 0.25 seconds again
}
