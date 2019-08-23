/*
**************************************************************************
*                                                                        *
*              This file is part of the NextStepRC project.              *
*                                                                        *
*                         Based on code named                            *
*             OpenTx - https://github.com/opentx/opentx                  *
*                                                                        *
*              ATmega AVR family (M64, M128, M2560, M2561)               *
*                                                                        *
*   NextStepRC is free software: you can redistribute it and/or modify   *
*   it under the terms of the GNU General Public License as published by *
*   the Free Software Foundation, either version 2 of the License, or    *
*   (at your option) any later version.                                  *
*                                                                        *
*   NextStepRC is distributed in the hope that it will be useful,        *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of       *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
*   GNU General Public License for more details.                         *
*                                                                        *
*       License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html          *
*                                                                        *
**************************************************************************
*/

#define GIMBAL_ADDR 0x48
#define PEDALS_ADDR 0x4A
#define THROTTLE_ADDR 0x08
#define HeadTracker_ADDR 0x0A

#define GIMBAL_X
#define GIMBAL_Y


#include "../../opentx.h"

int enc_old = 0;

#define ADC_VREF_TYPE (1 << REFS0) // AVCC with external capacitor at AREF pin

void read_HeadTracker()
{
		uint8_t b[6] ;
		int i;
		uint16_t rx,ry,rz;
		for(i=0;i<6;i++)
			b[i] = 0 ;
		if(!i2c_start(HeadTracker_ADDR << 1 | I2C_READ))
		{
		b[0] = i2c_read_ack() ; // X
		b[1] = i2c_read_ack() ; // X
		b[2] = i2c_read_ack() ; // Y
		b[3] = i2c_read_ack() ; // Y
		b[4] = i2c_read_ack() ; // Z
		b[5] = i2c_read_nack() ; // Z
		i2c_stop() ;
		
		rx = b[0] ;
		rx = (rx << 8) | b[1] ;
		ry = b[2] ;
		ry = (ry << 8) | b[3] ;
		rz = b[4] ;
		rz = (rz << 8) | b[5] ;

		s_anaFilt[5] = ry >> 2;
		s_anaFilt[6] = rz >> 2;
		}
}


void read_TQS()
{
		uint8_t b[10] ;
		int i;
		uint16_t throttle, antenna,rx,ry;
		for(i=0;i<10;i++)
			b[i] = 0 ;

		if(!i2c_start(THROTTLE_ADDR << 1 | I2C_READ))
		{
		b[0] = i2c_read_ack() ; // Throttle
		b[1] = i2c_read_ack() ; // Throttle
		b[2] = i2c_read_ack() ; // Antenna
		b[3] = i2c_read_ack() ; // Antenna
		b[4] = i2c_read_ack() ; // Buttons
		b[5] = i2c_read_ack() ; // Encodeur
		b[6] = i2c_read_ack() ; 
		b[7] = i2c_read_ack() ;
		b[8] = i2c_read_ack() ;
		b[9] = i2c_read_nack() ;
		i2c_stop() ;
		
		
		throttle = b[0] ;
		throttle = (throttle << 8) | b[1] ;
		throttle = 1024 - throttle ;
		antenna = b[2] ;
   	    antenna = (antenna << 8) | b[3] ;

		rx = b[6] ;
		rx = (rx << 8) | b[7] ;
		ry = b[8] ;
		ry = (ry << 8) | b[9] ;
		
		// Potars
		s_anaFilt[2] = throttle ;
		s_anaFilt[4] = antenna ;
		s_anaFilt[5] = rx >> 6 ;
		s_anaFilt[6] = ry >> 6;

		
		// Encodeur
		incRotaryEncoder(0,b[5]-enc_old) ;
		enc_old = b[5] ;
		//incRotaryEncoder(1,b[5]) ;
		
		//Boutons
		TQS_buttons = b[4] ;
		}
		
}

void adcInit()
{
  i2c_init();
  ADMUX = ADC_VREF_TYPE;
  ADCSRA = 0x85; // ADC enabled, pre-scaler division=32 (no interrupt, no auto-triggering)
#if defined(CPUM2560)
  ADCSRB = (1 << MUX5);
#endif
}

