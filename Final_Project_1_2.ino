#include <LiquidCrystal.h>
LiquidCrystal lcd(3,4,10,11,12,13);
const int sensor=A3;
int pulse = 0;
int lr = 0;
int li = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Instrumentation");
  lcd.setCursor(3,1);
  lcd.print("Medic");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PulseOximeter");
  lcd.setCursor(0,1);
  lcd.print("Project potato");
  delay(500);
  lcd.clear();
  Serial.begin(9600);
  Serial.println("Tempareture Sensor");
  Serial.println();
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  pulse=analogRead(A0);
  lr=analogRead(A1);
  li=analogRead(A2);
  lr=map(lr,0,1023,00,150);
  li=map(lr,0,1023,00,100);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PPM: ");
  lcd.setCursor(4,0);
  lcd.print(lr);
  lcd.setCursor(8,0);
  lcd.print("SPO2: ");
  lcd.setCursor(13,0);
  lcd.print(li);
  lcd.setCursor(15,0);
  lcd.print("%");
  if(li<90) {
    digitalWrite(7,HIGH);
    digitalWrite(5,HIGH);
    lcd.setCursor(3,1);
    lcd.print("Hypoxia Alart");
  }
  else {
    digitalWrite(7,LOW);
    digitalWrite(5,LOW);
  }
  if(li>=90&&li<=93) {
    digitalWrite(6,HIGH);
    lcd.setCursor(3,1);
    lcd.print("Lucky Day Man");  
  }
  else {
    digitalWrite(6,HIGH);
  }
  delay(150);
  int vout=analogRead(sensor);
  vout=(vout*4.88)/10;
  int tempc=vout;
  int tempf=(vout*1.8)+32;
  Serial.print("Temperature in C=");
  Serial.print("\t");
  Serial.print(tempc);
  Serial.print("Temperature in F=");
  Serial.print("\t");
  Serial.print(tempf);
  Serial.println();
  delay(1000);
}
