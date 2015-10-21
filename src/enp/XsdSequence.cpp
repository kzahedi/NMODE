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


#include "XsdSequence.h"


XsdSequence::XsdSequence()
  : XsdNode(XSD_NODE_TYPE_SEQUENCE)
{
}

XsdSequence::XsdSequence(string name)
  : XsdNode(XSD_NODE_TYPE_SEQUENCE)
{
  setName(name);
}

void XsdSequence::setName(string name)
{
  _name = name;
}

void XsdSequence::setName(char *name)
{
  _name = name;
}

void XsdSequence::add(XsdElement *element)
{
  _children.push_back(element);
  _elements.push_back(element);
}

string XsdSequence::name()
{
  return _name;
}

std::vector<XsdElement*>::iterator XsdSequence::e_begin()
{
  return _elements.begin();
}

std::vector<XsdElement*>::iterator XsdSequence::e_end()
{
  return _elements.end();
}

int XsdSequence::e_size()
{
  return (int)_elements.size();
}

std::vector<XsdAttribute*>::iterator XsdSequence::a_begin()
{
  return _attributes.begin();
}

std::vector<XsdAttribute*>::iterator XsdSequence::a_end()
{
  return _attributes.end();
}

int XsdSequence::a_size()
{
  return (int)_attributes.size();
}

void XsdSequence::add(XsdAttribute *attribute)
{
  _attributes.push_back(attribute);
}

std::vector<XsdChoice*>::iterator XsdSequence::c_begin()
{
  return _choices.begin();
}

std::vector<XsdChoice*>::iterator XsdSequence::c_end()
{
  return _choices.end();
}

int XsdSequence::c_size()
{
  return (int)_choices.size();
}

void XsdSequence::add(XsdChoice *choice)
{
  _children.push_back(choice);
  _choices.push_back(choice);
}

std::vector<XsdRegularExpression*>::iterator XsdSequence::r_begin()
{
  return _regExps.begin();
}

std::vector<XsdRegularExpression*>::iterator XsdSequence::r_end()
{
  return _regExps.end();
}

int XsdSequence::r_size()
{
  return (int)_regExps.size();
}

void XsdSequence::add(XsdRegularExpression *regExp)
{
  _children.push_back(regExp);
  _regExps.push_back(regExp);
}

// interval
std::vector<XsdInterval*>::iterator XsdSequence::i_begin()
{
  return _intervals.begin();
}

std::vector<XsdInterval*>::iterator XsdSequence::i_end()
{
  return _intervals.end();
}

int XsdSequence::i_size()
{
  return (int)_intervals.size();
}

void XsdSequence::add(XsdInterval *interval)
{
  _children.push_back(interval);
  _intervals.push_back(interval);
}

// node

std::vector<XsdNode*>::iterator XsdSequence::n_begin()
{
  return _children.begin();
}

std::vector<XsdNode*>::iterator XsdSequence::n_end()
{
  return _children.end();
}

int XsdSequence::n_size()
{
  return (int)_children.size();
}

void XsdSequence::add(std::vector<XsdElement*> elements)
{
  for(std::vector<XsdElement*>::iterator i = elements.begin(); i != elements.end(); i++)
  {
    add(*i);
  }
}
