/*

Veli Bayar
Pupa Robot 
v1.0
  
*/

#define LEFT_ENCODER 0  // Left encoder assigned Interrupt0 on D3 pin
#define RIGHT_ENCODER 1 // Right encoder assigned Interrupt1 on D2 pin

#define LEFT_INFRARED 5 // left infrared sensor assigned to D5 pin
#define MIDDLE_INFRARED 6 // middle infrared sensor assigned to D6 pin
#define RIGHT_INFRARED 7 // right infrared sensor assigned to D7 pin

#define LOOP_FREQUENCY 500 // Loop frequency in milliseconds

/* Encoder values */
long leftEncoderValue = 0; // value in revolution count
long rightEncoderValue = 0; // value in revolution count

/* Infrared sensor values */
long rightInfraredValue = 0;
long middleInfraredValue = 0;
long leftInfraredValue = 0;

/*
  rPiData[0] > leftEncoder value : LOOP_FREQUENCY (milliseconds) / leftEncoderValue
  rPiData[1] > rightEncoder value : LOOP_FREQUENCY (milliseconds) / rightEncoderValue
  rPiData[2] > rightInfrared value
  rPiData[3] > middleInfrared value
  rPiData[4] > rightInfrared value
  
*/
long rPiData[5] = {0,0,0,0,0};

void setup()
{
  Serial.begin(9600); // init serial port                            
  attachInterrupt(LEFT_ENCODER, readLeftEncoder, CHANGE); // init left encoder interrupt
  attachInterrupt(RIGHT_ENCODER, readRightEncoder, CHANGE); // init right encoder interrupt
  pinMode(LEFT_INFRARED, INPUT);
  pinMode(MIDDLE_INFRARED, INPUT);
  pinMode(RIGHT_INFRARED, INPUT);
}

void loop()
{
  static unsigned long timer = 0; // timer variable

  if(millis() - timer > LOOP_FREQUENCY)
  {                   
    
    rPiData[0] = leftEncoderValue;
    rPiData[1] = rightEncoderValue;
    rPiData[2] = readInfrared(LEFT_INFRARED);
    rPiData[3] = readInfrared(MIDDLE_INFRARED);
    rPiData[4] = readInfrared(RIGHT_INFRARED);
    
    for (int i = 0; i < 5; i++)
    {
      //Serial.write(rPiData[i]);
      Serial.print(rPiData[i]);
      Serial.print(" ");     
    }
    
    Serial.println();
    
    leftEncoderValue = 0;                 
    rightEncoderValue = 0;
    timer = millis();
    
    
    /*Test code for serial data format*/
//    Serial.print(rPiData[0]);
//    Serial.print(" ");    
//    Serial.print(rPiData[1]);
//    Serial.print(" "); 
//    Serial.print(rPiData[2]);
//    Serial.print(" ");
//    Serial.print(rPiData[3]);
//    Serial.print(" ");
//    Serial.print(rPiData[4]);
//    Serial.println();

     /*Test code pwm for motor speeds */
//    analogWrite(9,50);
//    analogWrite(10,50);
     
  }

}

int readInfrared(int pinNumber)
{
  int rawSensorValue = digitalRead(pinNumber);
  
  if(rawSensorValue == HIGH)
  {
    return LOW;
  }
  else
  {
    return HIGH;
  }
}

void readLeftEncoder()
{
  leftEncoderValue++;
}

void readRightEncoder()
{
  rightEncoderValue++;
}


