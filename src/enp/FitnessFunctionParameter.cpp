#include "FitnessFunctionParameter.h"

#include <stdio.h>
#include <stdlib.h>

# define YARS_STRING_NAME   (char*)"name"

FitnessFunctionParameter::FitnessFunctionParameter(DataNode *parent)
  : XsdParseNode(parent)
{

}

void FitnessFunctionParameter::add(FitnessFunctionParseElement *element)
{
  if(element->closing(YARS_STRING_PARAMETER))
  {
    current = parent;
  }
  if(element->opening(YARS_STRING_PARAMETER))
  {
    element->set(YARS_STRING_NAME, _name);
    element->set(YARS_STRING_VALUE, _value);
  }
}

string FitnessFunctionParameter::name()
{
  return _name;
}

string FitnessFunctionParameter::value()
{
  return _value;
}

int FitnessFunctionParameter::intValue()
{
  return atoi(_value.c_str());
}

bool FitnessFunctionParameter::boolValue()
{
  return _value == "true";
}

yReal FitnessFunctionParameter::realValue()
{
  return (yReal)atof(_value.c_str());
}

void FitnessFunctionParameter::createXsd()
{

}

FitnessFunctionParameter *FitnessFunctionParameter::copy()
{
  FitnessFunctionParameter *copy = new FitnessFunctionParameter(NULL);
  copy->_name = _name;
  copy->_value = _value;
  return copy;
}

void FitnessFunctionParameter::resetTo(const FitnessFunctionParameter *other)
{
  _name  = other->_name;
  _value = other->_value;
}
