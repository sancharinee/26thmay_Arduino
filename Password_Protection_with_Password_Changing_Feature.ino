#define buzzerPin 3
#define LEDPin 2

#include<EEPROM.h>

String password="";
String inputData="";
char inputChar=0,baseAddress=0;
unsigned char attempts=3; /*only 3 attempts will be given to enter password*/
bool hideInputData=0;

void setup() 
{
  pinMode(buzzerPin,OUTPUT);
  pinMode(LEDPin,OUTPUT);
  Serial.begin(9600);
  if(EEPROM.read(baseAddress)==255) /*default value stored in EEPROM is 255*/
  {
    password="default"; /*default password is 'default'*/
    writePassword();
  }
  else
  {
    readPassword();
  }
}

void loop() 
{
  mainMenu();
}

void writePassword() /*write string to EEPROM*/
{
  baseAddress=0;
  unsigned char index=0;
  unsigned char len=password.length();
  EEPROM.write(baseAddress,len);
  for(index=0;index<len;index++)
  {
    EEPROM.write(baseAddress+1,password[index]);
    baseAddress++;
  }
  baseAddress=0;
}

void readPassword() /*read string from EEPROM*/
{
  baseAddress=0;
  password="";
  unsigned char len=EEPROM.read(baseAddress),index=0;
  for(index=0;index<len;index++)
  {
    password.concat((char) EEPROM.read(baseAddress+1));
    baseAddress++;
  }
  baseAddress=0;
}

void mainMenu()
{
  Serial.println("MAIN MENU");
  Serial.println();
  Serial.println("1) Enter password.");
  Serial.println("2) Change password.");
  Serial.println();
  Serial.print("Enter your choice : ");
  hideInputData=0;
  takeInput();
  if(inputData=="1")
  {
    Serial.println();
    Serial.println();
    takeAndCheckPassword();
  }
  else if(inputData=="2")
  {
    Serial.println();
    Serial.println();
    changePassword();
  }
  else
  {
    Serial.println();
    Serial.println("Invalid Entry");
    Serial.println();
  }
}

void takeAndCheckPassword()
{
  Serial.println("AUTHENTICATION SYSTEM");
  Serial.println();
  hideInput();
  Serial.print("Enter password : ");
  takeInput();
  Serial.println();
  if(inputData==password)
  {
    attempts=3; /*after giving correct password*/
    Serial.println("Access Granted");
    Serial.println();
  }
  else
  {
    attempts--;
    Serial.println("Incorrect Password");
    alarmOn();
    delay(1000);
    alarmOff();
    Serial.println();
    Serial.print(attempts);
    Serial.println(" attempts left to ENTER PASSWORD");
    Serial.println();
    if(attempts==0)
    {
      Serial.println("System is locked");
      Serial.println("Restart the system");
      while(1) /*infinite loop to lock the system*/
      {
        alarmOn();
        delay(1000);
        alarmOff();
        delay(1000);
      }
    }
  }
}

void alarmOn()
{
  digitalWrite(LEDPin,HIGH);
  tone(buzzerPin,1000);
}

void alarmOff()
{
  digitalWrite(LEDPin,LOW);
  noTone(buzzerPin);
}

void hideInput() /* hide password while giving input*/
{
  Serial.print("Hide password (y/n) : ");
  takeInput();
  while(1) /*wait untill a valid entry is made.*/
  {
    if(inputData=="y")
    {
      hideInputData=1;
      Serial.println();
      Serial.println();
      break;
    }
    else if(inputData=="n")
    {
      hideInputData=0;
      Serial.println();
      Serial.println();
      break;
    }
    else
    {
      Serial.println();
      Serial.println("Invalid Entry");
      Serial.println();
      Serial.print("Hide password (y/n) : ");
      takeInput();
    }
  }
}

/*press enter at last to give input*/
/*input is read character by character*/
void takeInput() 
{
  char inputChar=0;
  inputData="";
  unsigned short len=0;
  while(1)
  {
    while(!Serial.available());
    inputChar=Serial.read();
    if(inputChar=='\r')
    {
      break;
    }
    else
    {
      len=inputData.length();
      if(inputChar=='\b' and len!=0) /*backspace is pressed*/
      {
        Serial.print(inputChar);
        inputData.remove(len-1,1);  /*delete the char whenever backspace is pressed*/
      }
      if(hideInputData==1 and inputChar!='\b') /* star('*') will be printed if hide password is chosen*/
      {
        Serial.print("*");
        inputData.concat(inputChar);
      }
      if(hideInputData==0 and inputChar!='\b')
      {
        Serial.print(inputChar);
        inputData.concat(inputChar);
      }
    }
  }
}

void changePassword()
{
  Serial.println("CHANGE PASSWORD");
  Serial.println("");
  checkPreviousPassword();
}

void checkPreviousPassword()
{
  hideInput();
  Serial.print("Enter previous password : ");
  takeInput();
  Serial.println();
  if(inputData==password)
  {
    Serial.println();
    takeNewPassword();
  }
  else
  {
    Serial.println("Incorrect previous Password");
    alarmOn();
    delay(1000);
    alarmOff();
    Serial.println();
  }
}

void takeNewPassword()
{
  String newPassword;
  hideInput();
  Serial.print("Enter new password : ");
  takeInput();
  newPassword=inputData;
  Serial.println();
  Serial.print("Re-Enter new password : ");
  takeInput();
  if(inputData==newPassword)
  {
    Serial.println("");
    Serial.println("Password changed successfully");
    Serial.println("");
    password=newPassword;
    writePassword();
  }
  else
  {
    Serial.println("");
    Serial.println("Incorrect re-entered password");
    Serial.println("");
  }
}
