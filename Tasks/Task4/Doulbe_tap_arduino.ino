const char switchPin=13;
unsigned int timeInterval=0;
unsigned long currentTime=0;

void setup() {
  pinMode(switchPin,INPUT);
  Serial.begin(9600);
}

void printTime(){
  Serial.print(millis()-currentTime);
  Serial.println(" milli sec");
  Serial.println();
}

void detectDoubleTab(){
  Serial.println("Press the button");
  while(!digitalRead(switchPin));        //wait till switch is pressed.
  currentTime=millis();    //timer starts.
  while(digitalRead(switchPin));         //wait till first press is released.
  if(currentTime+timeInterval<millis()) {
    Serial.print("You missed it. Time=");
    printTime();
    return 0;
  }
  else {
    Serial.print("First tab detected at ");
    Serial.print(millis()-currentTime);
    Serial.println(" milli sec");
  }
  while(currentTime+timeInterval>=millis()){
    if(digitalRead(switchPin)){          //detect second press.
      while(digitalRead(switchPin));     //wait till second press is released.
      if(currentTime+timeInterval>=millis()){
        Serial.print("Double tap detected at ");
        printTime();
        return 0;
      }
      else {
        Serial.print("You missed it. Time=");
        printTime();
        return 0;
      }
    }
  }
  Serial.print("You missed it. Time=");
  printTime();  
}

void loop() {
  Serial.println("Double tab will be detected within provided interval");
  Serial.print("Enter time interval in milli sec : ");
  while(!Serial.available());
  timeInterval=Serial.parseInt();
  Serial.println(timeInterval);
  detectDoubleTab();
  Serial.println();
}
