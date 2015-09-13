#include "Module.h"

#include "base/macros.h"

#include <algorithm>
#include <glog/logging.h>


Node::Node()
{
  _type  = -1;
  _bias = 0.0;
}

Node::~Node()
{
}

void Node::setPosition(P3D position)
{
  _position = position;
}

void Node::setType(string type) throw (ENPException)
{
  _type = -1;
  if(type == "sensor")    _type = NODE_TYPE_SENSOR;
  if(type == "actuator")  _type = NODE_TYPE_ACTUATOR;
  if(type == "input")     _type = NODE_TYPE_INPUT;
  if(type == "output")    _type = NODE_TYPE_OUTPUT;
  if(type == "hidden")    _type = NODE_TYPE_HIDDEN;
  if(type == "connector") _type = NODE_TYPE_CONNECTOR;
  if(_type == -1) throw ENPException("Node::setType uknown type");
  _stype = type;
}

void Node::setLabel(string label)
{
  _label = label;
}

void Node::setTransferfunction(string tf)
{
  _transferfunction = tf;
}

P3D Node::position()
{
  return _position;
}

int Node::type()
{
  return _type;
}

string Node::stype()
{
  return _stype;
}

string Node::label()
{
  return _label;
}

string Node::transferfunction()
{
  return _transferfunction;
}



bool Node::contains(Edge *e)
{
  if(_in.empty()) return false;

  if(std::find(_in.begin(), _in.end(), e) != _in.end()) {
    return true;
  }
  return false;
}

bool Node::contains(Node *n)
{
  FORC(Edges, e, _in)
  {
    if((*e)->source() == n) return true;
  }
  return false;
}

void Node::setBias(double v)
{
  _bias = v;
}

double Node::bias()
{
  return _bias;
}


