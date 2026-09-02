const int EnA=11;
const int EnB=10;

const int pingPin=8;

void setup() {
  Serial.begin(9600);

  pinMode(EnA, OUTPUT);
  pinMode(EnB, OUTPUT);
}

void loop() {
  //right motor
  analogWrite(EnA, 50);
  //left motor
  analogWrite(EnB, 200);

  long duration, cm;

  /*
  //change to trig
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  //pinging
  delayMicroseconds(5);
  //signal off
  digitalWrite(pingPin, LOW);

  //change to echo  
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  cm = microsecondsToCentimetres(duration);  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();  
  delay(100);
  */
}

long microsecondsToCentimetres(long microseconds)
{
  return microseconds / 29 / 2;
}
