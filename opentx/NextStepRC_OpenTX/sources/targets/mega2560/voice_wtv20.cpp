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


// WTV20 SD-card sound mini module driver, adapted from Gruvin9x somo14d

// Start and stop bits need to be 2ms in duration. Start bit is low, stop bit is high
#define WTV20_STOP_TIME    84 // This is the needed 2ms (4) + 40ms (80) to allow for the
// point at which the busy flag is checkable + 2ms for saftey (4)
#define WTV20_START_TIME   5  // The 2ms of a stop/start bit

enum WTV20_State {
  RESET,
  RESETPAUSE,
  PAUSE,
  SENDSTART,
  SENDDATA,
  SENDSTOP
};

#define QUEUE_LENGTH 10
uint16_t WTV20_playlist[QUEUE_LENGTH] = {0};
volatile uint8_t WTV20_InputIndex = 0;
uint8_t WTV20_PlayIndex = 4; // Also used for reset,(save 2 static uint8_t)
uint8_t Startstop = WTV20_START_TIME;
uint16_t WTV20_current = 0;
uint8_t state = RESET;

void WTV20_sendstart()
{
  WTV20_Clock_off; // Start Bit, CLK low for 2ms

  --Startstop;

  if (!Startstop) state = SENDDATA;
}

void WTV20_senddata()
{
  static uint8_t i = 0;

  if (!WTV20_CLK) {
    // Only change data when the CLK is low
    if (WTV20_current & 0x8000) {
      WTV20_Data_on; // Data high
    }
    WTV20_current = (WTV20_current << 1);
    ++i;
    _delay_us(1); // Data setup delay
    WTV20_Clock_on; // CLK high
  } else {
    // Don't alter after sending last bit in preparation for sending stop bit
    WTV20_Clock_off; // CLK low
    WTV20_Data_off; // Data low
  }

  if (i == 16) {
    i = 0;
    Startstop = WTV20_STOP_TIME;
    state = SENDSTOP;
  }
}

void WTV20_sendstop()
{
  WTV20_Data_off; // Data low
  WTV20_Clock_on; // Stop Bit, CLK high for 2ms
  --Startstop;

  if (!Startstop && !WTV20_BUSY) state = PAUSE;
}

void pushPrompt(uint16_t prompt)
{
  // if mute active => no voice
  if (g_eeGeneral.beepMode == e_mode_quiet) return;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { // To be sure than prompt list is fully updated
  /* Load playlist and activate interrupt */
  WTV20_playlist[WTV20_InputIndex] = prompt;
  ++WTV20_InputIndex;
  if (WTV20_InputIndex == QUEUE_LENGTH) WTV20_InputIndex = 0;
  }
  if (!isPlaying()) {
    TIMSK5 |= (1<<OCIE5A); // enable interrupts on Output Compare A Match
  }
}

bool isPlaying()
{
  /* interrupts active on Output Compare A Match ? */
#if defined(SIMU)
  return false;
#else
  return (TIMSK5 & (1<<OCIE5A));
#endif
}

#if !defined(SIMU)
ISR(TIMER5_COMPA_vect) // every 0.5ms normally, every 2ms during startup reset
{
  sei();
  if (state == PAUSE) {
    if (WTV20_PlayIndex == WTV20_InputIndex) {
      TIMSK5 &= ~(1<<OCIE5A); // stop reentrance
      TCNT5=0; // reset timer
      return; // nothing else to play
    } else {
      WTV20_current = WTV20_playlist[WTV20_PlayIndex];
      ++WTV20_PlayIndex;
      if (WTV20_PlayIndex == QUEUE_LENGTH) WTV20_PlayIndex = 0;
      Startstop = WTV20_START_TIME;
      state = SENDSTART;
    }
  } // end PAUSE

  if (state == SENDSTART) {
    WTV20_sendstart();
    return;
  }

  if (state == SENDDATA) {
    WTV20_senddata();
    return;
  }

  if (state == SENDSTOP) {
    WTV20_sendstop();
    return;
  }

  if (state == RESET) {
    if (WTV20_PlayIndex) { // WTV20_PlayIndex used as reset counter
      // OCR5A=0x1f4; setted in board_mega2560.cpp
      WTV20_Reset_off;
      WTV20_Data_off;
      WTV20_Clock_on;
      --WTV20_PlayIndex;
      return;
    } // RESET low
    else {
      state = RESETPAUSE;
      return;
    }
  }

  if (state == RESETPAUSE) {
    WTV20_Reset_on; // RESET high
    if (!WTV20_BUSY) {
      state = PAUSE;
      OCR5A = 0x7d; // 0.5 ms after init
    }
  }
  cli();
}
#endif
