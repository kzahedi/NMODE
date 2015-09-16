#include "ParseElement.h"

ParseElement::ParseElement(int type)
{
  _name = "";
  _type = type;
}

ParseElement::~ParseElement()
{
  for(unsigned int i = 0; i < size(); i++)
  {
    delete at(i);
  }
}

void ParseElement::setName(string name)
{
  _name = name;
}

void ParseElement::setName(char *name)
{
  _name = name;
}

string ParseElement::name()
{
  return _name;
}

void ParseElement::add(DataParseAttribute *attribute)
{
  push_back(attribute);
}

DataParseAttribute* ParseElement::attribute(string name)
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
bool ParseElement::hasAttriute(string name)
{
  return attribute(name) != NULL;
}

bool ParseElement::opening(string name)
{
  return _name == name && _type == YARS_DATA_PARSE_ELEMENT_TYPE_OPENING;
}

bool ParseElement::opening(char *name)
{
  return opening(string(name));
}

bool ParseElement::closing(string name)
{
  return _name == name && _type == YARS_DATA_PARSE_ELEMENT_TYPE_CLOSING;
}

bool ParseElement::closing(char *name)
{
  return closing(string(name));
}

void ParseElement::set(string name, double &value)
{
  if(attribute(name) != NULL)
  {
    value = attribute(name)->realValue();
  }
}

void ParseElement::set(string name, string &value)
{
  if(attribute(name) != NULL)
  {
    value = attribute(name)->value();
  }
}

void ParseElement::set(string name, bool &value)
{
  if(attribute(name) != NULL)
  {
    value = attribute(name)->boolValue();
  }
}

void ParseElement::set(string name, int &value)
{
  if(attribute(name) != NULL)
  {
    value = attribute(name)->intValue();
  }
}

void ParseElement::set(string name, unsigned long &value)
{
  if(attribute(name) != NULL)
  {
    value = attribute(name)->unsignedlongValue();
  }
}

