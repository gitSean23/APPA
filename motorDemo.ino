
//int ledPin = 2;
int speedPin = 5;
int directionPin = 4; 
int directionPin2 = 3; 
int motorSpeedPin = 255;
int DELAY = 500;


void setup() 
{
  // put your setup code here, to run once:

  pinMode(speedPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(directionPin2, OUTPUT);
  //pinMode(ledPin, OUTPUT);

  Serial.begin(96000);
}

void loop() 
{
  // put your main code here, to run repeatedly:

  /*digitalWrite(ledPin, HIGH);
  delay(DELAY);
  digitalWrite(ledPin, LOW);*/
  digitalWrite(directionPin, HIGH);
  digitalWrite(directionPin2, LOW);

  analogWrite(speedPin, motorSpeedPin);
  //digitalWrite(speedPin, HIGH);

}
