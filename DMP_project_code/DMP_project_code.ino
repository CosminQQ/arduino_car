// Pin definitions
const int ena = 9;
const int in1 = 8;
const int in2 = 7;
const int in3 = 5;
const int in4 = 4;
const int enb = 3;

const int vrxPin = A0; // Joystick VRx
const int vryPin = A1; // Joystick VRy
const int swPin = 2;   // Joystick button

// Maximum PWM value to ensure motors receive no more than 6V
const int maxPWM = 170;

// Joystick center and error margin
const int centerValue = 511; // Approximate center value for VRx and VRy
const int errorMargin = 50;  // Allowable error margin for center

void setup() {
  // Motor pins
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enb, OUTPUT);

  // Joystick button pin
  pinMode(swPin, INPUT_PULLUP);

  // Initialize Serial Monitor for debugging
  Serial.begin(9600);
}

void loop() {
  // Read joystick values
  int vrxValue = analogRead(vrxPin); // Horizontal
  int vryValue = analogRead(vryPin); // Vertical
  int swValue = digitalRead(swPin);  // Button state

  // Print joystick values (for debugging)
  Serial.print("VRx: ");
  Serial.print(vrxValue);
  Serial.print(" | VRy: ");
  Serial.print(vryValue);
  Serial.print(" | SW: ");
  Serial.println(swValue);

  // Joystick conditions for directions
  if (vryValue > centerValue + errorMargin && 
      abs(vrxValue - centerValue) <= errorMargin) {
    // Move forward
    moveForward();
  } else if (vrxValue > centerValue + errorMargin &&
             abs(vryValue - centerValue) <= errorMargin) {
    // Move right
    moveRight();
  } else if (vryValue < centerValue - errorMargin &&
             abs(vrxValue - centerValue) <= errorMargin) {
    // Move backward
    moveBackward();
  } else if (vrxValue < centerValue - errorMargin &&
             abs(vryValue - centerValue) <= errorMargin) {
    // Move left
    moveLeft();
  } else if (abs(vrxValue - centerValue) <= errorMargin &&
             abs(vryValue - centerValue) <= errorMargin) {
    // Stand still
    stopMotors();
  }

  delay(50);
}

// Function to move forward
void moveForward() {
  analogWrite(ena, maxPWM); // Motor A full speed
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enb, maxPWM); // Motor B full speed
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  Serial.println("Moving Forward");
}

// Function to move backward
void moveBackward() {
  analogWrite(ena, maxPWM); // Motor A full speed
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  analogWrite(enb, maxPWM); // Motor B full speed
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  Serial.println("Moving Backward");
}

// Function to move left
void moveLeft() {
  analogWrite(ena, maxPWM); // Motor A full speed
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  analogWrite(enb, maxPWM); // Motor B full speed
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  Serial.println("Turning Left");
}

// Function to move right
void moveRight() {
  analogWrite(ena, maxPWM); // Motor A full speed
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enb, maxPWM); // Motor B full speed
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  Serial.println("Turning Right");
}

// Function to stop motors
void stopMotors() {
  analogWrite(ena, 0); // Stop Motor A
  analogWrite(enb, 0); // Stop Motor B
  Serial.println("Standing Still");
}
