#include <LiquidCrystal_I2C.h>

#define s0 8
#define s1 9
#define s2 10
#define s3 11
#define out 12

volatile int  Red=0, Blue=0, Green=0;
volatile unsigned long prevTime = 0, period = 0;
volatile float rpm = 0;
bool sensorTrigger = false;
volatile unsigned long prev;


LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() 
{
  lcd.init(); // initialize the lcd
   pinMode(s0,OUTPUT);
   pinMode(s1,OUTPUT);
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
   pinMode(out,INPUT);

   Serial.begin(9600);

   lcd.backlight();
   lcd.setCursor(0, 0);
   

   digitalWrite(s0,HIGH); //Putting S0/S1 on HIGH/HIGH levels  means the output frequency scalling is at 100% (recommended)
   digitalWrite(s1,HIGH);  //LOW/LOW is off HIGH/LOW is 20% and LOW/HIGH is  2%


}

void loop(){
  if(sensorTrigger && prevTime + 500 < millis()){
    sensorTrigger = false;
  }

  GetColors();
  if (Blue<Red && Blue<Green && Blue<14 && !sensorTrigger){
      sensorTrigger = true;
      unsigned long currentTime = millis();
      period = currentTime-prevTime;
      prevTime = currentTime;
      rpm = 60000.0/period;
      lcd.setCursor(0, 0);
      lcd.print("rpm:");
      lcd.setCursor(0,1);
      lcd.print(rpm);
      Serial.print(rpm);
  }
}


void GetColors()  
{    
  digitalWrite(s2,  LOW);
  digitalWrite(s3, LOW);                                           
  Red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH); 
  delay(20);  
  digitalWrite(s3, HIGH);                                         
  Blue = pulseIn(out, digitalRead(out) == HIGH ? LOW  : HIGH);
  delay(20);  
  digitalWrite(s2, HIGH);  
  Green = pulseIn(out,  digitalRead(out) == HIGH ? LOW : HIGH);
  delay(20);  
}