void adcPrepareBandgap()
{
  // #if structure identical to the one in getADC_bandgap()
#if defined(PCBGRUVIN9X)
  // For PCB V4, use our own 1.2V, external reference (connected to ADC3)
  ADCSRB &= ~(1<<MUX5);
  ADMUX = 0x03|ADC_VREF_TYPE; // Switch MUX to internal reference
#elif defined(PCBMEGA2560)
#else
  ADMUX = 0x1E|ADC_VREF_TYPE; // Switch MUX to internal reference
#endif
}


void getADC()
{
	uint16_t temp_ana;
	//int adc_input = 0 ;

	// Gimbal X
	if(!i2c_start(GIMBAL_ADDR << 1 | I2C_READ))
	{
	i2c_stop();
	temp_ana = ads1115_readADC_SingleEnded(GIMBAL_ADDR,1,DATARATE_860SPS,FSR_6_144) ;	
	s_anaFilt[3] = temp_ana >> 5;
	temp_ana = ads1115_readADC_SingleEnded(GIMBAL_ADDR,1,DATARATE_860SPS,FSR_6_144) ;	
	s_anaFilt[3] += temp_ana >> 5;
	//Gimbal Y
	temp_ana = ads1115_readADC_SingleEnded(GIMBAL_ADDR,0,DATARATE_860SPS,FSR_6_144) ;	
	s_anaFilt[1] = temp_ana >> 5;
	temp_ana = ads1115_readADC_SingleEnded(GIMBAL_ADDR,0,DATARATE_860SPS,FSR_6_144) ;	
	s_anaFilt[1] += temp_ana >> 5;
	}

	//Throttle
	read_TQS() ;

	//Rudder 
	if(!i2c_start(PEDALS_ADDR << 1 | I2C_READ))
	{
	i2c_stop();
	temp_ana = ads1115_readADC_SingleEnded(PEDALS_ADDR,0,DATARATE_860SPS,FSR_6_144) ;
	s_anaFilt[0] = temp_ana >> 5;
	temp_ana = ads1115_readADC_SingleEnded(PEDALS_ADDR,0,DATARATE_860SPS,FSR_6_144) ;
	s_anaFilt[0] += temp_ana >> 5;
	}
	
	// HeadTracker
	read_HeadTracker() ;
	
	ADMUX = 7|ADC_VREF_TYPE;
    ADCSRA |= 1 << ADSC; // Start the AD conversion
    while (ADCSRA & (1 << ADSC)); // Wait for the AD conversion to complete
    temp_ana = ADC;
    ADCSRA |= 1 << ADSC; // Start the second AD conversion
    while (ADCSRA & (1 << ADSC)); // Wait for the AD conversion to complete
    temp_ana += ADC;
	//Batterie
	s_anaFilt[7] = temp_ana;
	
}



void getADC_bandgap()
{
#if defined(PCBGRUVIN9X)
  static uint8_t s_bgCheck = 0;
  static uint16_t s_bgSum = 0;
  ADCSRA |= (1 << ADSC); // request sample
  s_bgCheck += 32;
  while ((ADCSRA & (1 << ADIF))==0); // wait for sample
  ADCSRA |= (1 << ADIF);
  if (s_bgCheck == 0) { // 8x over-sample (256/32=8)
    BandGap = s_bgSum+ADC;
    s_bgSum = 0;
  } else {
    s_bgSum += ADC;
  }
  ADCSRB |= (1 << MUX5);
#elif defined(PCBMEGA2560)
  BandGap = 2040;
/*
  _delay_us(400); // this somewhat costly delay is the only remedy for stable results on the Atmega2560/1 chips
  ADCSRA |= 0x40;
  while ((ADCSRA & 0x10) == 0);
  ADCSRA |= 0x10; // take sample
  BandGap = ADC;      */
#else
  /*
    MCUCR|=0x28;  // enable Sleep (bit5) enable ADC Noise Reduction (bit2)
    asm volatile(" sleep        \n\t");  // if _SLEEP() is not defined use this
    // ADCSRA|=0x40;
    while ((ADCSRA & 0x10)==0);
    ADCSRA|=0x10; // take sample  clear flag?
    BandGap=ADC;
    MCUCR&=0x08;  // disable sleep
    */
  ADCSRA |= (1 << ADSC);
  while (ADCSRA & (1 << ADSC));
  BandGap = ADC;
#endif
}

