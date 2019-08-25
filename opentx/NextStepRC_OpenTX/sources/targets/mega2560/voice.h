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


#define PROMPT_CUSTOM_BASE      0
#define PROMPT_I18N_BASE        256
#define PROMPT_SYSTEM_BASE      480

extern void pushPrompt(uint16_t prompt);
extern bool isPlaying();

#define I18N_PLAY_FUNCTION(lng, x, ...) void x(__VA_ARGS__)
#define PLAY_FUNCTION(x, ...)           void x(__VA_ARGS__)
#define PUSH_CUSTOM_PROMPT(p, id)       pushPrompt(PROMPT_CUSTOM_BASE+(p))
#define PUSH_NUMBER_PROMPT(p)           pushPrompt(PROMPT_I18N_BASE+(p))
#define PUSH_SYSTEM_PROMPT(p)           pushPrompt(PROMPT_SYSTEM_BASE+(p))
#define PLAY_NUMBER(n, u, a)            playNumber((n), (u), (a))
#define PLAY_DURATION(d, att)           playDuration((d))
#define PLAY_DURATION_ATT
#define PLAY_TIME
#define IS_PLAY_TIME()                  (0)
#define IS_PLAYING(id)                  isPlaying()
#define PLAY_VALUE(v, id)               playValue((v))

#define VOLUME_LEVEL_MAX                7
#define VOLUME_LEVEL_DEF                7
#define setVolume(v)
