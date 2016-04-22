#include <nmode/XsdInterval.h>

#include <sstream>

XsdInterval::XsdInterval(string name, string type, int minimum, int maximum)
  : XsdNode(XSD_NODE_TYPE_INTERVAL)
{
  stringstream min;
  min << minimum;
  stringstream max;
  max << maximum;
  __init(name, type, min.str(), max.str());
}

XsdInterval::XsdInterval(string name, string type, string minimum, string maximum)
  : XsdNode(XSD_NODE_TYPE_INTERVAL)
{
  __init(name, type, minimum, maximum);
}

void XsdInterval::__init(string name, string type, string min, string max)
{
  _name = name;
  _type = type;
  _min  = min;
  _max  = max;

}

string XsdInterval::minimum()
{
  return _min;
}

string XsdInterval::maximum()
{
  return _max;
}

string XsdInterval::name()
{
  return _name;
}

string XsdInterval::type()
{
  return _type;
}
