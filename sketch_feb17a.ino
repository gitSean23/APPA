int trigPin = 9;
int echoPin = 10;

long duration;
double distance;

void setup() {
  // put your setup code here, to run once:

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedley:

  digitalWrite(trigPin, LOW);
  delay(50);

  digitalWrite(trigPin, HIGH);
  delay(50);
  digitalWrite(trigPin,LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

}
