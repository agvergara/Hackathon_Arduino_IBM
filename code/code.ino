#include <LiquidCrystal.h>

// Estos son los pines a la Arduino donde la pantalla esta conectada
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int UltraSPinEntrada = 6;
const int UltraSPinSalida = 7;
const int hallPin = 8;
const int ledPin = 13;
int photocellPin = 0;
int photocellReading = -1;
int tempReading = -1;
int tempPin = 1 ;
int PIREntrada = -1;
int PIRSalida = -1;

int control = 0;
int maxNum = 10;
int x = 0;
int valuePIR = -1;
int valueHALL = -1;
bool flag = false;

float voltTemp = 0.0;
float temp = 0.0;

void setup() {
  // Columnas y filas de la pantalla LCD:
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(UltraSPinEntrada, OUTPUT);
  pinMode(UltraSPinSalida, INPUT);
  pinMode(ledPin, OUTPUT);
  //pinMode(hallPin, INPUT);
}

 void loop()
        {   long duracion, distancia ;
       pinMode(UltraSPinEntrada, OUTPUT);
            digitalWrite(UltraSPinEntrada, LOW);
            delayMicroseconds(2);
            digitalWrite(UltraSPinEntrada, HIGH);
            delayMicroseconds(5);
            pinMode(UltraSPinEntrada, INPUT);
            digitalWrite(UltraSPinEntrada, LOW);
            duracion = pulseIn(UltraSPinEntrada, HIGH) ;
            distancia = duracion / 2 / 29.1  ;
            Serial.println(String(distancia) + " cm.") ;
            int Limite = 200 ;                  // Medida en vacío del sensor
            if ( distancia < Limite)
                 Serial.println('Loquequieras');
            else
                 Serial.println('Esto es una traza');
            delay (100);                  // Para limitar el número de mediciones
        }


/*void loop() {
   PIREntrada = pulseIn(echoPin, HIGH) ;

  //PIREntrada = PIRSensor(UltraSPinEntrada);
  Serial.println(PIREntrada);
  PIRSalida = PIRSensor(UltraSPinSalida);
  if (PIREntrada && !PIRSalida){
    PIRSalida = PIRSensor(UltraSPinSalida);
    if (PIRSalida){
      Serial.println("Entrando");
    }else{
      Serial.println("Algo raruno entrando");
    }
  }else if (!PIREntrada && PIRSalida){
    PIREntrada = PIRSensor(UltraSPinSalida);
    if (PIREntrada){
      Serial.println("Saliendo");
    }else{
      Serial.println("Algo raruno saliendo");
    }
  }
  PIREntrada = -1;
  PIRSalida = -1;
}*/

void testScreen(){
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
}

void hallSensor(){
  if(valueHALL == LOW){
    lcd.print("CERRADO");
  }else{
    lcd.print("ABIERTO");
  }
}

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

void photoSensor(int photocellPin, int ledPin){
  int reading = -1;
  reading = analogRead(photocellPin);
  digitalWrite(ledPin, HIGH);
  delay(reading);
  digitalWrite(ledPin, LOW); 
  delay(reading);
  Serial.print("LDR: ");
  Serial.println(reading);
}

int tempSensor(int tempPin){
  tempReading = analogRead(tempPin);
  voltTemp = 5.0 / 1024 * tempReading;
  temp = voltTemp * 100 - 50;
  return temp;
}
 
