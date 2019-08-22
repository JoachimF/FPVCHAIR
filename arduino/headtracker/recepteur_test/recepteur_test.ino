
/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
* Envoie les données sur bus I2C sous forme de 6 octets
*/

//#include <SoftSPI.h>
#include <Wire.h>
#define SOFTSPI 
#define SOFT_SPI_MISO_PIN A0
#define SOFT_SPI_MOSI_PIN 3
#define SOFT_SPI_SCK_PIN 4
#define MOSI_pin  3  // MOSI - D3
#define SCK_pin   4  // SCK  - D4
#define CE_pin    5  // CE   - D5
#define MISO_pin  A0 // MISO - A0
#define CS_pin    A1 // CS   - A1
#include "RF24.h"
#include "functions.h"
#define PPM_PIN 2
#define PPM_MIN 800
#define PPM_SAFE_THROTTLE 1050 
#define PPM_MID 1500
#define PPM_MAX 2200
#define PPM_pin 2 // PPM in
#define CHANNELS 8 // number of channels in ppm stream, 12 ideally

#define MOSI_pin  3  // MOSI - D3
#define SCK_pin   4  // SCK  - D4
#define CE_pin    5  // CE   - D5
#define MISO_pin  A0 // MISO - A0
#define CS_pin    A1 // CS   - A1

#define ledPin 13 // LED  - D13

#define DATA_TO_RECEIVE 10
byte fhss_schema[]={90,120,95,100,115,100};
byte data[6];
int data_received = 0 ;
int ptr_fhss_schema = 0 ;
unsigned long last_rx_time = 0;
bool fhss_on = false;

static bool reset=true;
volatile uint16_t Servo_data[12];
static uint16_t ppm[12] = {PPM_MIN,PPM_MIN,PPM_MIN,PPM_MIN,PPM_MID,PPM_MID,
PPM_MID,PPM_MID,PPM_MID,PPM_MID,PPM_MID,PPM_MID,};

unsigned char PpmIn_PpmOut[13] = {0,1,2,3,4,5,6,7,8,9,10,11,12};
long channel_value[13] = {2100,2100,2100,2100,2100,2100,2100,2100,2100,2100,2100,2100,2100};
// Local variables
unsigned int pulseTime = 0; 
unsigned int lastTime = 0; 
unsigned int timeRead; 
int channelsDetected = 0;
char channel = 0;
int channelValues[20]; 
char state = 0; // PPM signal high or Low?
unsigned char channel_number = 1;
char shift = 0;
char time_out = 0;
unsigned char htChannels[3] = {8, 7, 6}; // pan, tilt, roll
extern void ISR_ppm() ;
int headtrackerchans[16];
bool freshdata = false ;

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 1;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(CE_pin,CS_pin);
/**********************************************************/

long int addresses[][6] = {0x123457,0x123456};

#define NRF_ADDR_RX  0x123456
#define NRF_ADDR_TX  0x654321
// Used to control whether this node is sending or receiving
bool role = 0;



void setup() {
  Serial.begin(115200);
  Serial.println(F("RF24/examples/GettingStarted"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  Wire.begin(0x0A);                // adresse sur le bus I2C #10
  Wire.onRequest(requestEvent); // register event
  
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  
  // Open a writing and reading pipe on each radio, with opposite addresses
    radio.openWritingPipe(NRF_ADDR_TX);
    radio.openReadingPipe(1,NRF_ADDR_RX);
  radio.setDataRate(RF24_2MBPS) ;
  radio.setCRCLength(RF24_CRC_8) ;
  // Start the radio listening for data
  radio.setChannel(fhss_schema[0]);
  radio.startListening();
   // PPM ISR setup
  //attachInterrupt(digitalPinToInterrupt(PPM_pin), ISR_ppm, CHANGE);
  //TCCR1A = 0;  //reset timer1
  //TCCR1B = 0;
  //TCCR1B |= (1 << CS11); //set timer1 to increment every 1 us @ 8MHz, 0.5 us @16MHz
  //InitPWMInterrupt();         // Start PWM interrupt  
  //InitTimerInterrupt();        // Start timer interrupt (for sensors)  
//  analogWriteResolution(12);
  //pinMode(PPM_PIN,OUTPUT) ;
  pinMode(ledPin,OUTPUT) ;
}

int currmillis,millis_prec = millis() ;
void loop() {

    if( radio.available()){
      //Serial.print("Chan : ");
      //Serial.println(ptr_fhss_schema);                                                              // Variable for the received timestamp
      while (radio.available()) {                                   // While there is data ready
        fhss_on=true;  // Now we can follow the fhss schema (we are synced with PTX channel and with interrupt time of PTX)
        last_rx_time = millis();
        radio.read( &headtrackerchans, sizeof(int) * 3) ;             // Get the payload
        freshdata = true ;
        //digitalWrite(PPM_PIN,LOW) ;
        digitalWrite(13, !digitalRead(13));
      }

      //radio.stopListening();                                        // First, stop listening so we can talk   
      //radio.write( &got_time, sizeof(int)*3 );              // Send the final one back.      
      //radio.startListening(); // Now, resume listening so we catch the next packets.
      currmillis = millis() ;
      if(currmillis - millis_prec >= 10)
      {
        millis_prec = currmillis ;
        ptr_fhss_schema++ ;
        if(ptr_fhss_schema >= sizeof(fhss_schema)) ptr_fhss_schema=0; // To avoid fhss schema array indexing overflow
        radio.setChannel(fhss_schema[ptr_fhss_schema]); // Change channel  
        
        if(freshdata == true) {
        freshdata = false ;
        /*//Serial.println("Data received");      
        for(int i= 0;i<3;i++){
                 if(i == 1)
                  {
                    analogWrite(PPM_PIN, (headtrackerchans[i]-1000)/8);
                    Serial.print(" , 8-bit PWM value : ");
                    Serial.println((headtrackerchans[i]-1000)/8);  
                  }
                  Serial.print(i);
                  Serial.print(F(" - "));
                  Serial.println(headtrackerchans[i]);
              }*/
        }
      }
    }
    
    if((millis() - last_rx_time) > ((((sizeof(fhss_schema))+5)*10*10))) { 
        last_rx_time = millis();
        fhss_on=false;
        ptr_fhss_schema++;
        if(ptr_fhss_schema >= sizeof(fhss_schema)) ptr_fhss_schema=0;
        radio.setChannel(fhss_schema[ptr_fhss_schema]);
        //digitalWrite(PPM_PIN,HIGH) ;
        //Serial.print("HFSS Lost Chan : ");
        //Serial.println(ptr_fhss_schema);
    }
/*      for(int i= 0;i<8;i++){
        Serial.print("Channel ");
        Serial.print(i);
        Serial.print(" : ");
        Serial.println(channel_value[i]) ;
      }*/
      //delay(100) ;
      //Serial.print(".");
 
} // Loop

void requestEvent() 
{
  data[0] = (headtrackerchans[0] >> 8) & 0xFF;
  data[1] = headtrackerchans[0] & 0xFF;
  data[2] = (headtrackerchans[1] >> 8) & 0xFF;
  data[3] = headtrackerchans[1] & 0xFF;
  data[4] = (headtrackerchans[2] >> 8) & 0xFF;
  data[5] = headtrackerchans[2] & 0xFF;
  Wire.write(data,6);
   // as expected by master
}
