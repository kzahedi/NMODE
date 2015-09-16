#include "Module.h"

#include "macros.h"

#include <iostream>
#include <string>
#include <glog/logging.h>

#define TAG_NAME                   (char*)"name"
#define NO_NAME                    (char*)""
#define OPTION_A                   (char*)"option_a"
#define OPTION_B                   (char*)"option_b"

#define TAG_MODULE_COPY            (char*)"copy"
#define TAG_MODULE_COPY_DEFINITION (char*)"copy_definition"
#define TAG_MODULE_MIRROR          (char*)"mirror"
#define TAG_MODULE_ROTATE          (char*)"rotate"
#define TAG_MODULE_TRANSLATE       (char*)"translate"
#define TAG_MODULE_P3D_DEFINITION  (char*)"p3d_definition"
#define TAG_MODULE_B3D_DEFINITION  (char*)"b3d_definition"
#define TAG_TRUE_FALSE_DEFINITION  (char*)"true_definition"

#define TAG_CONNECTOR              (char*)"connector"

#define TAG_X                      (char*)"x"
#define TAG_Y                      (char*)"y"
#define TAG_Z                      (char*)"z"

using namespace std;

Module::Module(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _mirrorAxes   = new bool[3];
  _isCopy   = false;
  _isLinked = false;
  _globalId = 0;
  _modified = false;
}

Module::~Module()
{
  delete _mirrorAxes;
}

void Module::add(ParseElement *element)
{

  VLOG(100) << "parsing " << element->name();
  if(element->closing(TAG_MODULE))
  {
    // __linkConnectorNeurons();
    current = parent;
    return;
  }

  if(element->opening(TAG_MODULE))
  {
    element->set(TAG_NAME, _name);
    VLOG(100) << "setting name to " << _name;
  }

  if(element->opening(TAG_MODULE_NODE))
  {
    VLOG(100) << "found " << TAG_MODULE_NODE;
    Node *node = new Node(this);
    _nodes.push_back(node);
    current = node;
    node->add(element);
  }

  if(element->opening(TAG_MODULE_EDGE))
  {
    VLOG(100) << "found " << TAG_MODULE_EDGE;
    Edge *edge = new Edge(this);
    _edges.push_back(edge);
    current = edge;
    edge->add(element);
  }

  if(element->opening(TAG_MODULE_ROTATE))
  {
    VLOG(100) << "found " << TAG_MODULE_ROTATE;
    P3D r;
    element->set(TAG_X, r.x);
    element->set(TAG_Y, r.y);
    element->set(TAG_Z, r.z);
    _rotation << r;
    VLOG(100) << "  found " << _rotation;
  }

  if(element->opening(TAG_MODULE_MIRROR))
  {
    VLOG(100) << "found " << TAG_MODULE_MIRROR;
    P3D r;
    element->set(TAG_X, _mirrorAxes[0]);
    element->set(TAG_Y, _mirrorAxes[1]);
    element->set(TAG_Z, _mirrorAxes[2]);
    VLOG(100) << "found " << _mirrorAxes[0] << " " << _mirrorAxes[1] << " " << _mirrorAxes[2];
  }

  if(element->opening(TAG_MODULE_TRANSLATE))
  {
    VLOG(100) << "found " << TAG_MODULE_TRANSLATE;
    element->set(TAG_X, _translation.x);
    element->set(TAG_Y, _translation.y);
    element->set(TAG_Z, _translation.z);
    VLOG(100) << "  found " << _translation;
  }

  if(element->opening(TAG_MODULE_COPY))
  {
    VLOG(100) << "found " << TAG_MODULE_COPY;
    element->set(TAG_NAME, _ref);
    VLOG(100) << "  found " << _ref;
    _isCopy = true;
  }
}

