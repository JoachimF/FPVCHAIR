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


#include "../opentx.h"
#include "menu_model.h"


void menuModelTemplates(uint8_t event)
{
  SIMPLE_MENU(STR_MENUTEMPLATES, menuTabModel, e_Templates, 1+TMPL_COUNT);

  uint8_t sub = menuVerticalPosition - 1;

  if (sub < TMPL_COUNT) {
    if (warningResult) {
      warningResult = 0;
      applyTemplate(sub);
      AUDIO_WARNING2();
    }
    if (event==EVT_KEY_BREAK(KEY_ENTER)) {
      POPUP_CONFIRMATION(STR_VTEMPLATES+1 + (sub * LEN2_VTEMPLATES));
      s_editMode = 0;
    }
  }

  coord_t y = MENU_HEADER_HEIGHT + 1;
  uint8_t k = 0;
  for (uint8_t i=0; i<LCD_LINES-1 && k<TMPL_COUNT; i++) {
    k = i+menuVerticalOffset;
    lcdDrawNumberNAtt(3*FW, y, k, (sub==k ? INVERS : 0)|LEADING0, 2);
    lcdDrawTextAtIndex(4*FW, y, STR_VTEMPLATES, k, (sub==k ? INVERS  : 0));
    y+=FH;
  }
}
