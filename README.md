Joystick-Controlled Motors

Introduction
This project uses an Arduino to control two motors via an L298N dual H-bridge motor driver, using a joystick as the input. The joystick provides analog X and Y-axis values (0-1024) and a digital button input. The motors are controlled to move forward, backward, left, or right based on joystick movements.

Components
1.	Joystick:
•	X-axis (VRx): Outputs an analog value between 0 (forward) and 1024 (backward).
•	Y-axis (VRy): Outputs an analog value between 0 (right) and 1024 (left).
•	Button (SW): Outputs digital values (0 when pressed, 1 when released).

2.	L298N Dual H-Bridge Motor Driver:
•	Controls two DC motors (Motor A and Motor B).
•	Allows for forward, backward, left, and right movement by managing motor direction and speed.

3.	Arduino Uno:
•	Reads joystick inputs.
•	Sends control signals to the L298N to drive the motors.

Circuit Connections:
L298N Motor Driver to Arduino and Motors:
•	ENA (Enable A): Connect to pin 9 (PWM pin on Arduino).
•	IN1: Connect to pin 8.
•	IN2: Connect to pin 7.
•	IN3: Connect to pin 5.
•	IN4: Connect to pin 4.
•	ENB (Enable B): Connect to pin 3 (PWM pin on Arduino).
•	Motor A: Connect to the L298N outputs for Motor A.
•	Motor B: Connect to the L298N outputs for Motor B.
•	Power:
o	Connect the 9V battery to the L298N motor driver’s power input.
o	The L298N will power the Arduino via the Vin pin.
Joystick to Arduino:
•	GND: Connect to Arduino GND.
•	5V: Connect to Arduino 5V.
•	VRx: Connect to A0 (analog input pin).
•	VRy: Connect to A1 (analog input pin).
•	SW: Connect to pin 2 (digital input pin with internal pull-up).

How the Joystick Works
•	The joystick provides two analog values for the X (VRx) and Y (VRy) axes, and a digital signal for the button (SW).
•	Values range from 0 to 1024:
o	X-Axis (VRx):
	0: Joystick pushed fully forward.
	1024: Joystick pushed fully backward.
o	Y-Axis (VRy):
	0: Joystick pushed fully right.
	1024: Joystick pushed fully left.

How the L298N H-Bridge Works
•	The L298N allows bidirectional control of two motors by varying the input signals.
•	Two inputs (IN1/IN2 for Motor A, IN3/IN4 for Motor B) determine the motor's direction:
 
•	ENA and ENB control motor speed using PWM signals.
Movement Processing:
In order to make the car stationary outside the 
Software Implementation
Features:
1.	Directional control of motors based on joystick input:
•	Forward
•	Backward
•	Left
•	Right
•	Stand Still
2.	Voltage limiting using PWM to ensure motors receive no more than 6V.
3.	Button (SW) functionality is available for future features.
 
Code Overview:
The program reads joystick values using analogRead() and determines the direction of motion by comparing them to predefined ranges. Based on the input, the motors are controlled through the L298N H-bridge using the following functions:
•	moveForward(): Drives both motors forward.
•	moveBackward(): Drives both motors backward.
•	moveLeft(): Turns left by driving motors in opposite directions.
•	moveRight(): Turns right by driving motors in opposite directions.
•	stopMotors(): Stops both motors.
The analogWrite() function is used to generate PWM signals to limit the voltage supplied to the motors. The maximum PWM value is capped at 170 to ensure the motors receive no more than 6V from the 9V power source.

Joystick Input Handling:
•	Reads joystick VRx and VRy values using analogRead().
•	Uses conditions to check the joystick position relative to centerValue, errorMargin, X and Y coordinates to determine movement direction.
•	If the joystick is within the dead zone (centered), motors stop.

Movement processing:
To account for slightly shifts for the center of the joystick (512,512) we account for a tolerance of 50 units therefore every input in 512+-50 units will be considered a stop signal and the car will stop.
The movement is given by the following table:
X	Y	X ? Y	Motor A	Motor B	Movement
>512	>512	>	BACKWARD	BACKWARD	BACKWARD
>512	>512	<	FORWARD	BACKWARD	LEFT
IN TOLERANCE	IN TOLERANCE	x	STOP	STOP	STATIONARY
<512	<512	>	BACKWARD	FORWARD	RIGHT
<512	<512	<	FORWARD	FORWARD	FORWARD

Improvements
•	Implement finer speed control based on how far the joystick is pushed.
•	Add debouncing for the joystick button (SW) to handle accidental presses.
•	Display real-time motor and joystick states on an LCD or an OLED for better feedback.





