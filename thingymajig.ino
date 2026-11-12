#include <QTRSensors.h>


QTRSensors qtr;
const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];

const int EnA=11;
const int EnB=10;

const int S3=2;
const int S2=3;
const int OUT=4;

const int trig=13;
const int echo=12;

long cm;

void setup() {
Serial.begin(9600);
  Serial.println("Start");

  pinMode(EnA, OUTPUT);
  pinMode(EnB, OUTPUT);

  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3}, SensorCount);
  for (uint8_t i = 0; i < 250; i++)
  {
    qtr.calibrate();
    delay(20);
  }

  Serial.println("Calibrated");
  
}

void loop() {
  
  // white raw values 22 25 20
  // black raw values 121 146 115

  int green[] = {266, 236, 266};
  bool greenFlag[] = {false, false, false};

  int purple[] = {256, 145, 252};
  bool purpleFlag[] = {false, false, false};

  int yellow[] = {290, 261, 287};
  bool yellowFlag[] = {false, false, false};

  //red
  digitalWrite(S2,LOW);
  digitalWrite(S2,LOW);
  //Serial.print(" R");
  int redVar=pulseIn(OUT,LOW);
  redVar=map(redVar,22,121,255,0);
  //Serial.print(redVar);

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
  //Serial.print(" G");
  int greenVar=pulseIn(OUT,LOW);
  greenVar=map(greenVar,25,146,255,0);
  //Serial.print(greenVar);

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
  //Serial.print(" B");
  int blueVar=pulseIn(OUT,LOW);
  blueVar=map(blueVar,20,115,255,0);
  //Serial.println(blueVar);

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
    //damsel();
  } else if (purpleFlag[0] && purpleFlag[1] && purpleFlag[2]) {
    Serial.println("PURPLE");
    //rward();
  } else if (yellowFlag[0] && yellowFlag[1] && yellowFlag[2]) {
    Serial.println("YELLOW");
    //lward(); 
  }

  greenFlag[0] = false; greenFlag[1] = false; greenFlag[2] = false;
  purpleFlag[0] = false; purpleFlag[1] = false; purpleFlag[2] = false;
  yellowFlag[0] = false; yellowFlag[1] = false; yellowFlag[2] = false;

  int16_t position = qtr.readLineBlack(sensorValues);
  //Serial.println(position);

  int16_t corrVal = 0.01*position;
  int16_t m1Speed = 75 + corrVal;
  int16_t m2Speed = 75 - corrVal;
  Serial.println(corrVal);
  
  if (m1Speed < 0) { m1Speed = 0; }
  if (m2Speed < 0) { m2Speed = 0; }
  
  analogWrite(EnA, m1Speed);
  analogWrite(EnB, m2Speed);

  delay(100);
}

long microsecondsToCentimetres(long microseconds) { return microseconds / 29 / 2; }

/*void decodeDance (seqRaw) {
  char seq[64];
  seqRaw.toCharArray(seq, seqRaw.length());
  for (int i=0;i<seq.length();i++) {
    switch(seq[i]) {
      case 'F':
        fward();
        break;
      case 'B':
        bward();
        break;
      case 'L':
        lward();
        break;
      case 'R':
        rward();
        break;
    }
  }
}*/

void fward () {
  //right motor
  analogWrite(EnA, 100);
  //left motor
  analogWrite(EnB, 100);
  delay(500);
  analogWrite(EnA, 0);
  analogWrite(EnB, 0);
}

void bward () {
  //right motor
  analogWrite(EnA, 0);
  //left motor
  analogWrite(EnB, 255);
  delay(2000);
  //right motor
  analogWrite(EnA, 100);
  //left motor
  analogWrite(EnB, 100);
  delay(500);
  analogWrite(EnA, 0);
  analogWrite(EnB, 0);
}

void lward () {
  //right motor
  analogWrite(EnA, 0);
  //left motor
  analogWrite(EnB, 255);
  delay(500);
   //right motor
  analogWrite(EnA, 100);
  //left motor
  analogWrite(EnB, 100);
  delay(500);
  analogWrite(EnA, 0);
  analogWrite(EnB, 0);
}

void rward () {
  //right motor
  analogWrite(EnA, 255);
  //left motor
  analogWrite(EnB, 0);
  delay(500);
   //right motor
  analogWrite(EnA, 100);
  //left motor
  analogWrite(EnB, 100);
  delay(500);
  analogWrite(EnA, 0);
  analogWrite(EnB, 0);
}

void damsel () {
  
  int range[90];
  int pos;
  long duration;
  for (int i=0;i<90;i++) {
    analogWrite(EnA, 50);
    analogWrite(EnB, 0);
    delay(280);
    analogWrite(EnA, 0);
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(5);
    digitalWrite(trig, LOW);

    duration = pulseIn(echo, HIGH);

    //record and print time
    cm = microsecondsToCentimetres(duration);  
    //Serial.print(cm);
    //Serial.println("cm");
    range[i]=cm;
  }
  for (int j=1;j<90;j++) {
    if (range[j]>range[j-1]) {
      pos=j-1;
    }
    else if (range[j]<range[j-1]) {
      pos=j;
    }
  }
  
}
