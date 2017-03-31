
int pwmPin1 = 3; 
int pwmPin2 = 5;
int pwmPin3 = 6;
int pwmPin4 = 9;

int irPin = 10;
int incomingByte = 0;

int statusPin1 = 2;
int statusPin2 = 4;

void setup() {
  
  /* Initialize Serial at a 9600 baud rate */
  Serial.begin(9600);
  
  /* Configure PWM pins */
  pinMode(pwmPin1, OUTPUT);
  pinMode(pwmPin2, OUTPUT);
  pinMode(pwmPin3, OUTPUT);
  pinMode(pwmPin4, OUTPUT);
  
  pinMode(statusPin1, INPUT);
  pinMode(statusPin2, INPUT);
  
  /* Configure IR range finders */
  pinMode(irPin, INPUT);

}

void loop() {
    
    setMotor(1, 90);
    setMotor(2, 90);
    
    /*digitalWrite(pwmPin1, LOW);
    digitalWrite(pwmPin2, HIGH);
    digitalWrite(pwmPin3, LOW);
    digitalWrite(pwmPin4, HIGH);*/
    
    int stat = digitalRead(statusPin1);
    Serial.println(stat);
    
    stat = digitalRead(statusPin2);
    Serial.println(stat);

}

/* Read IR value of specified pin */
void readIR(int pin) {
  
  int val = analogRead(pin);
  getDistance(val);
}

/* 4 + 1023/Value */
float getDistance(int val) {
  
  float dist;
  //dist = 4 + 5 * 1023.0/(float)val; 
  dist = 12343.85 * pow(val, -1.15);
  Serial.println(dist);
  return dist;
}

/* Handles receiving serial communication */
void recvSerial() {
  
    if (Serial.available() > 0) {       
        incomingByte = Serial.read();
        Serial.print("received: ");
        Serial.println(incomingByte, DEC);
    }
}

/* Function to drive given PWM pin given value */
void setMotor(int motor, int value) {
  
  /* Map the value to 0 - 255 */
  value = map(value,-100,100,0,255);
  
  Serial.println(value);
  
  int forwardPin;
  int reversePin;
  
  /* Motor 1 is left */
  if(motor == 1) {
    forwardPin = pwmPin1;
    reversePin = pwmPin2;
  }
  else if (motor == 2) {
    forwardPin = pwmPin3;
    reversePin = pwmPin4;
  }
  
  if(value < 0) {
    analogWrite(forwardPin, 0);
    analogWrite(reversePin, value);
  }
  else {
    analogWrite(reversePin, 0);
    analogWrite(forwardPin, value);
  }
}

