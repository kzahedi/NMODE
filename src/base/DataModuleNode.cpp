#include "DataModuleNode.h"

#include "macros.h"

#include <iostream>
#include <glog/logging.h>

#define TAG_X                           (char*)"x"
#define TAG_Y                           (char*)"y"
#define TAG_Z                           (char*)"z"
#define TAG_NAME                        (char*)"name"
#define TAG_VALUE                       (char*)"value"
#define TAG_TYPE                        (char*)"type"
// #define TAG_OUTPUT                      (char*)"output"
#define TAG_NAME                        (char*)"name"
#define TAG_TANH                        (char*)"tanh"
#define TAG_SIGM                        (char*)"sigm"
#define TAG_ID                          (char*)"id"
#define TAG_TYPE_DEFINITION             (char*)"type_definition"
#define TAG_TYPE_CONNECTOR_DEFINITION   (char*)"type_connector_definition"
#define TAG_LABEL                       (char*)"label"
#define TAG_POSITION                    (char*)"position"
#define TAG_XYZ_DEFINITION              (char*)"xyz_definition"
#define TAG_TRANSFERFUNCTION            (char*)"transferfunction"
#define TAG_TRANSFERFUNCTION_DEFINITION (char*)"transferfunction_definition"
#define TAG_BIAS                        (char*)"bias"
#define TAG_BIAS_DEFINITION             (char*)"bias_definition"
#define TAG_TFUNCTION_ENUMERATION       (char*)"tfunction_enum_definition"

using namespace std;

DataModuleNode::DataModuleNode(DataNode *parent)
  : DataNode(parent)
{ }

DataModuleNode::~DataModuleNode()
{ }


void DataModuleNode::add(DataParseElement *element)
{
  VLOG(100) << "parsing " << element->name();
  if(element->closing(TAG_MODULE_NODE))
  {
    VLOG(100) << "closing " << _label;
    current = parent;
    return;
  }

  if(element->opening(TAG_MODULE_NODE))
  {
    element->set(TAG_TYPE,  _type);
    element->set(TAG_LABEL, _label);
    VLOG(100) << "setting type = " << _type << " and label = " << _label;
  }

  if(element->opening(TAG_POSITION))
  {
    element->set(TAG_X, _position.x);
    element->set(TAG_Y, _position.y);
    element->set(TAG_Z, _position.z);
    VLOG(100) << "setting position to " << _position;
  }

  if(element->opening(TAG_TRANSFERFUNCTION))
  {
    element->set(TAG_NAME, _transferfunction);
    VLOG(100) << "setting transfer-function to " << _transferfunction;
  }

  if(element->opening(TAG_BIAS))
  {
    element->set(TAG_BIAS, _bias);
    VLOG(100) << "setting bias to " << _bias;
  }
}

void DataModuleNode::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_MODULE_NODE_DEFINITION);
  root->add(NA(TAG_TYPE,             TAG_TYPE_DEFINITION,             true));
  root->add(NA(TAG_LABEL,            TAG_XSD_STRING,                  true));
  root->add(NE(TAG_POSITION,         TAG_XYZ_DEFINITION,              0, 1));
  root->add(NE(TAG_TRANSFERFUNCTION, TAG_TRANSFERFUNCTION_DEFINITION, 0, 1));
  root->add(NE(TAG_BIAS,             TAG_BIAS_DEFINITION,             0, 1));
  spec->add(root);

  XsdSequence *tfunc = new XsdSequence(TAG_TRANSFERFUNCTION_DEFINITION);
  tfunc->add(NA(TAG_NAME, TAG_TFUNCTION_ENUMERATION, true));
  spec->add(tfunc);

  XsdSequence *bias = new XsdSequence(TAG_BIAS_DEFINITION);
  bias->add(NA(TAG_VALUE, TAG_XSD_DECIMAL, true));
  spec->add(bias);

  XsdEnumeration *tfuncenum = new XsdEnumeration(TAG_TFUNCTION_ENUMERATION,
                                                 TAG_XSD_STRING);
  tfuncenum->add(TAG_TANH);
  tfuncenum->add(TAG_SIGM);
  tfuncenum->add(TAG_ID);
  spec->add(tfuncenum);

  XsdEnumeration *type = new XsdEnumeration(TAG_TYPE_DEFINITION,
                                            TAG_XSD_STRING);
  type->add(TAG_SENSOR);
  type->add(TAG_ACTUATOR);
  type->add(TAG_INPUT);
  // type->add(TAG_OUTPUT);
  type->add(TAG_HIDDEN);
  spec->add(type);

  XsdEnumeration *connectorType = new XsdEnumeration(TAG_TYPE_CONNECTOR_DEFINITION,
                                                     TAG_XSD_STRING);
  type->add(TAG_CONNECTOR);
  spec->add(connectorType);

}