void Module::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_MODULE_DEFINITION);
  root->add(NA(TAG_NAME,        TAG_XSD_STRING,             true));
  spec->add(root);

  XsdChoice *options = new XsdChoice(NO_NAME, 1, 1);
  root->add(options);

  XsdSequence *optionA = new XsdSequence(OPTION_A);
  optionA->add(NE(TAG_MODULE_NODE, TAG_MODULE_NODE_DEFINITION, 1, TAG_XSD_UNBOUNDED));
  optionA->add(NE(TAG_MODULE_EDGE, TAG_MODULE_EDGE_DEFINITION, 0, TAG_XSD_UNBOUNDED));
  options->add(optionA);

  XsdSequence *optionB = new XsdSequence(OPTION_B);
  optionB->add(NE(TAG_MODULE_COPY,      TAG_MODULE_COPY_DEFINITION, 1,1));
  optionB->add(NE(TAG_MODULE_MIRROR,    TAG_MODULE_B3D_DEFINITION,  0,1));
  optionB->add(NE(TAG_MODULE_ROTATE,    TAG_MODULE_P3D_DEFINITION,  0,1));
  optionB->add(NE(TAG_MODULE_TRANSLATE, TAG_MODULE_P3D_DEFINITION,  0,1));
  options->add(optionB);

  XsdSequence *p3d = new XsdSequence(TAG_MODULE_P3D_DEFINITION);
  p3d->add(NA(TAG_X, TAG_XSD_DECIMAL, false));
  p3d->add(NA(TAG_Y, TAG_XSD_DECIMAL, false));
  p3d->add(NA(TAG_Z, TAG_XSD_DECIMAL, false));
  spec->add(p3d);

  XsdSequence *b3d = new XsdSequence(TAG_MODULE_B3D_DEFINITION);
  b3d->add(NA(TAG_X, TAG_TRUE_FALSE_DEFINITION, false));
  b3d->add(NA(TAG_Y, TAG_TRUE_FALSE_DEFINITION, false));
  b3d->add(NA(TAG_Z, TAG_TRUE_FALSE_DEFINITION, false));
  spec->add(b3d);

  Node::createXsd(spec);
}

string Module::name()
{
  return _name;
}

Nodes::iterator Module::n_begin()
{
  return _nodes.begin();
}

Nodes::iterator Module::n_end()
{
  return _nodes.end();
}

int Module::n_size()
{
  return _nodes.size();
}

Nodes Module::nodes()
{
  return _nodes;
}

Edges::iterator Module::e_begin()
{
  return _edges.begin();
}

Edges::iterator Module::e_end()
{
  return _edges.end();
}

int Module::e_size()
{
  return _edges.size();
}

Edges Module::edges()
{
  return _edges;
}

string Module::ref()
{
  return _ref;
}

// void Module::__linkConnectorNeurons()
// {
  // FORC(Nodes, n, _nodes)
  // {
    // if((*n)->type() == TAG_CONNECTOR)
    // {
      // string label          = (*n)->label();
      // string::size_type pos = label.find('/');
      // string module_name    = label.substr(0, pos);
      // string node_name      = label.substr(pos+1, label.size()-1);
      // VLOG(100) << label << " -> " << module_name << " / " << node_name;
      // (*n)->setModuleName(module_name);
      // (*n)->setNodeName(node_name);
    // }
  // }
// }

void Module::update()
{
  _copiedEdges.clear();
  _copiedNodes.clear();

}

bool Module::isCopy()
{
  return _isCopy;
}

bool Module::isLinked()
{
  return _isLinked;
}

void Module::linkTo(Module* t)
{
  _target = t;
}

bool Module::operator==(const Module m)
{
  Nodes mn = m._nodes;
  FORC(Nodes, a, _nodes)
  {
    bool foundXsdParseNode = false;
    FORC(Nodes, b, mn)
    {
      if(**a == **b)
      {
        foundXsdParseNode = true;
        break;
      }
    }
    if(foundXsdParseNode == false) return false;
  }
  return true;
}

bool Module::operator!=(const Module m)
{
  Nodes mn = m._nodes;
  FORC(Nodes, a, _nodes)
  {
    bool foundXsdParseNode = true;
    FORC(Nodes, b, mn)
    {
      if(**a != **b)
      {
        foundXsdParseNode = false;
        break;
      }
    }
    if(foundXsdParseNode == false) return true;
  }
  return false;
}

