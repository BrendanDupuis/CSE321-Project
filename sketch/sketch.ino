#include <LiquidCrystal_I2C.h>

#define s0 8
#define s1 9
#define s2 10
#define s3 11
#define out 12
//#define CALIBRATION BUTTON //What pin
//#define START BUTTON //What pin

volatile int  Red=0, Blue=0, Green=0;
volatile int Red_Range[2] = {0,0}; //Red+15,red-15
volatile int Green_Range[2] = {0,0}; //Green+15,Green-15
volatile int Blue_Range[2] = {0,0}; //Blue+15,Blue-15

volatile unsigned long prevTime = 0, period = 0, startRangeTime=0;
volatile float rpm = 0;
volatile int start = 0;
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
 //  pinMode(CALIBRATION_BUTTON,INPUT);
//   pinMode(START_BUTTON,INPUT);
   pinMode(out,INPUT);

   Serial.begin(9600);

   lcd.backlight();
   lcd.setCursor(0, 0);
   

   digitalWrite(s0,HIGH); //Putting S0/S1 on HIGH/HIGH levels  means the output frequency scalling is at 100% (recommended)
   digitalWrite(s1,HIGH);  //LOW/LOW is off HIGH/LOW is 20% and LOW/HIGH is  2%
   detectStartColor();

}
void detectStartColor(){ //Sensor is pointing directly at sticker, no rotation so we can get color number range
  int read = 0;
  int redAvg = 0;
  int blueAvg = 0;
  int greenAvg = 0;
  lcd.setCursor(0, 0);
  lcd.print("Calibrating.");
  int prevLCD = 12;
  while(millis()-startRangeTime <3100){
      GetColors();           //Sets red blue and green
      read++;
      redAvg = (Red+redAvg)/read;
      greenAvg = (Green+greenAvg)/read;
      blueAvg = (Blue+blueAvg)/read;
      if(millis()-startRangeTime%1000 == 0){  //Printing Calibrating. *wait* . *wait* .
          lcd.setCursor(prevLCD+1,0);
          lcd.print(".");
          prevLCD++;
      }
  }
  Red_Range[0] = redAvg + 15;
  Red_Range[1] = redAvg - 15;
  Blue_Range[0] = blueAvg + 15;
  Blue_Range[1] = blueAvg - 15;
  Green_Range[0] = greenAvg + 15;
  Green_Range[1] = greenAvg - 15;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Calibrated!");
  Serial.print(Red_Range[0]);
  Serial.print(Green_Range[0]);
  Serial.print(Blue_Range[0]);

}
void loop(){
  //if(CALIBRATION_BUTTON == HIGH){  //Uncomment when we have button
  //  createColorRange();
  //  startRangeTime=millis();
  //}
  //if(START_BUTTON == HIGH){ //Uncomment when implement start button
  //  lcd.clear();
  //  start = 1;
  //}
  if(start == 1){
    if(sensorTrigger && prevTime + 500 < millis()){
      sensorTrigger = false;
    }
    GetColors();
    //if (Blue<Red && Blue<Green && Blue<14 && !sensorTrigger){ //No Range, just update when red
    if(Red<Red_Range[0] && Red>Red_Range[1] && Blue<Blue_Range[0] && Blue>Blue_Range[1] && Green<Green_Range[0] && Green>Green_Range[1]){ //With range from calibration
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
