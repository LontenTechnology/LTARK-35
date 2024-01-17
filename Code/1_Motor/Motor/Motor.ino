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
}
//Principal function
void loop()
{
  Forward();            //Car forward
  delay(2000);          
  Backward();           //Car back
  delay(2000);          
  TurnLeft();           //Car turnleft
  delay(2000);          
  TurnRight();          //Car turnright
  delay(2000);          
  Stop();               //Car stop
  delay(1000);          
}

void Forward(){
  digitalWrite(IN_1, LOW);
  analogWrite(IN_2, speedCar+10);//When the car cannot move straight forward or backward, the parameters can be modified to adjust it: 
                                //speedCar+10 has increased the speed by 10 units compared to the original speed, so the car can be adjusted to the right.
  analogWrite(IN_3, speedCar);
  digitalWrite(IN_4, LOW);
}

void Backward(){
  analogWrite(IN_1, speedCar);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, speedCar);
}

void TurnLeft(){
  analogWrite(IN_1, speedCar);
  digitalWrite(IN_2, LOW);
  analogWrite(IN_3, speedCar);
  digitalWrite(IN_4, LOW);
}

void TurnRight(){
  digitalWrite(IN_1, LOW);
  analogWrite(IN_2, speedCar);
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
