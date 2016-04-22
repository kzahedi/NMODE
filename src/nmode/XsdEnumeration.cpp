#include <nmode/XsdEnumeration.h>

XsdEnumeration::XsdEnumeration(string name, string type)
  : XsdNode(XSD_NODE_TYPE_ENUMERATION)
{
  _name = name;
  _type = type;
}

void XsdEnumeration::add(string value)
{
  _value.push_back(value);
}

std::vector<string>::iterator XsdEnumeration::v_begin()
{
  return _value.begin();
}

std::vector<string>::iterator XsdEnumeration::v_end()
{
  return _value.end();
}

string XsdEnumeration::name()
{
  return _name;
}

string XsdEnumeration::type()
{
  return _type;
}
