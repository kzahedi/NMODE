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


#include "DataParseAttribute.h"

#include <stdio.h>
#include <stdlib.h>


DataParseAttribute::DataParseAttribute()
{
  _name  = "";
  _value = "";
}

DataParseAttribute::~DataParseAttribute()
{
  // nothing to be done
}

void DataParseAttribute::setName(string name)
{
  _name = name;
}

void DataParseAttribute::setValue(string value)
{
  _value = value;
}

string DataParseAttribute::name()
{
  return _name;
}

string DataParseAttribute::value()
{
  return _value;
}

int DataParseAttribute::intValue()
{
  return atoi(_value.c_str());
}

unsigned long DataParseAttribute::unsignedlongValue()
{
  return (unsigned long)atoi(_value.c_str());
}

bool DataParseAttribute::boolValue()
{
  return _value == "true";
}

double DataParseAttribute::realValue()
{
  return (double)atof(_value.c_str());
}

