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


#include "opentx.h"
#include "keys.h"

uint8_t s_evt;
struct t_inactivity inactivity = {0};

uint8_t getEvent()
{
  uint8_t evt = s_evt;
  s_evt = 0;
  return evt;
}

#define KEY_LONG_DELAY 32

Key keys[NUM_KEYS];

void Key::input(bool val)
{
  uint8_t t_vals = m_vals ;
  t_vals <<= 1 ;
  if (val) t_vals |= 1; //portbit einschieben
  m_vals = t_vals ;

  m_cnt++;

  if (m_state && m_vals==0) {  //gerade eben sprung auf 0
    if (m_state != KSTATE_KILLED) {
      putEvent(EVT_KEY_BREAK(key()));
    }
    m_cnt   = 0;
    m_state = KSTATE_OFF;
  }
  switch(m_state) {
  case KSTATE_OFF:
    if (m_vals == FFVAL) { //gerade eben sprung auf ff
      m_state = KSTATE_START;
      m_cnt   = 0;
    }
    break;
  //fallthrough
  case KSTATE_START:
    putEvent(EVT_KEY_FIRST(key()));
    inactivity.counter = 0;
    m_state   = KSTATE_RPTDELAY;
    m_cnt     = 0;
    break;

  case KSTATE_RPTDELAY: // gruvin: delay state before first key repeat
    if (m_cnt == KEY_LONG_DELAY) {
      putEvent(EVT_KEY_LONG(key()));
    }
    if (m_cnt == 40) {
      m_state = 16;
      m_cnt = 0;
    }
    break;

  case 16:
  case 8:
  case 4:
  case 2:
    if (m_cnt >= 48)  { //3 6 12 24 48 pulses in every 480ms
      m_state >>= 1;
      m_cnt     = 0;
    }
  // no break
  case 1:
    if ((m_cnt & (m_state-1)) == 0) {
      putEvent(EVT_KEY_REPT(key()));
    }
    break;

  case KSTATE_PAUSE: //pause
    if (m_cnt >= 64) {
      m_state = 8;
      m_cnt   = 0;
    }
    break;

  case KSTATE_KILLED: //killed
    break;
  }
}

EnumKeys Key::key() const
{
  return static_cast<EnumKeys>(this - keys);
}

void pauseEvents(uint8_t event)
{
  event = EVT_KEY_MASK(event);
  if (event < (int)DIM(keys)) keys[event].pauseEvents();
}

void killEvents(uint8_t event)
{
#if defined(ROTARY_ENCODER_NAVIGATION)
  if (event == EVT_ROTARY_LONG) {
    killEvents(BTN_REa + NAVIGATION_RE_IDX());
  } else
#endif
  {
    event = EVT_KEY_MASK(event);
    if (event < (int)DIM(keys)) keys[event].killEvents();
  }
}

void clearKeyEvents()
{
  // loop until all keys are up
  while (keyDown()) {

#if defined(SIMU)
    SIMU_SLEEP(1/*ms*/);
#else
    MYWDT_RESET();
#endif

#if defined(PCBSTD) && defined(ROTARY_ENCODER_NAVIGATION) && !defined(TELEMETREZ)
    rotencPoll();
#endif
  }

  memclear(keys, sizeof(keys));
  putEvent(0);
}


