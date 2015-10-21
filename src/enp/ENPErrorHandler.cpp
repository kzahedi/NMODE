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
