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



#include "XsdAttribute.h"

XsdAttribute::XsdAttribute()
  : XsdNode(XSD_NODE_TYPE_ATTRIBUTE)
{
  _name = "";
  _type = "";
  _required = true;
}

XsdAttribute::XsdAttribute(string name, string type, bool required)
  : XsdNode(XSD_NODE_TYPE_ATTRIBUTE)
{
  _name     = name;
  _type     = type;
  _required = required;
}

void XsdAttribute::setName(string name)
{
  _name = name;
}

string XsdAttribute::name()
{
  return _name;
}

void XsdAttribute::setType(string type)
{
  _type = type;
}

string XsdAttribute::type()
{
  return _type;
}

void XsdAttribute::setRequired(bool required)
{
  _required = required;
}

bool XsdAttribute::required()
{
  return _required;
}