#include <nmode/XsdElement.h>

#include <sstream>

XsdElement::XsdElement()
  : XsdNode(XSD_NODE_TYPE_ELEMENT)
{
  _name = "";
  _type = "";
  _minOccurs = "";
  _maxOccurs = "";
  _minOccursGiven = false;
  _maxOccursGiven = false;
}

XsdElement::XsdElement(string name, string type, int minOccurs, int maxOccurs)
  : XsdNode(XSD_NODE_TYPE_ELEMENT)
{
  _name = name;
  _type = type;
  stringstream oss;
  oss << minOccurs;
  _minOccurs = oss.str();
  _minOccursGiven = true;

  oss.str("");
  oss << maxOccurs;
  _maxOccurs = oss.str();
  _maxOccursGiven = true;
}

XsdElement::XsdElement(string name, string type, int minOccurs)
  : XsdNode(XSD_NODE_TYPE_ELEMENT)
{
  _name = name;
  _type = type;
  stringstream oss;
  oss << minOccurs;
  _minOccurs = oss.str();
  _minOccursGiven = true;

  _maxOccurs = TAG_XSD_UNBOUNDED;
  _maxOccursGiven = true;
}

XsdElement::XsdElement(string name, string type, string minOccurs, string maxOccurs)
  : XsdNode(XSD_NODE_TYPE_ELEMENT)
{
  _name = name;
  _type = type;
  _minOccursGiven = false;
  _maxOccursGiven = false;
  if(minOccurs.length() > 0)
  {
    _minOccurs = minOccurs;
    _minOccursGiven = true;
  }
  if(maxOccurs.length() > 0)
  {
    _maxOccurs = maxOccurs;
    _maxOccursGiven = true;
  }
}

XsdElement::XsdElement(string name, string type, int minOccurs, string maxOccurs)
  : XsdNode(XSD_NODE_TYPE_ELEMENT)
{
  _name = name;
  _type = type;
  _minOccursGiven = false;
  _maxOccursGiven = false;
  stringstream oss;
  oss << minOccurs;
  _minOccurs = oss.str();
  _minOccursGiven = true;

  if(maxOccurs.length() > 0)
  {
    _maxOccurs = maxOccurs;
    _maxOccursGiven = true;
  }
}
void XsdElement::setName(string name)
{
  _name = name;
}

void XsdElement::setType(string type)
{
  _type = type;
}

void XsdElement::setMinOccurs(string minOccurs)
{
  _minOccurs      = minOccurs;
  _minOccursGiven = true;
}

void XsdElement::setMinOccurs(int minOccurs)
{
  stringstream oss;
  oss << minOccurs;
  setMinOccurs(oss.str());
}

void XsdElement::setMaxOccurs(string maxOccurs)
{
  _maxOccurs      = maxOccurs;
  _maxOccursGiven = true;
}

void XsdElement::setMaxOccurs(int maxOccurs)
{
  stringstream oss;
  oss << maxOccurs;
  setMaxOccurs(oss.str());
}

string XsdElement::name()
{
  return _name;
}

string XsdElement::minOccurs()
{
  return _minOccurs;
}

bool XsdElement::minOccursGiven()
{
  return _minOccursGiven;
}

string XsdElement::maxOccurs()
{
  return _maxOccurs;
}

bool XsdElement::maxOccursGiven()
{
  return _maxOccursGiven;
}

string XsdElement::type()
{
  return _type;
}

void XsdElement::add(XsdAttribute *attribute)
{
  _attributes.push_back(attribute);
}

std::vector<XsdAttribute*>::iterator XsdElement::a_begin()
{
  return _attributes.begin();
}

std::vector<XsdAttribute*>::iterator XsdElement::a_end()
{
  return _attributes.end();
}

int XsdElement::a_size()
{
  return _attributes.size();
}
