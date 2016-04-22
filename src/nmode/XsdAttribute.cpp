#include <nmode/XsdAttribute.h>

XsdAttribute::XsdAttribute()
  : XsdNode(XSD_NODE_TYPE_ATTRIBUTE)
{
  _name = "";
  _type = "";
  _required = true;
}

XsdAttribute::XsdAttribute(string name, string type, bool required)
  : XsdNode(XSD_NODE_TYPE_ATTRIBUTE)
{
  _name     = name;
  _type     = type;
  _required = required;
}

void XsdAttribute::setName(string name)
{
  _name = name;
}

string XsdAttribute::name()
{
  return _name;
}

void XsdAttribute::setType(string type)
{
  _type = type;
}

string XsdAttribute::type()
{
  return _type;
}

void XsdAttribute::setRequired(bool required)
{
  _required = required;
}

bool XsdAttribute::required()
{
  return _required;
}
