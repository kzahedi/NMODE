#include <nmode/ParseElement.h>

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

void ParseElement::add(ParseAttribute *attribute)
{
  push_back(attribute);
}

ParseAttribute* ParseElement::attribute(string name)
{
  for(std::vector<ParseAttribute*>::iterator i = begin(); i != end(); i++)
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

bool ParseElement::set(string name, double &value)
{
  if(attribute(name) != NULL)
  {
    double tmp = attribute(name)->realValue();
    if(tmp == value) return false;
    value = tmp;
    return true;
  }
  return false;
}

bool ParseElement::set(string name, string &value)
{
  if(attribute(name) != NULL)
  {
    string tmp = attribute(name)->value();
    if(tmp == value) return false;
    value = tmp;
    return true;
  }
  return false;
}

bool ParseElement::set(string name, bool &value)
{
  if(attribute(name) != NULL)
  {
    bool tmp = attribute(name)->boolValue();
    if(tmp == value) return false;
    value = tmp;
    return true;
  }
  return false;
}

bool ParseElement::set(string name, int &value)
{
  if(attribute(name) != NULL)
  {
    int tmp = attribute(name)->intValue();
    if(tmp == value) return false;
    value = tmp;
    return true;
  }
  return false;
}

bool ParseElement::set(string name, unsigned long &value)
{
  if(attribute(name) != NULL)
  {
    unsigned long tmp = attribute(name)->unsignedlongValue();
    if(tmp == value) return false;
    value = tmp;
    return true;
  }
  return false;
}

