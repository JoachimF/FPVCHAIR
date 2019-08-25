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
#include "stamp-opentx.h"

#define STR2(s) #s
#define DEFNUMSTR(s)  STR2(s)

#if defined(PCBSTD)
#define EEPROM_STR DEFNUMSTR(EEPROM_VER) "-" DEFNUMSTR(EEPROM_VARIANT)
#else
#define EEPROM_STR DEFNUMSTR(EEPROM_VER);
#endif

const pm_char vers_stamp[] PROGMEM = "FW: " "OpenTX-" FLAVOUR "\036VERS\037\033: " VERS_STR "\036DATE\037\033: " DATE_STR"\036TIME\037\033: " TIME_STR "\036EEPR\037\033: " EEPROM_STR;
