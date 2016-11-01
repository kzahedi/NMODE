#include "XsdGraphLink.h"

#include <iostream>

using namespace std;

XsdGraphLink::XsdGraphLink()
{
  _source      = NULL;
  _destination = NULL;
}

string XsdGraphLink::label()
{
  return _label;
}
void XsdGraphLink::setLabel(string label)
{
  _label = label;
}

XsdGraphNode* XsdGraphLink::source()
{
  return _source;
}

XsdGraphNode* XsdGraphLink::destination()
{
  return _destination;
}

string XsdGraphLink::destinationName()
{
  return _destinationName;
}

void XsdGraphLink::setDestinationName(string dName)
{
  _destinationName = dName;
}

void XsdGraphLink::setSource(XsdGraphNode *source)
{
  _source = source;
}

void XsdGraphLink::setDestination(XsdGraphNode *destination)
{
  _destination = destination;
}

