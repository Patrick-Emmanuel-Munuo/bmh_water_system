// defines pins numbers
const int sensor1_trigPin = 9;
const int sensor1_echoPin = 10;
const int sensor2_trigPin = 11;
const int sensor2_echoPin = 12;
// defines variables
float tank1_empty = 5.68;
float tank2_empty = 7.984;
int pump = 13;


int selonoid = 8;
int utility_supply = 7;
bool utility_supply_available = false;

// include the library code:
#include <LiquidCrystal.h>
LiquidCrystal lcd(4,5,A4,A3,A2,A1);

void setup() {
  // put your setup code here, to run once:
   pinMode(sensor1_trigPin, OUTPUT);
   pinMode(sensor1_echoPin, INPUT);
   pinMode(sensor2_trigPin, OUTPUT);
   pinMode(sensor2_echoPin, INPUT);
   Serial.begin(9600); // Starts the serial communication
      lcd.begin(20, 4);
  pinMode(pump,OUTPUT);
  pinMode(A5,INPUT);
  //delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  float sensor1_distance = (analogRead(A5)*100.0)/1023.0; //distance_finder(sensor1_trigPin,sensor1_echoPin);
  float sensor2_distance = 1.22; //distance_finder(sensor2_trigPin,sensor2_echoPin);
  float distance1 = tank1_empty - sensor1_distance;
  float distance2 = sensor1_distance; //tank2_empty - sensor2_distance;
  Serial.println("value " + String(sensor1_distance));
  // Print a message to the LCD.
  lcd.print("  MAIN TANK " + String(sensor1_distance) +"%");
  lcd.setCursor(0, 1);
  lcd.print("  ");
  lcd.setCursor(0, 2);
  lcd.print("   ");
  lcd.setCursor(0, 3);
  lcd.print("  ");
  delay(100);


  /*
//utility supply monitor
if(distance1 <= 90.3){
  if(utility_supply_available){
    digitalWrite(selonoid, HIGH);
  }else{
    if(distance1 < 60){
      digitalWrite(selonoid, LOW);
      //send 2-3 sms to request water
    }
  }
}*/

//display tanks

//pump monitor
 bool pump_state1 = true;
 bool pump_state2 = false;
  if(distance2 <= 90.3){
    if(distance2 <= 75 and pump_state1){
      pump_state2 = true;
      digitalWrite(pump, HIGH);
      Serial.println("Pump on");
    }
    if(distance2 > 89.00 and pump_state2){
      pump_state1 = false;
      digitalWrite(pump, LOW);
      Serial.println("Pump off");
    }
  }else{
    digitalWrite(pump, LOW);
    Serial.println("Pump off");
  }



  
}

float distance_finder(int  trigeger_pin, int echo_pin){
// Clears the trigPin
  digitalWrite(trigeger_pin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigeger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigeger_pin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echo_pin, HIGH);
  // Calculating the distance
  float distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance: ");
  //Serial.println(distance);
  return distance;
}
