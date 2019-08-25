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


#include "../../opentx.h"


#if defined(SIMU)
#include "lcd_simu_driver.cpp"
#else
#if defined(LCD_KS108)
#include "targets/common/lcd_ks108_driver.cpp"
#elif defined(LCD_ST7920)
#include "targets/common/lcd_st7920_driver.cpp"
#elif defined(LCD_SSD1306)
#include "targets/common/lcd_ssd1306_driver.cpp"
#elif defined(LCD_SH1306)
#include "targets/common/lcd_sh1106_driver.cpp"
#else
#include "targets/common/lcd_default_driver.cpp" // ST7565P, ST7565R, ERC12864FSF
#endif
#endif // defined
