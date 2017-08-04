int switchPin = 2; // switch input
int motor1Pin1 = 5; // pin 2 on L293D
int motor1Pin2 = 4; // pin 7 on L293D
int enablePin = 6; // pin 1 on L293D
int clol =20;
int clor=20;
#define duck
#define but
#define old
const int TriggerPin = 8; //Trig pin
const int EchoPin = 9; //Echo pin
long Duration = 0;
const int TriggerPin2 = 10; //Trig pin
const int EchoPin2 = 11; //Echo pin
long Duration2 = 0;
int D;
int i;
int l=0;
int r=0;

unsigned long previousMillis = 0; 
const long interval = 1000;        
int buttonPress = 0;
int b;
boolean cur;
boolean pre;
int pres=0;
const int buttonPin = 12;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
int buttonState = 0;      

void setup() {
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT);  
    Serial.begin(9600);
    // set all the other pins you're using as outputs:
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(enablePin, OUTPUT);
   // digitalWrite(enablePin, HIGH);
#if defined old2
    digitalWrite(enablePin, HIGH);  
#endif
    pinMode(TriggerPin,OUTPUT); // Trigger is an output pin
    pinMode(EchoPin,INPUT); // Echo is an input pin
    pinMode(TriggerPin2,OUTPUT); // Trigger is an output pin
    pinMode(EchoPin2,INPUT); // Echo is an input pin
    #if defined init
    i=2;
    #endif
}

void loop() {
 int input= Serial.read();
 #if defined old
digitalWrite(TriggerPin, LOW);
delayMicroseconds(2);
digitalWrite(TriggerPin, HIGH); // Trigger pin to HIGH
delayMicroseconds(10); // 10us high
digitalWrite(TriggerPin, LOW); // Trigger pin to HIGH
Duration = pulseIn(EchoPin,HIGH); // Waits for the echo pin to get high
// returns the Duration in microseconds
long dis1 = Distance(Duration); // Use function to calculate the distance
Serial.print("Duration = ");
Serial.print(Duration);
Serial.print("   ");
Serial.print("Distance = "); // Output to serial
Serial.print(dis1);
Serial.println(" mm");

digitalWrite(TriggerPin2, LOW);
delayMicroseconds(2);
digitalWrite(TriggerPin2, HIGH); // Trigger pin to HIGH
delayMicroseconds(10); // 10us high
digitalWrite(TriggerPin2, LOW); // Trigger pin to HIGH
Duration2 = pulseIn(EchoPin2,HIGH); // Waits for the echo pin to get high
// returns the Duration in microseconds
long dis2 = Distance(Duration2); // Use function to calculate the distance
Serial.print("Duration2 = ");
Serial.print(Duration2);
Serial.print("   ");
Serial.print("Distance2 = "); // Output to serial
Serial.print(dis2);
Serial.println(" mm");

         if ( Duration == 0 ) {
            delay(100);
            pinMode(EchoPin, OUTPUT);
            digitalWrite(EchoPin, LOW);
            delay(100);
            pinMode(EchoPin, INPUT);
        }
         if ( Duration2 == 0 ) {
            delay(100);
            pinMode(EchoPin2, OUTPUT);
            digitalWrite(EchoPin2, LOW);
            delay(100);
            pinMode(EchoPin2, INPUT);
        }
        if (D==1) {
        digitalWrite(motor1Pin1, LOW); 
        digitalWrite(motor1Pin2, HIGH);
        Serial.println("D1 alone");
        }
        if (D==2){
        digitalWrite(motor1Pin1, HIGH); 
        digitalWrite(motor1Pin2, LOW);
        Serial.println("D2 alone");
        }
        if ( dis1>0 & dis1 < clor ) {
        digitalWrite(motor1Pin1, LOW); 
        digitalWrite(motor1Pin2, HIGH);
        Serial.println("dis1");
        D=1;
        //#if defined init
       // i=3;
        //Serial.println(i);//when not d init it still i=2
        //#endif
        if (b==1){
        l++;
        }//if b=1
        Serial.println("l");
        Serial.println(l);
      }//if dis1 0 clor
      if( dis2 > 0 & dis2 < clol ) {
        digitalWrite(motor1Pin1, HIGH); 
        digitalWrite(motor1Pin2, LOW);
        Serial.println("dis2");
        D=2;
        #if defined init
        i=3;
        Serial.println(i);
        #endif
        if(b==1){
        r++;
       }
    }//if dis2
    #if defined duck
    if (l==4 ){
    Serial.println("l=2");
 //  digitalWrite(motor1Pin1, LOW); 
   //digitalWrite(motor1Pin2, HIGH);
   // delay(1000);
    digitalWrite(enablePin, LOW);
    delay(10000);
    digitalWrite(enablePin, HIGH); 
    l=0;
    r=0;
    } 
    #endif//duck
    #endif//old

#if defined but
   unsigned long currentMillis = millis();//QA
  //if (digitalRead.available()){}
  //if(currentMillis - previousMillis >= interval) //  I1
  // previousMillis = currentMillis;
    cur = digitalRead(buttonPin);
    if(pre==LOW && cur==HIGH){
    digitalWrite(ledPin, HIGH);
    digitalWrite(enablePin, HIGH);
    b=1;
    pres++;
    l=0;
  }//but first press
  if(pre==LOW && cur==HIGH && pres==2){//pres=2 indicate its secound press which is to stop taking data
    digitalWrite(ledPin, LOW);
    b=0;
    pres=0; 
    digitalWrite(enablePin, LOW);  
   //Serial.print("2");
   }
   #endif //but
}//loop

long Distance(long time)
{
// Calculates the Distance in mm
// ((time)*(Speed of sound))/ toward and backward of object) * 10

long DistanceCalc; // Calculation variable
DistanceCalc = ((time /2.9) / 2); // Actual calculation in mm
//DistanceCalc = time / 74 / 2; // Actual calculation in inches
return DistanceCalc; // return calculated value
}

