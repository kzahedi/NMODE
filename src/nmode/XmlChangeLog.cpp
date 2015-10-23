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



#include "XmlChangeLog.h"

#include "nmode/macros.h"

#include <sstream>

XmlChangeLog* XmlChangeLog::_me = NULL;



XmlChangeLog::XmlChangeLog()
{ }

XmlChangeLog::~XmlChangeLog()
{
  close();
}

void XmlChangeLog::close()
{
  if (_me != NULL)
  {
    FORP(vector<XmlChangeLogEntry*>, x, _me) delete *x;
    delete _me;
  }
}

void XmlChangeLog::add(Version version, string description, bool crucial)
{
  if(_me == NULL) _me = new XmlChangeLog();
  XmlChangeLogEntry *entry = new XmlChangeLogEntry(version, description, crucial);
  _me->push_back(entry);
  sort(_me->begin(), _me->end(), XmlChangeLog::compare);
  _me->_version = (*_me)[_me->size()-1]->version();
  for(int i = _me->size()-1; i >= 0; i--)
  {
    if(_me->at(i)->crucial())
    {
      _me->_last_crucial_change = _me->at(i)->version();
      break;
    }
  }
}

void XmlChangeLog::add(int major, int minor, int patch, string description, bool crucial)
{
  if(_me == NULL) _me = new XmlChangeLog();
  Version v(major, minor, patch);
  add(v, description, crucial);
}

Version XmlChangeLog::version()
{
  if(_me == NULL) _me = new XmlChangeLog();
  return _me->_version;
}


Version XmlChangeLog::last_crucial_change()
{
  if(_me == NULL) _me = new XmlChangeLog();
  return _me->_last_crucial_change;
}

string XmlChangeLog::changes(Version version)
{
  if(_me == NULL) _me = new XmlChangeLog();
  stringstream oss;
  int size = 0;
  FORP(vector<XmlChangeLogEntry*>, x, _me)
  {
    oss.str("");
    oss.precision(1);
    oss.setf(ios::fixed,ios::floatfield);
    oss << (*x)->version();
    if((int)oss.str().length() > size) size = oss.str().length();
  }
  oss.str("");
  FORP(vector<XmlChangeLogEntry*>, x, _me)
  {
    if((*x)->version() > version)
    {
      oss.width(size);
      oss                      << (*x)->version();
      oss.width(0);
      oss << " -- ";
      if ((*x)->crucial()) oss << "crucial ";
      else                 oss << "optional";
      oss                      << " -- " << (*x)->description() << endl;
    }
  }
  return oss.str();
}

bool XmlChangeLog::compare(XmlChangeLogEntry *a, XmlChangeLogEntry *b)
{
  return a->version() < b->version();
}
