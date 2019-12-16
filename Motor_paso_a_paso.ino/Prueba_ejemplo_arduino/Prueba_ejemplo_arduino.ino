int motorPins[] = {3, 4, 5, 6};
int count = 0;
int count2 = 0;
int delayTime = 500;
int val = 0;


void setup() {
  for (count = 0; count < 4; count++) {
    pinMode(motorPins[count], OUTPUT);
  }
}

void moveForward() {
  if ((count2 == 0) || (count2 == 1)) {
    count2 = 16;
  }
  count2>>=1;
  for (count = 3; count >= 0; count--) {
    digitalWrite(motorPins[count], count2>>count&0x01);
  }
  delay(delayTime);
}

void moveBackward() {
  if ((count2 == 0) || (count2 == 1)) {
    count2 = 16;
  }
  count2>>=1;
  for (count = 3; count >= 0; count--) {
    digitalWrite(motorPins[3 - count], !(count2>>count&0x01));
  }
  delay(delayTime);
}

void loop() {
  //val = analogRead(0);
  val=888;
  if (val > 540) {
    // move faster the higher the value from the potentiometer
    delayTime = 2048 - 1024 * val / 512 + 1; 
    moveForward();
  } else if (val < 480) {
    // move faster the lower the value from the potentiometer
    delayTime = 1024 * val / 512 + 1; 
    moveBackward();
  } else {
    delayTime = 1024;
  }
}