bool Module::removeNode(Node *n) throw (ENPException)
{
  if(n->type() != TAG_HIDDEN) throw ENPException("Attempting to remove non-hidden node");
  Nodes::iterator i;

  int neuron_index = -1;
  for(int i = 0; i < (int)_nodes.size(); i++)
  {
    if(_nodes[i] == n)
    {
      neuron_index = i;
      break;
    }
  }

  VLOG(50) << "   Found neuron index " << neuron_index;

  i = std::find(_nodes.begin(), _nodes.end(), n);
  if(i != _nodes.end())
  {
    _nodes.erase(i);
    VLOG(50) << "   Removed neuron " << (*i)->label() << " from nodes";
  }

  i = std::find(_hidden.begin(), _hidden.end(), n);
  if(i != _hidden.end())
  {
    _hidden.erase(i);
    VLOG(50) << "   Removed neuron " << (*i)->label() << " from hidden";
  }

  Edges toBeRemoved;
  FORC(Edges, e, _edges)
  {
    if((*e)->source()      == n->label() ||
       (*e)->destination() == n->label())
    {
      VLOG(50) << "    Removing edge with "
        << (*e)->source()      << " -> "
        << (*e)->destination() << " with " << (*e)->weight();
      Edges::iterator ei = std::find(_edges.begin(), _edges.end(), *e);
      if(ei != _edges.end()) toBeRemoved.push_back(*e);
    }
  }

  for(Edges::iterator e = toBeRemoved.begin(); e != toBeRemoved.end(); e++)
  {
    Edges::iterator ei = std::find(_edges.begin(), _edges.end(), *e);
    _edges.erase(ei);
  }

  FORC(Nodes, nn, _nodes) (*nn)->removeEdge(n);
  return true;
}

bool Module::removeEdge(Edge *e)
{
  FORC(Edges, i, _edges)
  {
    if((**i) == *e)
    {
      _edges.erase(i);
      return true;
    }
  }
  return false;
}


Edge* Module::addEdge(Node *src, Node *dst, double weight) throw (ENPException)
{
  if(dst->contains(src)) throw ENPException("Module::addEdge: The destination node already contains an edge from the source node");
  Edge *e = new Edge(NULL);
  e->setSourceNode(src);
  e->setDestinationNode(dst);
  e->setWeight(weight);

  dst->addEdge(e);

  _edges.push_back(e);

  return e;
}

Node* Module::node(int index)
{
  return _nodes[index];
}



Nodes::iterator Module::s_begin()
{
  return _sensor.begin();
}

Nodes::iterator Module::s_end()
{
  return _sensor.end();
}

int Module::s_size()
{
  return _sensor.size();
}

Nodes Module::sensorNodes()
{
  return _sensor;
}

Nodes::iterator Module::a_begin()
{
  return _actuator.begin();
}

Nodes::iterator Module::a_end()
{
  return _actuator.end();
}

int Module::a_size()
{
  return _actuator.size();
}

Nodes::iterator Module::h_begin()
{
  return _hidden.begin();
}

Nodes::iterator Module::h_end()
{
  return _hidden.end();
}

int Module::h_size()
{
  return _hidden.size();
}

Nodes Module::actuatorNodes()
{
  return _actuator;
}

Node* Module::sensorNode(int index)
{
  return _sensor[index];
}

Node* Module::actuatorNode(int index)
{
  return _actuator[index];
}

Node* Module::hiddenNode(int index)
{
  return _hidden[index];
}

bool Module::modified()
{
  return _modified;
}

void Module::setModified(bool m)
{
  _modified = m;
}

int Module::getNewNodeId()
{
  int i = _globalId;
  _globalId++;
  return i;
}

void Module::updateFromLink()
{
  // TODO
}


Edge* Module::edge(int index)
{
  return _edges[index];
}


void Module::addNode(Node *node)
{
  if(node->type() == TAG_HIDDEN)
  {
    _hidden.push_back(node);
  }
  else if(node->type() == TAG_INPUT)
  {
    _input.push_back(node);
  }
  else if(node->type() == TAG_SENSOR)
  {
    _sensor.push_back(node);
  }
  else if(node->type() == TAG_ACTUATOR)
  {
    _actuator.push_back(node);
  }

}

void Module::setName(string name)
{
  _name = name;
}
