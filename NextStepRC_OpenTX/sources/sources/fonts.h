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


#ifndef fonts_h
#define fonts_h

extern const pm_uchar font_5x7[];
extern const pm_uchar font_10x14[];

//#if defined(BOLD_FONT) && (defined(EXTSTD) || defined(PCBMEGA2560))
//#if defined(BOLD_FONT) && ((!defined(CPUM64) && !defined(PCBMEGA2560)) || defined(TELEMETRY_NONE)) && !defined(BOOT) 
//#define BOLD_SPECIFIC_FONT
//extern const pm_uchar font_5x7_B[];
//#endif

#endif
