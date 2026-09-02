const int EnA=5;
const int In1=7;
const int In2=6;
const int In3=4;
const int In4=2;
const int EnB=3;

const int pingPin=8;

void setup() {
  Serial.begin(9600);

  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(EnA, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(EnB, OUTPUT);
}

void loop() {
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  analogWrite(EnA, 0);

  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  analogWrite(EnB, 0);

  // establish variables for duration of the ping, 
  // and the distance result centimetres:
  long duration, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // Change the pin mode, as we will now read in on this pin  
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimetres(duration);
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();  
  delay(100);
}

long microsecondsToCentimetres(long microseconds)
{
  return microseconds / 29 / 2;
}
