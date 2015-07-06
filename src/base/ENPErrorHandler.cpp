/*************************************************************************
 *                                                                       *
 * This file is part of Yet Another Robot Simulator (YARS).              *
 * Copyright (C) 2003-2015 Keyan Ghazi-Zahedi.                           *
 * All rights reserved.                                                  *
 * Email: keyan.zahedi@googlemail.com                                    *
 * Web: https://github.com/kzahedi/YARS                                  *
 *                                                                       *
 * For a list of contributors see the file AUTHORS.                      *
 *                                                                       *
 * YARS is free software; you can redistribute it and/or modify it under *
 * the terms of the GNU General Public License as published by the Free  *
 * Software Foundation; either version 2 of the License, or (at your     *
 * option) any later version.                                            *
 *                                                                       *
 * YARS is distributed in the hope that it will be useful, but WITHOUT   *
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or *
 * FITNESS FOR A PARTICULAR PURPOSE.                                     *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with YARS in the file COPYING; if not, write to the Free        *
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor,               *
 * Boston, MA 02110-1301, USA                                            *
 *                                                                       *
 *************************************************************************/



#include "ENPErrorHandler.h"

#include "StringTokeniser.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#ifndef __APPLE__
#include <string.h>
#endif // __APPLE__

ENPErrorHandler* ENPErrorHandler::_me = NULL;

ENPErrorHandler::ENPErrorHandler()
{

}

ENPErrorHandler* ENPErrorHandler::instance()
{
  if(_me == NULL)
  {
    _me = new ENPErrorHandler();
  }
  return _me;
}

string ENPErrorHandler::message()
{
  return str();
}

void ENPErrorHandler::push()
{
  // if(_me->observers.size() > 0) // is part of yars
  // {
  //   _me->notifyObservers(_m_error);
  // }
  // else // is part of robot controller
  // {
    cout << _me->str() << endl;
    exit(-1);
  // }
}

void ENPErrorHandler::push(string message)
{
  (*_me) << message;
  _me->push();
}

void ENPErrorHandler::push(const char *message, ...)
{
  va_list ap;
  va_start (ap, message);
  int result = -1; 
  int length = 256;
  char *buffer = 0;
  while (result == -1)
  {
    if (buffer) delete [] buffer;
    buffer = new char [length + 1];
    memset(buffer, 0, length + 1);
    result = vsnprintf(buffer, length, message, ap);
    length *= 2;
  }
  std::string s(buffer);
  delete [] buffer;
  va_end (ap);
  (*_me) << s;
  _me->push();
}
