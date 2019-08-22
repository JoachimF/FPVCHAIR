// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

//#define DEBUG // uncomment to test - set serial baud rate to 115200


uint16_t x,y,rx,ry;
uint8_t b = 0b00000000; //digital pins 2 to 9; x ^= (1 << n); - toggles nth bit of x.  all other bits left alone.

byte pins[] = {15,16,14,10,7};
byte encoder0PinA = 8 ;
byte encoder0PinB = 9 ;

byte data[11];

uint8_t encoder0Pos = 0;
uint8_t encoder0PinALast = LOW;

uint8_t n0 = LOW;

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  Serial.begin(9600);           // start serial for output
  for (int i = 0; i < sizeof(pins); i++)
  {
    pinMode(pins[i], INPUT_PULLUP);
  }
  pinMode (encoder0PinA,INPUT_PULLUP);
  pinMode (encoder0PinB, INPUT_PULLUP); 
  #if defined(DEBUG)
    Serial.begin (115200);
  #endif
}

void loop() {
  x = analogRead(A0);
  x = map(x,290,762,0,1023);
  y = analogRead(A1);
  rx = analogRead(A2);
  ry = analogRead(A3);
  for (int i = 0; i < sizeof(pins); i++)
  {
    bool pin = !digitalRead(pins[i]);
    if (pin == 1)
    {
       b |= (1 << i);       // forces ith bit of b to be 1.  all other bits left alone.
    }
    else
    {
      b &= ~(1 << i);      // forces ith bit of b to be 0.  all other bits left alone.
    }
    //Serial.print(" Buttons : ");  
    //Serial.print(b);
    
  }
  n0 = !digitalRead(encoder0PinA);
  if ((encoder0PinALast == LOW) && (n0 == HIGH)) 
  {
    if (!digitalRead(encoder0PinB) == LOW) 
    {
      encoder0Pos--;
    } 
    else 
    {
      encoder0Pos++;
    }
   }
  encoder0PinALast = n0;
// DEBUG
#if defined(DEBUG)
    printBits(b);
    Serial.print(" ");
    Serial.print (x);
    Serial.print(" ");
    Serial.print (y);
    Serial.print(" ");
    Serial.print (encoder0Pos);
    Serial.print(" ");
    Serial.print (rx);
    Serial.print(" ");
    Serial.print (ry);
    
    Serial.println();
#endif
  

}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void requestEvent() {
  data[0] = (x >> 8) & 0xFF;
  data[1] = x & 0xFF;
  data[2] = (y >> 8) & 0xFF;
  data[3] = y & 0xFF;
  data[4] = b;
  data[5] = encoder0Pos ;
  data[6] = (rx >> 8) & 0xFF;
  data[7] = rx & 0xFF;
  data[8] = (ry >> 8) & 0xFF;
  data[9] = ry & 0xFF;
  Wire.write(data,10);
   // as expected by master
}

void printBits(byte myByte)
{
   for(byte mask = 0x80; mask; mask >>= 1)
   {
   if(mask  & myByte)
       Serial.print('1');
   else
       Serial.print('0');
   }
}
