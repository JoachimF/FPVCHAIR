#include "Arduino.h"
#include "functions.h"

#define PPM_IN  0
// Dead-time between each channel in the PPM-stream. 
#define DEAD_TIME 800
// Set to 1 to enable support for positive shift PPM equipment, 0 for negative.
#define POSITIVE_SHIFT_PPM  1
// Sets the frame-length .
#define FRAME_LENGTH (5003 + NUMBER_OF_CHANNELS * 5000)
#define PPM_IN_MIN 1000 // 0.5 ms
#define PPM_IN_MAX 4000 // 2 ms
// Number of PPM channels out. 1 - 12 channels supported. 
#define NUMBER_OF_CHANNELS 8
// TOP (timer rollover) used for PPM pulse time measurement
#define TOP (5003 + NUMBER_OF_CHANNELS * 5000)

#define PPM_MIN 800
#define PPM_SAFE_THROTTLE 1050 
#define PPM_MID 1500
#define PPM_MAX 2200
#define PPM_pin 2 // PPM in
#define CHANNELS 8 // number of channels in ppm stream, 12 ideally


extern int channelsDetected ;
extern char channel ;
extern int channelValues[20] ; 
extern char state ; // PPM signal high or Low?
extern unsigned char channel_number ;
extern long channel_value[13] ;
static volatile bool ppm_ok = false;
extern int headtrackerchans[16];
extern bool freshdata ;
/*
void InitPWMInterrupt()
{
#if (DEBUG)    
    Serial.println("PWM interrupt initialized");
#endif
  
    TCCR1A = 
       (0 << WGM10) |
       (0 << WGM11) |
       (0 << COM1A1) |
       (1 << COM1A0) | // Toggle pin om compare-match
       (0 << COM1B1) |
       (0 << COM1B0);  
  
    TCCR1B =
        (1 << ICNC1)| // Input capture noise canceler - set to active 
        (1 << ICES1)| // Input capture edge select. 1 = rising, 0 = falling. We will toggle this, doesn't matter what it starts at        
        (0 << CS10) | // Prescale 8  
        (1 << CS11) | // Prescale 8  
        (0 << CS12) | // Prescale 8
        (0 << WGM13)|    
        (1 << WGM12); // CTC mode (Clear timer on compare match) with ICR1 as top.           
    
    // Not used in this case:
    TCCR1C =
        (0 << FOC1A)| // No force output compare (A)
        (0 << FOC1B); // No force output compare (B)
        
    
    TIMSK1 = 
        (PPM_IN << ICIE1) | // Enable input capture interrupt    
        (1 << OCIE1A) | // Interrupt on compare A
        (0 << OCIE1B) | // Disable interrupt on compare B    
        (0 << TOIE1);          

    // OCR1A is used to generate PPM signal and later reset counter (to control frame-length)
    OCR1A = DEAD_TIME;    
}

//--------------------------------------------------------------------------------------
// Func: InitTimerInterrupt
// Desc: Initializes timer interrupts.
//--------------------------------------------------------------------------------------
void InitTimerInterrupt()
{  
#if (DEBUG)    
    Serial.println("Timer interrupt initialized");
#endif
  
    TCCR0A = 
       (0 << WGM00) |
       (1 << WGM01) |
       (0 << COM0A1) |
       (0 << COM0A0) |
       (0 << COM0B1) |
       (0 << COM0B0);  
   
    // 61 hz update-rate:
    TCCR0B =
        (0 << FOC0A)| // 
        (0 << FOC0B)| // 
        (1 << CS00) | // Prescale 1024 
        (0 << CS01) | // Prescale 1024  
        (1 << CS02) | // Prescale 1024
        (0 << WGM02);
  
    TIMSK0 = 
        (0 << OCIE0B) |
        (1 << OCIE0A) |
        (1 << TOIE0);       

    OCR0B = 64 * 2; 
    OCR0A = 64 * 2;
}

//--------------------------------------------------------------------------------------
// Func: TIMER1_OVF_vect
// Desc: Timer 1 overflow vector - only here for debugging/testing, as it should always
//      be reset/cleared before overflow. 
//--------------------------------------------------------------------------------------
ISR(TIMER1_OVF_vect)
{
    Serial.print("Timer 1 OVF");
}

//--------------------------------------------------------------------------------------
// Func: TIMER1_COMPA_vect
// Desc: Timer 1 compare A vector
//--------------------------------------------------------------------------------------
ISR(TIMER1_COMPA_vect)
{
    //Serial.println("X");
    if (OCR1A == FRAME_LENGTH)
    {
        TCCR1A = 
            (0 << WGM10) |
            (0 << WGM11) |
            (1 << COM1A1) |
            (1 << COM1A0) |
            (0 << COM1B1) |
            (0 << COM1B0);   
  
        channel_number = 1;
        OCR1A = DEAD_TIME;
  
        TCCR1B &= ~(1 << WGM12);
    }
    else
    {
        if (channel_number == 1)
        {
            // After first time, when pin have been set high, we toggle the pin at each interrupt
            TCCR1A = 
                (0 << WGM10) |
                (0 << WGM11) |
                (0 << COM1A1) |
                (POSITIVE_SHIFT_PPM << COM1A0) |
                (0 << COM1B1) |
                (0 << COM1B0);   
        }
                  
        if ((channel_number - 1) < NUMBER_OF_CHANNELS * 2)
        {
            if ((channel_number-1) % 2 == 1)
            {
                OCR1A += DEAD_TIME; 
            }
            else
            {
                OCR1A += channel_value[(channel_number + 1) / 2];
            }
            channel_number++;
        }
        else
        {
            // We have to use OCR1A as top too, as ICR1 is used for input capture and OCR1B can't be
            // used as top. 
            OCR1A = FRAME_LENGTH;
            TCCR1B |= (1 << WGM12);
        }
    }
}  


void ISR_ppm()
{
    #if F_CPU == 16000000
        #define PPM_SCALE 1L
    #elif F_CPU == 8000000
        #define PPM_SCALE 0L
    #else
        #error // 8 or 16MHz only !
    #endif
    static unsigned int pulse;
    static unsigned long counterPPM;
    static byte chan;
    counterPPM = TCNT1;
    TCNT1 = 0;
    ppm_ok=false;
    if(counterPPM < 510 << PPM_SCALE) {  //must be a pulse if less than 510us
        pulse = counterPPM;
    }
    else if(counterPPM > 1910 << PPM_SCALE) {  //sync pulses over 1910us
        chan = 0;
    }
    else{  //servo values between 510us and 2420us will end up here
        if(chan < CHANNELS) {
            channel_value[chan]= constrain((counterPPM + pulse) >> PPM_SCALE, PPM_MIN, PPM_MAX);
            if(chan==3)
                ppm_ok = true; // 4 first channels Ok
            if( freshdata && chan == 6 )
              channel_value[chan] = headtrackerchans[0] ;
            if( freshdata && chan == 7 ){
              channel_value[chan] = headtrackerchans[1] ;
              freshdata = false ;
            }
        }
        chan++;
    }
}*/
