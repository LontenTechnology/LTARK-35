#define Trig 2             //GPIO2  (D9)
#define Echo 15            //GPIO15 (D10)
float distance;
float cm;

#define IN_1  0            // L9110S A-1A motors Left       GPIO0 (D8)
#define IN_2  4            // L9110S A-1B motors Left       GPIO4 (D4)
#define IN_3  13           // L9110S B-1A motors Right      GPIO13(D7)
#define IN_4  12           // L9110S B-2A motors Right      GPIO12(D6)
int speedCar =180;

//Function initialization
void setup() 
{
  Serial.begin(115200);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
}

//Principal function
void loop() 
{
    cm = GetDistance();
    if(cm <5){
        Backward();
    }
    else if(cm > 10 && cm <25){
        Forward();
    }
    else{
        Stop();
    }
}

float GetDistance()
{ // Send a low short pulse to Trig to trigger the ranging
  digitalWrite(Trig, LOW); //Send a low level to Trig
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  distance = pulseIn(Echo, HIGH) / 58.00;
  Serial.print("Distance = ");
  Serial.println(distance);//The serial output distance is converted into cm
  return distance;
}

void Forward(){
  digitalWrite(IN_1, LOW);
  analogWrite(IN_2, speedCar+10);
  analogWrite(IN_3, speedCar);
  digitalWrite(IN_4, LOW);
}

void Backward(){
  analogWrite(IN_1, speedCar);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, speedCar);
}

void Stop()
{
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
}

