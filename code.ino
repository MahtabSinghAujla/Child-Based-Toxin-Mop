const int In1 = 6;
const int In2 = 5;
const int EnA = 7; 

const int In3 = 4;
const int In4 = 3;
const int EnB = 2; 

void setup(){
  // All motor control pins are outputs
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);

  pinMode(EnA, OUTPUT); 
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(EnB, OUTPUT); 
  Serial.begin(9600);
}

void goStraight() {  //run both motors in the same direction
  // turn on motor A
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  analogWrite(EnA, 150);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  analogWrite(EnB, 150);
}

void loop(){
  goStraight();
}
