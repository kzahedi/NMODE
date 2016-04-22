#include <nmode/XsdRegularExpression.h>

#include <sstream>

XsdRegularExpression::XsdRegularExpression(string name, string type, string regExp)
  : XsdNode(XSD_NODE_TYPE_REG_EXP)
{
  _name   = name;
  _type   = type;
  _regExp = regExp;
}

string XsdRegularExpression::regExp()
{
  return _regExp;
}

string XsdRegularExpression::name()
{
  return _name;
}

string XsdRegularExpression::type()
{
  return _type;
}
