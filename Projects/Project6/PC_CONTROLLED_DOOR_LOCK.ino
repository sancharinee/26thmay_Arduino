#include<Servo.h>

Servo drive;

unsigned char buzzerPin=3,servoPin=2;
String password="doorlock",inputString="";
bool doorClose=1;

void setup() {
  pinMode(buzzerPin,OUTPUT);
  pinMode(servoPin,OUTPUT);
  drive.attach(servoPin);
  Serial.begin(9600);
  drive.write(0); //close the door
}

void hidePassword(){
  unsigned char len=inputString.length();
  for(int i=1;i<=len;i++) Serial.print("*");
  Serial.println();
}

void openDoor(){
  Serial.println("Door is opening.......");
  for(int i=0;i<=90;i++){
    drive.write(i);
    delay(100);
  }
  Serial.println("Door is opened now");
  Serial.println();
  doorClose=0;
}

void closeDoor(){
  Serial.println("Door is closing.......");
  for(int i=90;i>=0;i--){
    drive.write(i);
    delay(100);
  }
  Serial.println("Door is closed now");
  Serial.println();
  doorClose=1;
}

void controlDoor(){
  String command="";
  while(1){
    Serial.println("PC controlled Door lock");
    Serial.println();
    if(doorClose){
      while(1){
        Serial.println("Door is close");
        Serial.print("Type 'open' to open the door : ");
        while(!Serial.available());
        command=Serial.readString();
        Serial.println(command);
        Serial.println();
        if(command=="open"){
          openDoor();
          break;
        }
        else {
          Serial.println("Enter a valid input");
          Serial.println();
        }
      } 
    }
    else{
      while(1){
        Serial.println("Door is open");
        Serial.print("Type 'close' to close the door : ");
        while(!Serial.available());
        command=Serial.readString();
        Serial.println(command);
        Serial.println();
        if(command=="close"){
          closeDoor();
          break;
        }
        else {
          Serial.println("Enter a valid input");
          Serial.println();
        }
      } 
    } 
  }
  Serial.println();
}

bool takePassword(){
  Serial.print("Enter password : ");
  while(!Serial.available());
  inputString=Serial.readString();
  hidePassword();
  if(inputString==password){
    Serial.println("Access granted");
    Serial.println();
    controlDoor();
  }
  else{
    Serial.println("Access denied");
    Serial.println("Alarm is ON!!!");
    Serial.println("Restart the system");
    while(1){
      tone(buzzerPin,1000);
      delay(500);
      noTone(buzzerPin);
      delay(500);
    }
    Serial.println();
  }
}

void loop() {
  takePassword();
  controlDoor(); 
}
