const char tempSensor1Pin=A1,tempSensor2Pin=A0,heaterPin=7,fanPin=5,coolerPin=3;
const char maxSpeed=255,medSpeed=170,lowSpeed=85;
int temp=0;

void setup(){
  pinMode(fanPin,OUTPUT);
  pinMode(coolerPin,OUTPUT);
  pinMode(heaterPin,OUTPUT);
  Serial.begin(9600);
}

//taking only integer value of temp.
int getTemp(){ 
  int tempSensor1Val=analogRead(tempSensor1Pin);
  int tempSensor2Val=analogRead(tempSensor2Pin);
  int diff=tempSensor1Val-tempSensor2Val;
  float voltage=diff*5.0/1023;
  temp=voltage*100;
  return temp;
}

void tempToMode(){
  if(-5<=temp and temp<10){
    heaterMode('o');
    fanMode('x');
    coolerMode('x');
  }
  else if(10<=temp and temp<15){
    heaterMode('x');
    fanMode('s');
    coolerMode('x');
  }
  else if(15<=temp and temp<20){
    heaterMode('x');
    fanMode('m');
    coolerMode('x');
  }
  else if(20<=temp and temp<25){
    heaterMode('x');
    fanMode('h');
    coolerMode('x');
  }
  else if(25<=temp and temp<30){
    heaterMode('x');
    fanMode('h');
    coolerMode('s');
  }
  else if(30<=temp and temp<35){
    heaterMode('x');
    fanMode('h');
    coolerMode('m');
  }
  else if(35<=temp and temp<=40){
    heaterMode('x');
    fanMode('h');
    coolerMode('h');
  }
  else Serial.println("Temp. limit exceeds!!!");
}

/*
 There are three modes of fan and cooler.
 1)High.
 2)Medium.
 3)Slow.
*/
void fanMode(char mode){
  if(mode=='x'){
    Serial.println("FAN IS OFF");
    digitalWrite(fanPin,LOW);
  }
  else{
    Serial.println("FAN IS ON");
    if(mode=='h'){
      analogWrite(fanPin,maxSpeed);
      Serial.println("FAN Mode : HIGH");
    }
    else if(mode=='m'){
      analogWrite(fanPin,medSpeed);
      Serial.println("FAN Mode : MEDIUM");
    }
    else if(mode=='s'){
      analogWrite(fanPin,lowSpeed);
      Serial.println("FAN Mode : LOW");
    }
  }
}

void coolerMode(char mode){
  if(mode=='x'){
    Serial.println("COOLER IS OFF");
    digitalWrite(coolerPin,LOW);
  }
  else{
    Serial.println("COOLER IS ON");
    if(mode=='h'){
      analogWrite(coolerPin,maxSpeed);
      Serial.println("COOLER Mode : HIGH");
    }
    else if(mode=='m'){
      analogWrite(coolerPin,medSpeed);
      Serial.println("COOLER Mode : MEDIUM");
    }
    else if(mode=='s'){
      analogWrite(coolerPin,lowSpeed);
      Serial.println("COOLER Mode : LOW");
    }
  }
}

void heaterMode(char mode){
  if(mode=='x'){
    Serial.println("HEATER IS OFF");
    digitalWrite(heaterPin,LOW);
  }
  else if(mode=='o'){
    Serial.println("HEATER IS ON");
    digitalWrite(heaterPin,HIGH);
  }
}

void loop(){
  int currentTemp=getTemp();
  int previousTemp=currentTemp;
  Serial.print("Temp.= ");
  Serial.print(currentTemp);
  Serial.println(" degree celsius");
  tempToMode();
  while(1){
    while(abs(previousTemp-currentTemp)<=1) currentTemp=getTemp();//screen will update after every 2 celsius change.
    Serial.println();
    Serial.print("Temp.= ");
    Serial.print(currentTemp);
    Serial.println(" degree celsius");
    tempToMode();
    Serial.println();
    previousTemp=currentTemp;
  }
}
