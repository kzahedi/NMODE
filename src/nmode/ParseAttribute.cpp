#include <nmode/ParseAttribute.h>

#include <stdio.h>
#include <stdlib.h>


ParseAttribute::ParseAttribute()
{
  _name  = "";
  _value = "";
}

ParseAttribute::~ParseAttribute()
{
  // nothing to be done
}

void ParseAttribute::setName(string name)
{
  _name = name;
}

void ParseAttribute::setValue(string value)
{
  _value = value;
}

string ParseAttribute::name()
{
  return _name;
}

string ParseAttribute::value()
{
  return _value;
}

int ParseAttribute::intValue()
{
  return atoi(_value.c_str());
}

unsigned long ParseAttribute::unsignedlongValue()
{
  return (unsigned long)atoi(_value.c_str());
}

bool ParseAttribute::boolValue()
{
  return _value == "true";
}

double ParseAttribute::realValue()
{
  return (double)atof(_value.c_str());
}

