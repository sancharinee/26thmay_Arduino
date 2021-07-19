#include<SoftwareSerial.h>
SoftwareSerial arduinoTerminal(2,3);

String password="btapp",inputString="";
byte stringLen=0;

void setup() {
  Serial.begin(9600);
  arduinoTerminal.begin(9600);
}

void printNewLineMobile(int n){
  for(int i=1;i<=n;i++) Serial.println();
}

void printNewLineArduino(int n){
  for(int i=1;i<=n;i++) arduinoTerminal.println();
}

void takePassFromMobileTerminal(){
  Serial.print("Enter password : ");
  while(!Serial.available());
  inputString=Serial.readString();
  stringLen=inputString.length();
  for(int i=1;i<=stringLen;i++) Serial.print("*");
  printNewLineMobile(2);
}

bool passCheck(){
  if(inputString==password) {
    Serial.print("Access granted");
    printNewLineMobile(2);
    return true;
  }
  else {
    Serial.print("Access denied");
    printNewLineMobile(2);
    return false;
  }
}

void forward(){
   arduinoTerminal.print("Moving forward");
   printNewLineArduino(2);
}

void backward(){
   arduinoTerminal.print("Moving backward");
   printNewLineArduino(2);
}

void left(){
   arduinoTerminal.print("Moving left");
   printNewLineArduino(2);
}

void right(){
   arduinoTerminal.print("Moving right");
   printNewLineArduino(2);
}

void Stop(){
   arduinoTerminal.print("Motion stop");
   printNewLineArduino(2);
}

void openApp(){
  while(1){
    Serial.println("5 services are provided : ");
    printNewLineMobile(1);
    Serial.println("1) Forward (press f)");
    Serial.println("2) Backward (press b)");
    Serial.println("3) Left (press l)");
    Serial.println("4) Right (press r)"); 
    Serial.println("5) Stop (press s)");
    Serial.println("6) Press any other key to exit.");
    printNewLineMobile(1);
    Serial.print("Enter your choice : ");
    while(!Serial.available());
    inputString=Serial.readString();
    Serial.print(inputString);
    printNewLineMobile(2);
    if(inputString=="f") forward();
    else if(inputString=="b") backward();
    else if(inputString=="l") left();
    else if(inputString=="r") right();
    else if(inputString=="s") Stop();
    else break;
  }
}

void loop() {
  takePassFromMobileTerminal();
  if(passCheck()) openApp(); 
}
