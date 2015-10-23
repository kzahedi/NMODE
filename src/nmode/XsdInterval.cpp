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


#include "XsdInterval.h"

#include <sstream>

XsdInterval::XsdInterval(string name, string type, int minimum, int maximum)
  : XsdNode(XSD_NODE_TYPE_INTERVAL)
{
  stringstream min;
  min << minimum;
  stringstream max;
  max << maximum;
  __init(name, type, min.str(), max.str());
}

XsdInterval::XsdInterval(string name, string type, string minimum, string maximum)
  : XsdNode(XSD_NODE_TYPE_INTERVAL)
{
  __init(name, type, minimum, maximum);
}

void XsdInterval::__init(string name, string type, string min, string max)
{
  _name = name;
  _type = type;
  _min  = min;
  _max  = max;

}

string XsdInterval::minimum()
{
  return _min;
}

string XsdInterval::maximum()
{
  return _max;
}

string XsdInterval::name()
{
  return _name;
}

string XsdInterval::type()
{
  return _type;
}
