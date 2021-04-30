
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
 
int num_Measure = 20 ; // Set the number of measurements   
int pinSignal = A0; // pin connected to pin O module sound sensor  
int redLed = 5; 
long Sound_signal;    // Store the value read Sound Sensor   
long sum = 0 ; // Store the total value of n measurements   
long level = 0 ; // Store the average value   
int soundlow = 40;
int soundmedium = 150;
 
void setup ()  
{   
  pinMode (pinSignal, INPUT); // Set the signal pin as input   
  Serial.begin (9600); 
  lcd.begin(16,2); 
  lcd.init(); // initialize the lcd
  lcd.backlight();
}  
   
void loop ()  
{  
  // Performs 128 signal readings   
  for ( int i = 0 ; i <num_Measure; i ++)  
  {  
   Sound_signal = analogRead (pinSignal);  
    sum =sum + Sound_signal;  
  }  
 
  level = sum / num_Measure; // Calculate the average value   
  Serial.print("Sound Level: ");
  lcd.print("Sound Level= ");
 

  Serial.println (level-364);  
  lcd.print(level-364);
  if(level-364<soundlow)
  {
    lcd.setCursor(0,1);
    lcd.print("Intensitas : Low");
     digitalWrite(redLed,LOW);
  }
  if(level-364>soundlow && level-364<soundmedium)
  {
    lcd.setCursor(0,1);
    lcd.print("Intens : Medium"); 
     digitalWrite(redLed,LOW); 
  }
  if(level-364>soundmedium)
  {
    lcd.setCursor(0,1);
    lcd.print("Intensitas : High");   
    digitalWrite(redLed,HIGH); 
  }
  sum = 0 ; // Reset the sum of the measurement values  
  delay(500);
  lcd.clear();
}
