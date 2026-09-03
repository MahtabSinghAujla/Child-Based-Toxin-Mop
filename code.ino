#include <QTRSensors.h>


QTRSensors qtr;
const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];

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

  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3}, SensorCount);

  Serial.begin(9600);
}

void loop() {
  //right motor
  analogWrite(EnA, 100);
  //left motor
  analogWrite(EnB, 100);

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
  Serial.println("cm");
  
  // white raw values 23 28 23
  // black raw values 165 216 164

  int green[] = {175, 225, 174};
  bool greenFlag[] = {false, false, false};

  int purple[] = {221, 182, 220};
  bool purpleFlag[] = {false, false, false};

  int yellow[] = {195, 247, 195};
  bool yellowFlag[] = {false, false, false};

  //red
  digitalWrite(S2,LOW);
  digitalWrite(S2,LOW);
  Serial.print(" R");
  int redVar=pulseIn(OUT,LOW);
  redVar=map(redVar,23,165,255,0);
  Serial.print(redVar);

  //comparing to colours R values
  if (abs(redVar-green[0])<10) {
    greenFlag[0]=true;
  } else if (abs(redVar-purple[0])<10) {
    purpleFlag[0]=true;
  } else if (abs(redVar-yellow[0])<10) {
    yellowFlag[0]=true;
  }
  delay(100);

  //green
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  Serial.print(" G");
  int greenVar=pulseIn(OUT,LOW);
  greenVar=map(greenVar,28,216,255,0);
  Serial.print(greenVar);

  //comparing to colours G values
  if (abs(greenVar-green[1])<10) {
    greenFlag[1]=true;
  } else if (abs(greenVar-purple[1])<10) {
    purpleFlag[1]=true;
  } else if (abs(greenVar-yellow[1])<10) {
    yellowFlag[1]=true;
  }
  delay(100);

  //blue
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  Serial.print(" B");
  int blueVar=pulseIn(OUT,LOW);
  blueVar=map(blueVar,23,164,255,0);
  Serial.println(blueVar);

  //comparing to colours B values
  if (abs(blueVar-green[2])<10) {
    greenFlag[2]=true;
  } else if (abs(blueVar-purple[2])<10) {
    purpleFlag[2]=true;
  } else if (abs(blueVar-yellow[2])<10) {
    yellowFlag[2]=true;
  }
  
  //colour determination and printing
  if (greenFlag[0] && greenFlag[1] && greenFlag[2]){
    Serial.println("GREEN");
  } else if (purpleFlag[0] && purpleFlag[1] && purpleFlag[2]) {
    Serial.println("PURPLE");
  } else if (yellowFlag[0] && yellowFlag[1] && yellowFlag[2]) {
    Serial.println("YELLOW");
  }

  greenFlag[0] = false; greenFlag[1] = false; greenFlag[2] = false;
  purpleFlag[0] = false; purpleFlag[1] = false; purpleFlag[2] = false;
  yellowFlag[0] = false; yellowFlag[1] = false; yellowFlag[2] = false;

  //line array
  qtr.read(sensorValues);
  int corrVal = 0;
  for (uint8_t i = 0; i < SensorCount; i++) {
    if (i==0) {
      corrVal+=(2*sensorValues[i]);
    } else if (i==1) {
      corrVal+=sensorValues[i];
    } else if (i==2) {
      corrVal-=sensorValues[i];
    } else if (i==3) {
      corrVal-=(2*sensorValues[i]);
    }
  }
  Serial.print("corrVal ");
  Serial.println(corrVal);
  
  Serial.println();
  delay(100);
}

long microsecondsToCentimetres(long microseconds) { return microseconds / 29 / 2; }
