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


#include "DataParseElement.h"

DataParseElement::DataParseElement(int type)
{
  _name = "";
  _type = type;
}

DataParseElement::~DataParseElement()
{
  for(unsigned int i = 0; i < size(); i++)
  {
    delete at(i);
  }
}

void DataParseElement::setName(string name)
{
  _name = name;
}

void DataParseElement::setName(char *name)
{
  _name = name;
}

string DataParseElement::name()
{
  return _name;
}

void DataParseElement::add(DataParseAttribute *attribute)
{
  push_back(attribute);
}

DataParseAttribute* DataParseElement::attribute(string name)
{
  for(std::vector<DataParseAttribute*>::iterator i = begin(); i != end(); i++)
  {
    if( (*i)->name() == name)
    {
      return (*i);
    }
  }
  return NULL;
}
bool DataParseElement::hasAttriute(string name)
{
  return attribute(name) != NULL;
}

bool DataParseElement::opening(string name)
{
  return _name == name && _type == YARS_DATA_PARSE_ELEMENT_TYPE_OPENING;
}

bool DataParseElement::opening(char *name)
{
  return opening(string(name));
}

bool DataParseElement::closing(string name)
{
  return _name == name && _type == YARS_DATA_PARSE_ELEMENT_TYPE_CLOSING;
}

bool DataParseElement::closing(char *name)
{
  return closing(string(name));
}

void DataParseElement::set(string name, double &value)
{
  if(attribute(name) != NULL)
  {
    value = attribute(name)->realValue();
  }
}

void DataParseElement::set(string name, string &value)
{
  if(attribute(name) != NULL)
  {
    value = attribute(name)->value();
  }
}

void DataParseElement::set(string name, bool &value)
{
  if(attribute(name) != NULL)
  {
    value = attribute(name)->boolValue();
  }
}

void DataParseElement::set(string name, int &value)
{
  if(attribute(name) != NULL)
  {
    value = attribute(name)->intValue();
  }
}

void DataParseElement::set(string name, unsigned long &value)
{
  if(attribute(name) != NULL)
  {
    value = attribute(name)->unsignedlongValue();
  }
}

