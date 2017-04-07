
const Motor* leftMotor = new Motor(PWM_PIN_3, PWM_PIN_5);
const Motor* rightMotor = new Motor(PWM_PIN_6, PWM_PIN_9);

void setup() {
  
  /* Initialize Serial at a 115200 baud rate */
  Serial.begin(11500);
  
  /* Configure IR range finders */
  pinMode(irPin, INPUT);

}

void loop() {
    
    /* Check if serial data is available */
    if (Serial.available() > 0) {       
        byte packet_type = Serial.read();
        
        /* Determine the length of the incoming packet */
        byte packet_length = HARDWARE_MAP[packet_type];
   
        /* Create a array to store the incoming message */
        byte packet[packet_length];
        
        /* Receive the rest of the packet */
        for(int i = 0; i < packet_length; i++) {
          packet[i] = Serial.read();
        }
        
        /* Handle the packet appropriately */
        switch(packet_type) {
          /* Left Motor */
          case 1:
            setMotor(1 ,packet[0]);
            break;
          /* Right Motor */
          case 2:
            setMotor(2 ,packet[0]);
            break;
          default:
            break;
        } /* End handle packet type */
    } /* End Receive Serial Data */
} /* End while loop */

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
  return dist;
}

/* Function to drive given PWM pin given value */
/* 0 - 127 is negative, 127-255 is positive */
void setMotor(int motor, byte value) {
  
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
  
  /* Drive Backwards */
  if(value < 127) {
    /* Map the value to 0 - 255 */
    value = map(value,127,0,0,255);
    analogWrite(forwardPin, 0);
    analogWrite(reversePin, value);
  }
  /* Drive Forwards */
  else {
    /* Map the value to 0 - 255 */
    value = map(value,128,255,0,255);
    analogWrite(reversePin, 0);
    analogWrite(forwardPin, value);
  }
}

