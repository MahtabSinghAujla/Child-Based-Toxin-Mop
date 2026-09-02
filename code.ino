const int EnA=11;
const int EnB=10;

const int S3=2;
const int S2=3;
const int OUT=4;

const int pingPin=8;

void setup() {
  Serial.begin(9600);

  pinMode(EnA, OUTPUT);
  pinMode(EnB, OUTPUT);

  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
}

void loop() {
  //right motor
  analogWrite(EnA, 0);
  //left motor
  analogWrite(EnB, 0);

  long duration, cm;

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

  //record and print time
  cm = microsecondsToCentimetres(duration);  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();  

  //red
  digitalWrite(S2,LOW);
  digitalWrite(S2,LOW);
  Serial.print('R');
  Serial.print(pulseIn(OUT,LOW));
  delay(200);
  //green
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  Serial.print('G');
  Serial.print(pulseIn(OUT,LOW));
  delay(200);
  //blue
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  Serial.print('B');
  Serial.print(pulseIn(OUT,LOW));
  delay(200);
  
  Serial.println();
}

long microsecondsToCentimetres(long microseconds)
{
  return microseconds / 29 / 2;
}
