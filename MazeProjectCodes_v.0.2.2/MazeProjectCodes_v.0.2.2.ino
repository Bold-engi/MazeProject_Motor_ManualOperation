/***********************************************************************

  MazeProject version v0.2.2

  Contributors:
    - Yumo Liu
    - Shi Zhao

  Updates on 2 Dec 2021:
    - Fixed code errors in the beta version of the code, now motor will
      work as expected.
    - Simplified the monitor menu.
    - Simplified the loop() function.
    - Now motor will spin a full revolution in either clockwise or
      anticlockwise directions.

  Project Description:
    This project allows user to control the rotation of a stepper motor.
    
    By typing commands in the serial monitor, user is able to let the 
    motor spin a full revolution in either clockwise or anticlockwise
    direction.

  Materials:
    - 103H5205-0410 stepper motor (Bipolar winding, datasheet see https://docs.rs-online.com/9c79/0900766b8141d4fe.pdf)
    - Pmod DHB1 motor driver (user manual see https://digilent.com/reference/_media/reference/pmod/pmoddhb1/pmoddhb1_rm.pdf)
    - Arduino Mega 2560 Rev3

***********************************************************************/

// Pin definitions
// for one driver and one motor
const int EN1 = 2;
const int EN2 = 5;
const int DIR1 = 3;
const int DIR2 = 6;

// Setting global variable
boolean start = true;

void setup() {
  
  // Initialize the serial monitor
  Serial.begin(9600);
  
  // Pin configurations
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(DIR2, OUTPUT);

  // User interference
  Serial.println("'t' for clockwise, 'f' for anticlockwise");
}

void loop() {
  
  // Parameter definition
  boolean en    = true;

  // Activate the driver
  digitalWrite(EN1, en);
  digitalWrite(EN2, en);
  
  if (Serial.available()){ // Check input availability
    char dir = Serial.read();
    switch (dir){
      case 't':
        if (::start == true){
          pRev();
        }
        break;

      case 'f':
        if (::start == true){
          nRev();
        }
        break;
    }
  }
  
}

void pRev(){ // p stands for positive

  int steps = 50;
  
  for (int i=0; i<steps; i++){
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, LOW);
    delay(3);
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, HIGH);
    delay(3);
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, HIGH);
    delay(3);
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, LOW);
    delay(3);
  }

  ::start = false; // Motor stops after one revolution
}

void nRev(){ // n stands for negative
  
  int steps = 50;
  
  for (int i=0; i<steps; i++){
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, LOW);
    delay(3);
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, HIGH);
    delay(3);
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, HIGH);
    delay(3);
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, LOW);
    delay(3);
  }

  ::start = false; // Motor stops after one revolution
}
