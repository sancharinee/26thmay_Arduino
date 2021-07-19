#include<Keypad.h>
#include<LiquidCrystal.h>

LiquidCrystal lcd(13,12,11,10,9,8);

String notice="";

char keys[4][3]={
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
char rows[4]={3,2,1,0};
char columns[5]={4,5,6};

Keypad keypad=Keypad(makeKeymap(keys),rows,columns,4,3);

void setup(){
  lcd.begin(16,2);
}

void scrollNotice(){
  unsigned char len=notice.length();
  lcd.setCursor(0,1);
  lcd.print(notice);
  delay(800);
  for(int i=-1;i>=-1*(len-16);i--){
    lcd.setCursor(i,1);
    lcd.print(notice);
    delay(200);
  }
  delay(800);
}

void notice1(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("NOTICE 1");
  notice="There will be no class on Monday.";
  scrollNotice();
}

void notice2(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("NOTICE 2");
  notice="There will be no class on Tuesday.";
  scrollNotice();
}

void notice3(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("NOTICE 3");
  notice="There will be no class on Wednesday.";
  scrollNotice();
}

void notice4(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("NOTICE 4");
  notice="There will be no class on Thursday.";
  scrollNotice();
}

void notice5(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("NOTICE 5");
  notice="There will be no class on Friday.";
  scrollNotice();
}

void notice6(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("NOTICE 6");
  notice="There will be no class on Saturday.";
  scrollNotice();
}

void invalidInput(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Invalid entry");
  lcd.setCursor(0,1);
  lcd.print("Press 1 to 6 key");
  delay(800);
}

void displayNotice(){
  char k=keypad.waitForKey();
  if(k=='1') notice1();
  else if(k=='2') notice2();
  else if(k=='3') notice3();
  else if(k=='4') notice4();
  else if(k=='5') notice5();
  else if(k=='6') notice6();
  else invalidInput();
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Digital Notice");
  lcd.setCursor(0,1);
  lcd.print("Press 1 to 6 key");
  displayNotice();
}
