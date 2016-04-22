#include <nmode/XsdGraphNode.h>

#include <sstream>

XsdGraphNode::XsdGraphNode() { }

void XsdGraphNode::setUniqueNodeName(string n)
{
  _uniqueName = n;
}

string XsdGraphNode::uniqueNodeName()
{
  return _uniqueName;
}

bool XsdGraphNode::hasDefinition(string type)
{
  return type.find("definition") != string::npos;
}
