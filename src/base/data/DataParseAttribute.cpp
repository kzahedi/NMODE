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

