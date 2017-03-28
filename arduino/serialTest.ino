
int pwmPin1 = 3; 
int pwmPin2 = 5;
int pwmPin3 = 6;
int pwmPin4 = 9;

int irPin = 10;
int incomingByte = 0;


void setup() {
  
  /* Initialize Serial at a 9600 baud rate */
  Serial.begin(9600);
  
  /* Configure PWM pins */
  pinMode(pwmPin1, OUTPUT);
  pinMode(pwmPin2, OUTPUT);
  pinMode(pwmPin3, OUTPUT);
  pinMode(pwmPin4, OUTPUT);
  
  /* Configure IR range finders */
  pinMode(irPin, INPUT);

}

void loop() {
    
    

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
void writePWM(int pin, float value) {
  
  analogWrite(pin, value);
}

