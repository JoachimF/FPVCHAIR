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


#ifndef _FIFO_H_
#define _FIFO_H_

template <int N>
class Fifo
{
public:
  Fifo():
    widx(0),
    ridx(0)
  {
  }

  void push(uint8_t byte)
  {
    uint32_t next = (widx+1) & (N-1);
    if (next != ridx) {
      fifo[widx] = byte;
      widx = next;
    }
  }

  bool pop(uint8_t & byte)
  {
    if (isEmpty()) {
      return false;
    } else {
      byte = fifo[ridx];
      ridx = (ridx+1) & (N-1);
      return true;
    }
  }

  bool isEmpty()
  {
    return (ridx == widx);
  }

  bool isFull()
  {
    uint32_t next = (widx+1) & (N-1);
    return (next == ridx);
  }

  void flush()
  {
    while (!isEmpty()) {};
  }

protected:
  uint8_t fifo[N];
  volatile uint32_t widx;
  volatile uint32_t ridx;
};

#endif // _FIFO_H_
