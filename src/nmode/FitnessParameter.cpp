#include "FitnessParameter.h"

#include <stdio.h>
#include <stdlib.h>

# define TAG_NAME (char*)"name"

FitnessParameter::FitnessParameter(XsdParseNode *parent)
  : XsdParseNode(parent)
{

}

void FitnessParameter::add(ParseElement *element)
{
  if(element->closing(TAG_FITNESS_PARAMETER))
  {
    current = parent;
  }

  if(element->opening(TAG_FITNESS_PARAMETER))
  {
    element->set(TAG_NAME,  _name);
    element->set(TAG_VALUE, _value);
  }
}

string FitnessParameter::name()
{
  return _name;
}

string FitnessParameter::value()
{
  return _value;
}

int FitnessParameter::intValue()
{
  return atoi(_value.c_str());
}

bool FitnessParameter::boolValue()
{
  return _value == "true";
}

double FitnessParameter::realValue()
{
  return (double)atof(_value.c_str());
}

void FitnessParameter::createXsd()
{

}

FitnessParameter *FitnessParameter::copy()
{
  FitnessParameter *copy = new FitnessParameter(NULL);
  copy->_name = _name;
  copy->_value = _value;
  return copy;
}

void FitnessParameter::resetTo(const FitnessParameter *other)
{
  _name  = other->_name;
  _value = other->_value;
}
