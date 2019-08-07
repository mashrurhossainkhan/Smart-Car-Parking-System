#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
#define LED_G 5
#define LED_R 4
#define BUZZER 2
Servo myServo;
Servo myServo1;
int a0=0, a2=0, d6=0;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  myServo.attach(3);
  myServo.write(0);
  myServo1.attach(7);
  myServo1.write(0);

  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  pinMode(A0, INPUT);
  pinMode(A2, INPUT);
  pinMode(6, INPUT);
  pinMode(8, OUTPUT);
  pinMode(A1, INPUT); //EXIT

  
  

}
void loop() 
{ 
  delay(3000);
  int val = digitalRead(6);
  if(val == 1){
    d6 = 0;
  }
  if(!analogRead(A0) < 500){
    a0 = 0;
  }
  if(!analogRead(A2) < 500){
    a2 = 0;
  }

  if(a0 ==0 || a2 == 0 || d6 == 0){
  if(val == 0){
    a2 = 1;
    digitalWrite(LED_G, LOW);
    delay(1000);
   
  }
  else{
    a2 = 0;
  }
  
  if(analogRead(A0) < 500){
    a0 = 1;
    digitalWrite(LED_G, LOW);
    delay(1000);
    
  }
  else{
    a0 = 0;
  }
  if(analogRead(A2) < 500){
    d6 = 1;
    digitalWrite(LED_G, LOW);
    delay(1000);
    
  }
  else{
    d6 = 0;
  }
  if(analogRead(A1) < 500){
    Serial.println("See you again");
    digitalWrite(LED_R, HIGH);
    delay(1000);
    tone(BUZZER, 500);
    delay(1000);
    noTone(BUZZER);
    myServo1.write(90);
    delay(5000);
    myServo1.write(0);
    delay(1000);
    digitalWrite(LED_R, LOW);
    
  }
  else{
    
  }
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "73 04 F6 2D" && (a0 ==0 || a2 == 0 || d6 == 0)) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("WELCOME BMW");
    digitalWrite(LED_G, HIGH);
    delay(1000);
    tone(BUZZER, 500);
    delay(1000);
    noTone(BUZZER);
    myServo.write(90);
    delay(1000);
    myServo.write(0);
    
  }
  else if (content.substring(1) == "9E 93 9A 5A" && (a0 ==0 || a2 == 0 || d6 == 0)) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("WELCOME AUDI");
    digitalWrite(LED_G, HIGH);
    delay(1000);
    tone(BUZZER, 500);
    delay(1000);
    noTone(BUZZER);
    myServo.write(90);
    delay(1000);
    myServo.write(0);
    
  }
  else   {
    Serial.println(" Access denied");
    for(int i=0; i<3; i++){
      tone(BUZZER, 1000);
    delay(1000);
    noTone(BUZZER);
      digitalWrite(8, HIGH);
    delay(1000);
    
    
    digitalWrite(8, LOW);
    }
  }
  }
 
 
} 
