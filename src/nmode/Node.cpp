#include <nmode/Node.h>

#include <nmode/macros.h>

#include <iostream>
#include <glog/logging.h>

#define TAG_X                           (char*)"x"
#define TAG_Y                           (char*)"y"
#define TAG_Z                           (char*)"z"
#define TAG_NAME                        (char*)"name"
#define TAG_VALUE                       (char*)"value"
#define TAG_TYPE                        (char*)"type"
#define TAG_INACTIVE                    (char*)"inactive"
#define TAG_NAME                        (char*)"name"
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
#define TAG_TRUE_FALSE_DEFINITION       (char*)"true_definition"

using namespace std;

Node::Node(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _isSource      = false;
  _isDestination = false;
  _bias          = 0.0;
  _inactive      = false;
}

Node::~Node()
{
  _in.resize(0);
}

void Node::add(ParseElement *element)
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
    element->set(TAG_TYPE,     _type);
    element->set(TAG_LABEL,    _label);
    element->set(TAG_INACTIVE, _inactive);
    VLOG(100) << "setting type = " << _type << " and label = " << _label;

    if(_type == TAG_ACTUATOR || _type == TAG_SENSOR ||
       _type == TAG_INPUT    || _type == TAG_HIDDEN ||
       _type == TAG_CONNECTOR)
    {
      _isSource = true;
    }

    if(_type == TAG_ACTUATOR || _type == TAG_OUTPUT ||
       _type == TAG_HIDDEN   || _type == TAG_CONNECTOR)
    {
      _isDestination = true;
    }
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
    element->set(TAG_VALUE, _bias);
    VLOG(100) << "setting bias to " << _bias;
  }
}

void Node::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_MODULE_NODE_DEFINITION);
  root->add(NA(TAG_TYPE,             TAG_TYPE_DEFINITION,             true));
  root->add(NA(TAG_LABEL,            TAG_XSD_STRING,                  true));
  root->add(NA(TAG_INACTIVE,         TAG_TRUE_FALSE_DEFINITION,       false));
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
  type->add(TAG_OUTPUT);
  type->add(TAG_HIDDEN);
  type->add(TAG_CONNECTOR);
  spec->add(type);

  // XsdEnumeration *connectorType = new XsdEnumeration(TAG_TYPE_CONNECTOR_DEFINITION,
                                                     // TAG_XSD_STRING);
  // type->add(TAG_CONNECTOR);
  // spec->add(connectorType);
}

string Node::type()
{
  return _type;
}

void Node::setType(string t) throw (NMODEException)
{
  if(t == TAG_ACTUATOR ||
     t == TAG_SENSOR   ||
     t == TAG_INPUT    ||
     t == TAG_OUTPUT   ||
     t == TAG_HIDDEN   ||
     t == TAG_CONNECTOR)
  {
    _type = t;
  }
  else
  {
    stringstream sst;
    sst << "Unknown node type \"" << t << "\" given";
    throw NMODEException(sst.str());
  }
  if(_type == TAG_ACTUATOR || _type == TAG_SENSOR ||
     _type == TAG_INPUT    || _type == TAG_HIDDEN ||
     _type == TAG_CONNECTOR)
  {
    _isSource = true;
  }

  if(_type == TAG_ACTUATOR || _type == TAG_OUTPUT ||
     _type == TAG_HIDDEN   || _type == TAG_CONNECTOR)
  {
    _isDestination = true;
  }
}

string Node::label()
{
  return _label;
}

void Node::setLabel(string l)
{
  _label = l;
}

P3D Node::position()
{
  return _position;
}

string Node::transferfunction()
{
  return _transferfunction;
}

double Node::bias()
{
  return _bias;
}

void Node::setBias(double b)
{
  _bias = b;
}

void Node::setPosition(P3D p)
{
  _position = p;
}

void Node::setTransferfunction(string tf)
{
  _transferfunction = tf;
}


string Node::moduleName()
{
  return _moduleName;
}

void Node::setModuleName(string mn)
{
  _moduleName = mn;
}

string Node::nodeName()
{
  return _nodeName;
}

void Node::setNodeName(string nn)
{
  _nodeName = nn;
}

bool Node::operator==(const Node o) const
{
  return (_position         == o._position &&
          _label            == o._label    &&
          _type             == o._type     &&
          _transferfunction == o._transferfunction);
}

bool Node::operator!=(const Node o) const
{
  return (_position         != o._position ||
          _label            != o._label    ||
          _type             != o._type     ||
          _transferfunction != o._transferfunction);
}

// bool Node::contains(Edge *e)
// {
  // if(_in.empty()) return false;
  // if(std::find(_in.begin(), _in.end(), e) != _in.end()) return true;
  // return false;
// }

bool Node::contains(Node *n)
{
  FORC(Edges, e, _in)
    if((*e)->sourceNode() == n)
      return true;
  return false;
}

Edges::iterator Node::e_begin()
{
  return _in.begin();
}

Edges::iterator Node::e_end()
{
  return _in.end();
}

int Node::e_size()
{
  return _in.size();
}

Edge* Node::edge(int index)
{
  return _in[index];
}

void Node::addEdge(Edge *e)
{
  _in.push_back(e);
}

void Node::removeEdge(Node *n)
{
  FORC(Edges, e, _in)
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

bool Node::removeEdge(Edge *e)
{
  Edges::iterator ei = std::find(_in.begin(), _in.end(), e);
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

bool Node::isSource()
{
  return _isSource;
}

bool Node::isDestination()
{
  return _isDestination;
}


Node* Node::copy()
{
  Node *copy              = new Node(NULL);
  copy->_type             = _type;
  copy->_label            = _label;
  copy->_position         = _position;
  copy->_transferfunction = _transferfunction;
  copy->_nodeName         = _nodeName;
  copy->_moduleName       = _moduleName;
  copy->_bias             = _bias;
  copy->_isSource         = _isSource;
  copy->_isDestination    = _isDestination;
  copy->_inactive         = _inactive;

  // edges must be copied outside of here
  return copy;
}

void Node::setIsSource(bool s)
{
  _isSource = s;
}

void Node::setIsDestination(bool d)
{
  _isDestination = d;
}

void Node::setInactive(bool b)
{
  _inactive = b;
}

bool Node::isInactive()
{
  return _inactive;
}

bool Node::equal(Node* other)
{
  EQUAL_TEST_DOUBLE(_bias,          other->bias(),         "Node Bias mismatch");
  EQUAL_TEST(_position,         other->position(),         "Node Position mismatch");
  EQUAL_TEST(_isDestination,    other->isDestination(),    "Node isDestination mismatch");
  EQUAL_TEST(_isSource,         other->isSource(),         "Node isSource mismatch");
  EQUAL_TEST(_inactive,         other->isInactive(),       "Node isInactive mismatch");
  EQUAL_TEST(_label,            other->label(),            "Node Label mismatch");
  EQUAL_TEST(_moduleName,       other->moduleName(),       "Node Module Name mismatch");
  EQUAL_TEST(_nodeName,         other->nodeName(),         "Node Node Name mismatch");
  EQUAL_TEST(_transferfunction, other->transferfunction(), "Node Transfer Function mismatch");
  EQUAL_TEST(_type,             other->type(),             "Node Type mismatch");
  return true;
}
