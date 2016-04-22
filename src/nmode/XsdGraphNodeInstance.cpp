#include <nmode/XsdGraphNodeInstance.h>

#include <sstream>

int XsdGraphNodeInstance::_index = 0;

XsdGraphNodeInstance::XsdGraphNodeInstance(string name, string label, XsdGraphNode *node)
{
  stringstream oss;
  oss << name << "_" << _index++;

  _name       = name;
  _label      = label;
  _node       = node;
  _port       = 0;
  _uniqueName = oss.str();
};

string XsdGraphNodeInstance::uniqueName()
{
  return _uniqueName;
};

string XsdGraphNodeInstance::name()
{
  return _name;
};

string XsdGraphNodeInstance::label()
{
  return _node->customLabel(_name);
};

int XsdGraphNodeInstance::port()
{
  return _port;
}

void XsdGraphNodeInstance::setPort(int port)
{
  _port = port;
}
