//-----------------------------------------------------------------------------
// File: Functions.h
// Desc: Declares PPM-related functions for the project.
//-----------------------------------------------------------------------------
#ifndef functions_h
#define functions_h


void InitTimerInterrupt();
void InitPWMInterrupt();
void DetectPPM();
void PrintPPM();
void DetectPPM();
#if HeadTracker == 1
void Send_i2C() ;
#endif

#if NRF24L01 == 1
void Send_NRF() ;
#endif
#endif
