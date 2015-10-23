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


#include "XsdElement.h"

#include <sstream>

XsdElement::XsdElement()
  : XsdNode(XSD_NODE_TYPE_ELEMENT)
{
  _name = "";
  _type = "";
  _minOccurs = "";
  _maxOccurs = "";
  _minOccursGiven = false;
  _maxOccursGiven = false;
}

XsdElement::XsdElement(string name, string type, int minOccurs, int maxOccurs)
  : XsdNode(XSD_NODE_TYPE_ELEMENT)
{
  _name = name;
  _type = type;
  stringstream oss;
  oss << minOccurs;
  _minOccurs = oss.str();
  _minOccursGiven = true;

  oss.str("");
  oss << maxOccurs;
  _maxOccurs = oss.str();
  _maxOccursGiven = true;
}

XsdElement::XsdElement(string name, string type, int minOccurs)
  : XsdNode(XSD_NODE_TYPE_ELEMENT)
{
  _name = name;
  _type = type;
  stringstream oss;
  oss << minOccurs;
  _minOccurs = oss.str();
  _minOccursGiven = true;

  _maxOccurs = TAG_XSD_UNBOUNDED;
  _maxOccursGiven = true;
}

XsdElement::XsdElement(string name, string type, string minOccurs, string maxOccurs)
  : XsdNode(XSD_NODE_TYPE_ELEMENT)
{
  _name = name;
  _type = type;
  _minOccursGiven = false;
  _maxOccursGiven = false;
  if(minOccurs.length() > 0)
  {
    _minOccurs = minOccurs;
    _minOccursGiven = true;
  }
  if(maxOccurs.length() > 0)
  {
    _maxOccurs = maxOccurs;
    _maxOccursGiven = true;
  }
}

XsdElement::XsdElement(string name, string type, int minOccurs, string maxOccurs)
  : XsdNode(XSD_NODE_TYPE_ELEMENT)
{
  _name = name;
  _type = type;
  _minOccursGiven = false;
  _maxOccursGiven = false;
  stringstream oss;
  oss << minOccurs;
  _minOccurs = oss.str();
  _minOccursGiven = true;

  if(maxOccurs.length() > 0)
  {
    _maxOccurs = maxOccurs;
    _maxOccursGiven = true;
  }
}
void XsdElement::setName(string name)
{
  _name = name;
}

void XsdElement::setType(string type)
{
  _type = type;
}

void XsdElement::setMinOccurs(string minOccurs)
{
  _minOccurs      = minOccurs;
  _minOccursGiven = true;
}

void XsdElement::setMinOccurs(int minOccurs)
{
  stringstream oss;
  oss << minOccurs;
  setMinOccurs(oss.str());
}

void XsdElement::setMaxOccurs(string maxOccurs)
{
  _maxOccurs      = maxOccurs;
  _maxOccursGiven = true;
}

void XsdElement::setMaxOccurs(int maxOccurs)
{
  stringstream oss;
  oss << maxOccurs;
  setMaxOccurs(oss.str());
}

string XsdElement::name()
{
  return _name;
}

string XsdElement::minOccurs()
{
  return _minOccurs;
}

bool XsdElement::minOccursGiven()
{
  return _minOccursGiven;
}

string XsdElement::maxOccurs()
{
  return _maxOccurs;
}

bool XsdElement::maxOccursGiven()
{
  return _maxOccursGiven;
}

string XsdElement::type()
{
  return _type;
}

void XsdElement::add(XsdAttribute *attribute)
{
  _attributes.push_back(attribute);
}

std::vector<XsdAttribute*>::iterator XsdElement::a_begin()
{
  return _attributes.begin();
}

std::vector<XsdAttribute*>::iterator XsdElement::a_end()
{
  return _attributes.end();
}

int XsdElement::a_size()
{
  return _attributes.size();
}
