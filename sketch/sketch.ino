#define s0 8
#define s1 9
#define s2 10
#define s3 11
#define out 12

volatile int  Red=0, Blue=0, Green=0;
volatile unsigned long prevTime = 0, period = 0;
volatile float rpm = 0;

void setup() 
{
   pinMode(s0,OUTPUT);
   pinMode(s1,OUTPUT);
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
   pinMode(out,INPUT);

   Serial.begin(9600);
   
   digitalWrite(s0,HIGH); //Putting S0/S1 on HIGH/HIGH levels  means the output frequency scalling is at 100% (recommended)
   digitalWrite(s1,HIGH);  //LOW/LOW is off HIGH/LOW is 20% and LOW/HIGH is  2%
}

void loop(){
  GetColors();
  if (Red<Blue && Red<=Green && Red<23){
      unsigned long currentTime = millis();
      period = currentTime-prevTime;
      prevTime = currentTime;
      rpm = 60000.0/period;
      Serial.println(rpm);
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