string DataModuleNode::type()
{
  return _type;
}

void DataModuleNode::setType(string t)
{
  _type = t;
}

string DataModuleNode::label()
{
  return _label;
}

void DataModuleNode::setLabel(string l)
{
  _label = l;
}

P3D DataModuleNode::position()
{
  return _position;
}

string DataModuleNode::transferfunction()
{
  return _transferfunction;
}

double DataModuleNode::bias()
{
  return _bias;
}

void DataModuleNode::setBias(double b)
{
  _bias = b;
}

void DataModuleNode::setPosition(P3D p)
{
  _position = p;
}


void DataModuleNode::setTransferfunction(string tf)
{
  _transferfunction = tf;
}


string DataModuleNode::moduleName()
{
  return _moduleName;
}

void DataModuleNode::setModuleName(string mn)
{
  _moduleName = mn;
}

string DataModuleNode::nodeName()
{
  return _nodeName;
}

void DataModuleNode::setNodeName(string nn)
{
  _nodeName = nn;
}

bool DataModuleNode::operator==(const DataModuleNode o)
{
  return (_position         == o._position &&
          _label            == o._label    &&
          _type             == o._type     &&
          _transferfunction == o._transferfunction);
}

bool DataModuleNode::operator!=(const DataModuleNode o)
{
  return (_position         != o._position ||
          _label            != o._label    ||
          _type             != o._type     ||
          _transferfunction != o._transferfunction);
}

bool DataModuleNode::contains(DataModuleEdge *e)
{
  if(_in.empty()) return false;

  if(std::find(_in.begin(), _in.end(), e) != _in.end()) {
    return true;
  }
  return false;
}

bool DataModuleNode::contains(DataModuleNode *n)
{
  FORC(DataModuleEdges, e, _in)
  {
    if((*e)->sourceNode() == n) return true;
  }
  return false;
}

DataModuleEdges::iterator DataModuleNode::e_begin()
{
  return _in.begin();
}

DataModuleEdges::iterator DataModuleNode::e_end()
{
  return _in.end();
}

int DataModuleNode::e_size()
{
  return _in.size();
}

DataModuleEdge* DataModuleNode::edge(int index)
{
  return _in[index];
}

void DataModuleNode::addEdge(DataModuleEdge *e)
{
  _in.push_back(e);
}

void DataModuleNode::removeEdge(DataModuleNode *n)
{
  FORC(DataModuleEdges, e, _in)
  {
    if((*e)->sourceNode()->label() == n->label())
    {
      if(removeEdge(*e))
      {
        return;
      }
    }
  }
}

bool DataModuleNode::removeEdge(DataModuleEdge *e)
{
  DataModuleEdges::iterator ei = std::find(_in.begin(), _in.end(), e);
  if(ei != _in.end())
  {
    _in.erase(ei);

    VLOG(20) << "   removing input edge with "
      << e->sourceNode()->label() << " -> "
      << e->destinationNode()->label()
      << " with " << e->weight();
    return true;
  }
  return false;
}

bool DataModuleNode::isSource()
{
  return (_type == TAG_ACTUATOR  ||
          _type == TAG_SENSOR    ||
          _type == TAG_INPUT     ||
          _type == TAG_CONNECTOR ||
          _type == TAG_HIDDEN);
}

bool DataModuleNode::isDestination()
{
  return (_type == TAG_ACTUATOR  ||
          // _type == TAG_OUTPUT    ||
          _type == TAG_CONNECTOR ||
          _type == TAG_HIDDEN);
}
