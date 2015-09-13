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


#include "XsdChoice.h"

#include <sstream>


XsdChoice::XsdChoice(string name)
  : XsdNode(XSD_NODE_TYPE_CHOICE)
{
  _minOccurs = "";
  _maxOccurs = "";
  _minOccursGiven = false;
  _maxOccursGiven = false;
  setName(name);
}

XsdChoice::XsdChoice(string name, int minOccurs, int maxOccurs)
  : XsdNode(XSD_NODE_TYPE_CHOICE)
{
  setName(name);
  stringstream max;
  stringstream min;
  max << maxOccurs;
  min << minOccurs;
  setMaxOccurs(max.str());
  setMinOccurs(min.str());
}

XsdChoice::XsdChoice(string name, string minOccurs, string maxOccurs)
  : XsdNode(XSD_NODE_TYPE_CHOICE)
{
  setName(name);
  setMaxOccurs(maxOccurs);
  setMinOccurs(minOccurs);
}

void XsdChoice::setName(string name)
{
  _name = name;
}

void XsdChoice::add(XsdElement *element)
{
  _elements.push_back(element);
}

string XsdChoice::name()
{
  return _name;
}

std::vector<XsdElement*>::iterator XsdChoice::e_begin()
{
  return _elements.begin();
}

std::vector<XsdElement*>::iterator XsdChoice::e_end()
{
  return _elements.end();
}

int XsdChoice::e_size()
{
  return (int)_elements.size();
}

std::vector<XsdAttribute*>::iterator XsdChoice::a_begin()
{
  return _attributes.begin();
}

std::vector<XsdAttribute*>::iterator XsdChoice::a_end()
{
  return _attributes.end();
}

int XsdChoice::a_size()
{
  return (int)_attributes.size();
}

void XsdChoice::add(XsdAttribute *attribute)
{
  _attributes.push_back(attribute);
}

bool XsdChoice::maxOccursGiven()
{
  return _maxOccursGiven;
}

bool XsdChoice::minOccursGiven()
{
  return _minOccursGiven;
}

string XsdChoice::maxOccurs()
{
  return _maxOccurs;
}

string XsdChoice::minOccurs()
{
  return _minOccurs;
}

void XsdChoice::setMaxOccurs(string maxOccurs)
{
  _maxOccursGiven = true;
  _maxOccurs = maxOccurs;
}

void XsdChoice::setMinOccurs(string minOccurs)
{
  _minOccursGiven = true;
  _minOccurs = minOccurs;
}

void XsdChoice::add(std::vector<XsdElement*> elements)
{
  for(std::vector<XsdElement*>::iterator i = elements.begin(); i != elements.end(); i++)
  {
    add(*i);
  }
}

void XsdChoice::add(XsdSequence *sequence)
{
  _sequences.push_back(sequence);
}

std::vector<XsdSequence*>::iterator XsdChoice::s_begin()
{
  return _sequences.begin();
}

std::vector<XsdSequence*>::iterator XsdChoice::s_end()
{
  return _sequences.end();
}

int XsdChoice::s_size()
{
  return (int)_sequences.size();
}

