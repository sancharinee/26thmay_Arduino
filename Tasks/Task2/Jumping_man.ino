#include<LiquidCrystal.h>
LiquidCrystal lcd(13,12,11,10,9,8);
volatile int row=1;
int score=0;
byte randNum=1,len=1;
bool gameOver=0;

byte man[8]={
  0b01110,
  0b01110,
  0b00100,
  0b11111,
  0b00100,
  0b00100,
  0b01010,
  0b10001
};

byte obstacle[8]={
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b00000,
  0b00000,
};

void row1_clear(){
  lcd.clear();
  row=!row;
  changeRow();
}

void game_over(){
  gameOver=1;
  lcd.clear();
  score--;
  update_score();
  while(row){
    lcd.setCursor(3,0);
    lcd.print("GAME OVER");
  }
  score=0;
  lcd.clear();
}

void update_score(){
  if(row==1 and !gameOver)score++;
  if(score/10==0){
    lcd.setCursor(13,0);
    lcd.print("00");
    lcd.print(score);
  }
  else if((score/10)>=1 and (score/10)<=9){
    lcd.setCursor(13,0);
    lcd.print("0");
    lcd.print(score);
  }
  else if((score/10)>=10 and (score/10)<=99){
    lcd.setCursor(13,0);
    lcd.print(score);
  }
}

void create_and_move_obstacle(){
  len=random(2,6);
  byte index=15,j=0,i=0;
  for(int j=index;j>=0;j--){
    for(int i=j;i>=j-len+1;i--){
      lcd.setCursor(i,1);
      lcd.write(2);
      if(row==1 and 5>=j-len+1 and 5<=j) {
        game_over(); 
        break;
      }
    }
    if(gameOver){
      gameOver=0;
      row=1;
      changeRow();
      break;
    }
    delay(150);
    row1_clear();
    update_score();
  }  
}

void setup() {
  lcd.createChar(1,man);
  lcd.createChar(2,obstacle);
  lcd.begin(16,2);
  attachInterrupt(digitalPinToInterrupt(2),changeRow,RISING);
  randomSeed(analogRead(0));
}

void changeRow(){
  row=!row;
  if(!gameOver){
    if(row==1){
      lcd.setCursor(5,1);
      lcd.write(1);
      lcd.setCursor(5,0); 
      lcd.print(" ");
    }
    if(row==0){
      lcd.setCursor(5,0);
      lcd.write(1);
      lcd.setCursor(5,1); 
      lcd.print(" ");
    }
  }
}

void loop(){
  create_and_move_obstacle();
}
