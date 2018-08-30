#include <Servo.h>
#include <Keypad.h>
#include<LiquidCrystal.h>
#include<EEPROM.h>
 #include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);
LiquidCrystal lcd(9,8,7,6,5,4);
Servo myservo;
int pos=0;
char password[4];
char pass[4],pass1[4];
int i=0; 
int pulse=1500;
char customKey=0;
const byte ROWS = 4;
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
byte rowPins[ROWS] = {A0,A1,A2,A3};
byte colPins[COLS] = {A4,A5,13,12};
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
int led;
int buzzer = 10;
int m11;
int m12;
void setup()
{ 
  Serial.begin(9600);
  pinMode(11, OUTPUT);
   myservo.attach(11); 
   delay(100);
 mySerial.begin(9600);  
  Serial.begin(9600);   
  delay(100);
  lcd.begin(16,2);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  lcd.print(" Electronic ");
  Serial.print(" Electronic ");
  lcd.setCursor(0,1);
  lcd.print(" Keypad Lock ");
  Serial.print(" Keypad Lock ");
  delay(2000);
  lcd.clear();
  lcd.print("Enter Ur Passkey:");
  Serial.println("Enter Ur Passkey:");
  lcd.setCursor(0,1);
  for(int j=0;j<4;j++)
    EEPROM.write(j, j+49);
  for(int j=0;j<4;j++)
    pass[j]=EEPROM.read(j);
}

void loop()
{
  //digitalWrite(11, HIGH);
  customKey = customKeypad.getKey();
  if(customKey=='*')
  changeabc();
  if(customKey=='#')
    change();
  if (customKey)
  {
    password[i++]=customKey;
    lcd.print(customKey);
    Serial.print(customKey);
    beep();
  }
  if(i==4)
  {
    delay(200);
    for(int j=0;j<4;j++)
      pass[j]=EEPROM.read(j);
    if(!(strncmp(password, pass,4)))
    {
      
       for (pos = 0; pos <=180 ; pos += 1) { 
    myservo.write(pos);             
  }
  
    

   delay(100); 
      digitalWrite(led, HIGH);
      beep();
      lcd.clear();
      lcd.print("Passkey Accepted");
      Serial.println("Passkey Accepted");

     delay(5000); //5s gap as delay 
         
        for(pos=180;pos>=0;pos-=1)
        {
          myservo.write(pos);
        }
      delay(2000);
      lcd.setCursor(0,1);
      lcd.print("#.Change Passkey");
      Serial.println("#.Change Passkey");
      delay(2000);
      lcd.clear();
      lcd.print("Enter Passkey:");
      Serial.println("Enter Passkey:");
      lcd.setCursor(0,1);
      i=0;
      digitalWrite(led, LOW);
    }
    else
    {
                         
      
      digitalWrite(buzzer, HIGH);
      lcd.clear();
      lcd.print("Access Denied...");
      Serial.println("Access Denied...");
      lcd.setCursor(0,1);
      lcd.print("#.Change Passkey");
      Serial.println("#.Change Passkey");
      delay(2000);
      lcd.clear();
      lcd.print("Enter Passkey:");
      Serial.println("Enter Passkey:");
      lcd.setCursor(0,1);
      i=0;
      digitalWrite(buzzer, LOW);
       SendMessage();
    }
  }
}
void change()
{
  int j=0;
  lcd.clear();
  lcd.print("UR Current Passk");
  Serial.println("UR Current Passk");
  lcd.setCursor(0,1);
  while(j<4)
  {
    char key=customKeypad.getKey();
    if(key)
    {
      pass1[j++]=key;
      lcd.print(key);
      Serial.print(key);
      beep();
    }
    key=0;
  }
  delay(500);

  if((strncmp(pass1, pass, 4)))
  {
    lcd.clear();
    lcd.print("Wrong Passkey...");
    Serial.println("Wrong Passkey...");
    lcd.setCursor(0,1);
    lcd.print("Better Luck Again");
    Serial.println("Better Luck Again");
    delay(1000);
  }
  else
  {
    j=0;
    lcd.clear();
    lcd.print("Enter New Passk:");
    Serial.println("Enter New Passk:");
    lcd.setCursor(0,1);
    while(j<4)
    {
      char key=customKeypad.getKey();
      if(key)
      {
        pass[j]=key;
        lcd.print(key);
        Serial.print(key);
        EEPROM.write(j,key);
        j++;
        beep();
      }
    }
    lcd.print(" Done......");
    Serial.println(" Done......");
    delay(1000);
  }
  lcd.clear();
  lcd.print("Enter Ur Passk:");
  Serial.println("Enter Ur Passk:");
  lcd.setCursor(0,1);
  customKey=0;
}
void beep()
{
  digitalWrite(buzzer, HIGH);
  delay(20);
  digitalWrite(buzzer, LOW);
}

 void SendMessage()
{
  mySerial.println("AT+CMGF=1");  
  delay(1000); 
  mySerial.println("AT+CMGS=\"+918910707970\"\r"); 
  delay(1000);
  mySerial.println("Intruder alert");
  delay(100);
   mySerial.println((char)26);
  delay(1000);
}

void changeabc()
{ delay(200);
    for(pos=180;pos>=0;pos-=1)
        {
          myservo.write(pos);
        }
}

