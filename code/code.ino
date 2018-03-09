#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int PIRPinIn = 6;
const int PIRPinOut = 9;
const int ledPin = 13;
const int ledPinRed = 10;

int PIROut = -1;
int PIRIn = -1;

int pirState = LOW;
int valIn = 0;
int valOut = 0;

int aux = 13;
int control = 0;
int valuePIRIn = -1;
int valuePIROut = - 1;
int valuePIR = -1;

bool flagPIROut = false;
bool flagPIRIn = false;

void setup() {
  lcd.begin(16, 2);
  pinMode(PIRPinIn, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPinRed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
   lcd.setCursor(0,0);
   lcd.print("People: ");
   prettyPrint(control, aux);
   valuePIRIn = PIRReadingIn (PIRPinIn);
   valuePIROut = PIRReadingOut(PIRPinOut);
   
   delay(100);
   
   if (valuePIRIn == HIGH && valuePIROut == LOW){
      flagPIRIn = true;
   }else if(valuePIROut == HIGH && valuePIRIn == LOW){
      flagPIROut = true;
   }

   if (flagPIRIn){
      delay(100);
      if (PIRReadingOut(PIRPinOut) == HIGH){
        control -= 1;
        if(control < 0 ){
          control = 0;
        }
      }
   }

   if (flagPIROut){
      delay(100);
      if (PIRReadingIn(PIRPinIn) == HIGH){
        control += 1;
      }
   }
   flagPIRIn = false;
   flagPIROut = false;
}

int PIRReadingIn(int PIRPins) {
  valIn = digitalRead(PIRPins);  
  
  if (valIn == HIGH) {         
    digitalWrite(ledPinRed, HIGH);
    if (pirState == LOW) {
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPinRed, LOW);
    if (pirState == HIGH){
      pirState = LOW;
    }
  }
  return valIn;
}

int PIRReadingOut(int PIRPins) {
  valOut = digitalRead(PIRPins); 
  
  if (valOut == HIGH) {           
    if (pirState == LOW) {
      digitalWrite(ledPin, HIGH);
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW);
    if (pirState == HIGH){
      pirState = LOW;
    }
  }
  return valOut;
}

void prettyPrint(int control, int aux){
  for(aux++; aux <= 15; aux++){
    lcd.setCursor(aux,1);
    lcd.print(" ");
  }
  if (control < 10){
    lcd.setCursor(15,1);
  }else if (control >= 10 && control <= 99){
    lcd.setCursor(14, 1);
  }else{
    lcd.setCursor(13, 1);
  }
  lcd.print(control);
  aux = 13;
}
 
