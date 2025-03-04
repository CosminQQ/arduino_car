
const int ena = 9;
const int in1 = 8;
const int in2 = 7;
const int in3 = 5;
const int in4 = 4;
const int enb = 3;

const int vrxPin = A0;
const int vryPin = A1;
const int swPin = 2;  


const int maxPWM = 170;


const int centerValue = 511; 
const int errorMargin = 50; 

void setup() {
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enb, OUTPUT);
 
  pinMode(swPin, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {

  int vrxValue = analogRead(vrxPin); 
  int vryValue = analogRead(vryPin); 
  int swValue = digitalRead(swPin);  


  Serial.print("VRx: ");
  Serial.print(vrxValue);
  Serial.print(" | VRy: ");
  Serial.print(vryValue);
  Serial.print(" | SW: ");
  Serial.println(swValue);


  if (vryValue > centerValue + errorMargin && 
      abs(vrxValue - centerValue) <= errorMargin) {

    moveForward();
  } else if (vrxValue > centerValue + errorMargin &&
             abs(vryValue - centerValue) <= errorMargin) {

    moveRight();
  } else if (vryValue < centerValue - errorMargin &&
             abs(vrxValue - centerValue) <= errorMargin) {

    moveBackward();
  } else if (vrxValue < centerValue - errorMargin &&
             abs(vryValue - centerValue) <= errorMargin) {

    moveLeft();
  } else if (abs(vrxValue - centerValue) <= errorMargin &&
             abs(vryValue - centerValue) <= errorMargin) {

    stopMotors();
  }

  delay(50);
}


void moveForward() {
  analogWrite(ena, maxPWM); 
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enb, maxPWM); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  Serial.println("Moving Forward");
}


void moveBackward() {
  analogWrite(ena, maxPWM); 
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  analogWrite(enb, maxPWM);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  Serial.println("Moving Backward");
}

// Function to move left
void moveLeft() {
  analogWrite(ena, maxPWM); 
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  analogWrite(enb, maxPWM); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  Serial.println("Turning Left");
}

void moveRight() {
  analogWrite(ena, maxPWM); 
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enb, maxPWM); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  Serial.println("Turning Right");
}

void stopMotors() {
  analogWrite(ena, 0);
  analogWrite(enb, 0); 
  Serial.println("Standing Still");
}
