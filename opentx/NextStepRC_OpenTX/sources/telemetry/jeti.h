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


#ifndef jeti_h
#define jeti_h

#define JETI_KEY_LEFT		0x70
#define JETI_KEY_RIGHT		0xe0
#define JETI_KEY_UP		0xd0
#define JETI_KEY_DOWN		0xb0
#define JETI_KEY_NOCHANGE	0xf0

void JETI_Init(void);
void JETI_EnableRXD (void);
void JETI_DisableRXD (void);
void JETI_EnableTXD (void);
void JETI_DisableTXD (void);

void telemetryInterrupt10ms();
void menuTelemetryJeti(uint8_t event);

#endif

