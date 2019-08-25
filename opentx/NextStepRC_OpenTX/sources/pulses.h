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


#ifndef PULSES_H
#define PULSES_H

extern uint8_t s_current_protocol[1];
extern uint8_t s_pulses_paused;

extern uint8_t *pulses2MHzRPtr;
extern uint8_t *pulses2MHzWPtr;

extern uint16_t nextMixerEndTime;

extern uint8_t moduleFlag[NUM_MODULES];

enum ModuleFlag {
  MODULE_NORMAL_MODE,
  MODULE_RANGECHECK,
  MODULE_BIND,
  // MODULE_OFF, // will need an EEPROM conversion
};

#define MAX_MIXER_DELTA (50*16) /* 50ms max as an interval between 2 mixer calculations */

#define SEND_FAILSAFE_NOW()
#define SEND_FAILSAFE_1S()

#define IS_PPM_PROTOCOL(protocol)          (protocol<=PROTO_PPMSIM)

#if NUM_MODULES > 1
#define IS_RANGECHECK_ENABLE()             (moduleFlag[0] == MODULE_RANGECHECK || moduleFlag[1] == MODULE_RANGECHECK)
#else
#define IS_RANGECHECK_ENABLE()             (moduleFlag[0] == MODULE_RANGECHECK)
#endif

#if defined(DSM2)
#define DSM2_BIND_TIMEOUT      255         // 255*11ms
#define IS_DSM2_PROTOCOL(protocol)         (protocol>=PROTO_DSM2_LP45 && protocol<=PROTO_DSM2_DSMX)
extern uint8_t dsm2BindTimer;
#else
#define IS_DSM2_PROTOCOL(protocol)         (0)
#endif

#if defined(DSM2_SERIAL)
#define IS_DSM2_SERIAL_PROTOCOL(protocol)  (IS_DSM2_PROTOCOL(protocol))
#else
#define IS_DSM2_SERIAL_PROTOCOL(protocol)  (0)
#endif

#if defined(PXX)
#define IS_PXX_PROTOCOL(protocol)          (protocol==PROTO_PXX)
#else
#define IS_PXX_PROTOCOL(protocol)          (0)
#endif

void startPulses();
inline bool pulsesStarted()
{
  return s_current_protocol[0] != 255;
}
inline void pausePulses()
{
  s_pulses_paused = true;
}
inline void resumePulses()
{
  s_pulses_paused = false;
}
void setupPulses();
void DSM2_Init();
void DSM2_Done();

#endif
