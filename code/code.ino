#include <LiquidCrystal.h>

// Estos son los pines a la Arduino donde la pantalla esta conectada
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int PIRPin = 6;
const int PIRPinFuera = 9;
const int hallPin = 8;
const int ledPin = 13;

int PIROut = -1;
int PIRIn = -1;

int pirState = LOW;
int pirStateFuera = LOW;
int val = 0;

int aux = 13;
int control = 0;
int valuePIR = -1;
int valueHALL = -1;

void setup() {
  // Columnas y filas de la pantalla LCD:
  lcd.begin(16, 2);
  pinMode(PIRPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(hallPin, INPUT);
  Serial.begin(9600);
}

void loop() {
   lcd.setCursor(0,0);
   lcd.print("People: ");
   valueHALL = digitalRead(hallPin);
   if (valueHALL == LOW){
      //Cerrado
      PIRIn = PIRReading(PIRPin);
      if (digitalRead(hallPIN == HIGH) && PIRIn == HIGH{
        PIROut = PIRReading(PIRPinFuera);
        if (PIROut == HIGH){
          control -= 1;
        }
      }
   }else{
      //Abierto
   }
   //control = testPIR(control);
   //prettyPrint(control, aux);
   //Serial.print(control);
   //delay(100);*/
   hallSensor();
}

int PIRReading(int PIRPins) {
  val = digitalRead(PIRPins);  // read input value
  
  if (val == HIGH) {            // check if the input is HIGH
    //lcd.clear();
    if (pirState == LOW) {
      digitalWrite(ledPin, HIGH);
      // we have just turned on
      //lcd.print("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    Serial.print("--->");
    digitalWrite(ledPin, LOW);
    if (pirState == HIGH){
      // we have just turned of
      //lcd.print("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
  //delay(100);
  return pirState;
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

/*void testScreen(){
 control = 0;
 // Mensaje:
  lcd.print("Contador cutre:");
  // Poner el cursor a la fila 0 (la primera) o a 1 (la segunda fila)
  // Las columnas iran de 0 a 15, ya que es un display de 16 columnas y 2 filas
  lcd.setCursor(15, 1);
  lcd.print(control);
  delay(1000);
  for (x=0; x < maxNum*2; x++){
    lcd.setCursor(15, 1);
    if (flag){
      control--;
    }else{
      control++;
      if (control == maxNum){
        flag = true;
        lcd.setCursor(14, 1);
      }
    }
    lcd.print(control);
    delay(1000);
    // Borramos el 1 del 10
    if (control == maxNum){
      lcd.setCursor(14, 1);
      lcd.print(" ");
    }
  }
  lcd.clear();
  lcd.print("DONE");
  flag = false;
  delay(1000);
  lcd.clear(); 
}*/

/*void hallSensor(){
  valueHALL = digitalRead(hallPin);
  
  /*if(valueHALL == LOW){
    // CERRADO
    digitalWrite(ledPin, LOW);
    if (pirState == HIGH){
      // we have just turned of
      //lcd.print("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }else{
    // ABIERTO
    pirState = HIGH
   //control = testPIR(control);
   //prettyPrint(control, aux);
   //Serial.print(control);
  }
  //delay(2000);
}*/

int PIRSensor(int PIRPin){
  valuePIR = digitalRead(PIRPin);
  lcd.setCursor(0,0);
  lcd.print("Detected -> ");
  if (valuePIR == HIGH){
    lcd.print("Y");
  }else{
    lcd.print("N");
  }
  return valuePIR;
}
 
