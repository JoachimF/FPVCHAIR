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


#if defined(SIMU)
#define WRITE_DELAY_10MS 200
#elif defined(PCBGRUVIN9X) && !defined(REV0)
#define WRITE_DELAY_10MS 500
#else
#define WRITE_DELAY_10MS 200
#endif

#define TIME_TO_WRITE() (s_eeDirtyMsk && (tmr10ms_t)(get_tmr10ms() - s_eeDirtyTime10ms) >= (tmr10ms_t)WRITE_DELAY_10MS)

extern uint8_t   s_eeDirtyMsk;
extern tmr10ms_t s_eeDirtyTime10ms;

void eeDirty(uint8_t msk);
void eeCheck(bool immediately);
void eeReadAll();
bool eeModelExists(uint8_t id);
void eeLoadModel(uint8_t id);
bool eeConvert();
void eeErase(bool warn);
void ConvertModel(int id, int version);
uint8_t eeFindEmptyModel(uint8_t id, bool down);
void selectModel(uint8_t sub);

#define eeLoadModelHeaders()
