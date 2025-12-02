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
volatile float rpm = 0.0;
volatile int start = 0;
bool sensorTrigger = false;
volatile unsigned long prev;

volatile unsigned long tot_actual_ms;
volatile uint32_t rev_count = 0;



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
  int nextTime = 2000;
  bool boolFlag = false;
  lcd.setCursor(0, 0);
  lcd.print("Calibrating.");
  int prevLCD = 12;
  while(millis()-startRangeTime <3000){
      GetColors();           //Sets red blue and green
      if(millis()-startRangeTime<nextTime){
        boolFlag = true;
        nextTime-=1000;
      }
      read++;
      redAvg = Red+redAvg;
      greenAvg = Green+greenAvg;
      blueAvg = Blue+blueAvg;
      if(boolFlag){  //Printing Calibrating. *wait* . *wait* .
          lcd.setCursor(prevLCD+1,0);
          lcd.print(".");
          prevLCD++;
          boolFlag = false;
      }
  }
  Red_Range[0] = redAvg/read + 15;
  Red_Range[1] = redAvg/read - 15;
  Blue_Range[0] = blueAvg/read + 15;
  Blue_Range[1] = blueAvg/read - 15;
  Green_Range[0] = greenAvg/read + 15;
  Green_Range[1] = greenAvg/read - 15;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Calibrated!");
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
  if(millis()>4000 && start!=1){
    start = 1;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Beginning in:");
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print("3");
    delay(1000);
    lcd.setCursor(0, 2);
    lcd.print("2");
    delay(1000);
    lcd.setCursor(0, 3);
    lcd.print("1");
    delay(1000);
    lcd.clear();
  }
  if(start == 1){
    if(sensorTrigger && prevTime + 500 < millis()){
      sensorTrigger = false;
    }
    GetColors();
    if (Blue<Red && Blue<Green && Blue<14 && !sensorTrigger){ //No Range, just update when red
   // if(Red<Red_Range[0] && Red>Red_Range[1] && Blue<Blue_Range[0] && Blue>Blue_Range[1] && Green<Green_Range[0] && Green>Green_Range[1] && !sensorTrigger){ //With range from calibration

        // RPM calculation
        lcd.clear(); // should properly reset any sticking numbers. Try removing if issues involving visibility of numbers
        sensorTrigger = true;
        unsigned long currentTime = millis();
        period = currentTime-prevTime;
        prevTime = currentTime;
        rpm = 60000.0/period;
        lcd.setCursor(0, 0);
        lcd.print("rpm:");
        lcd.setCursor(0,1);
        lcd.print(rpm);
        //Serial.print(rpm);



        //Time gain / loss calculation:
        tot_actual_ms += period;
        rev_count++; //will be multiplied by 1.8s if 33.3RPM setting, and 1.33s if 45RPM setting in calculation
        long tot_ideal_ms = (long)rev_count*1800.0;
        if(){ //if button for switching RPM setting is pressed (brendan please implement this if statement, let user change to 45 RPM while start timer thing is active using button)
          tot_ideal_ms = (long)rev_count*1333.3;
        }
        double error_s = (double)(tot_actual_ms - tot_ideal_ms) / 1000.0;

        lcd.setCursor(0, 2);
        lcd.print("Time gain/loss:");
        lcd.setCursor(7, 3);
        lcd.print(error_s);
        lcd.setCursor(13,4);
        lcd.print("sec");
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
