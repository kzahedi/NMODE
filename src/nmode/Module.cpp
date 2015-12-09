#include <nmode/Module.h>

#include <nmode/macros.h>

#include <iostream>
#include <string>
#include <glog/logging.h>

#define TAG_NAME                   (char*)"name"
#define TAG_NODE_ID                (char*)"nodeid"
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

#define REMOVE_NEURON_FROM_LIST(lst, n, msg) \
  { \
    i = std::find(lst.begin(), lst.end(), n); \
    if(i != lst.end())\
    { \
      lst.erase(i); \
      VLOG(50) << "   Removed neuron " << (*i)->label() << " from " << msg; \
    } \
  }


using namespace std;

Module::Module(XsdParseNode *parent)
  : XsdParseNode(parent), _mirrorAxes()
{
  _globalId = 0;
  _isCopy   = false;
  _modified = false;
  _mutation = NULL;
}

Module::Module(const Module &m)
  : XsdParseNode(m.parent)
{
  *this = m;
}

Module::~Module()
{
  if(_isCopy == false)
  {
    FORC(Nodes, n, _nodes) delete (*n);
    FORC(Edges, e, _edges) delete (*e);

    // if(_mutation != NULL) delete _mutation;

    _copiedEdges.resize(0);
    _copiedNodes.resize(0);
    _nodes.resize(0);
    _sensor.resize(0);
    _actuator.resize(0);
    _connector.resize(0);
    _moduleInput.resize(0);
    _moduleOutput.resize(0);
    _hidden.resize(0);
    _tmpArrayOfNodes.resize(0);
    _edges.resize(0);

  }
}

void Module::add(ParseElement *element)
{

  VLOG(100) << "parsing " << element->name();
  if(element->closing(TAG_MODULE))
  {
    FORC(Nodes, n, _tmpArrayOfNodes) addNode(*n);
    FORC(Edges, e, _edges)
    {
      Node *src = nodeByName((*e)->source());
      Node *dst = nodeByName((*e)->destination());
      (*e)->setSourceNode(src);
      (*e)->setDestinationNode(dst);
    }
    if(_isCopy == false)
    {
      __applyTranslation();
    }
    current = parent;
    return;
  }

  if(element->opening(TAG_MODULE))
  {
    element->set(TAG_NAME,    _name);
    element->set(TAG_NODE_ID, _globalId);
    VLOG(100) << "setting name to " << _name;
  }

  if(element->opening(TAG_MODULE_NODE))
  {
    VLOG(100) << "found " << TAG_MODULE_NODE;
    Node *node = new Node(this);
    _tmpArrayOfNodes.push_back(node);
    current = node;
    node->add(element);
  }

  if(element->opening(TAG_MODULE_EDGE))
  {
    VLOG(100) << "found " << TAG_MODULE_EDGE;
    Edge *edge = new Edge(this);
    _edges.push_back(edge);
    // TODO connect to source and destination node
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

    VLOG(100) << "  found " << r;
    r.x = DEG_TO_RAD(r.x);
    r.y = DEG_TO_RAD(r.y);
    r.z = DEG_TO_RAD(r.z);

    _rotation << r;
    VLOG(100) << "  found " << _rotation;
  }

  if(element->opening(TAG_MODULE_MIRROR))
  {
    VLOG(100) << "found " << TAG_MODULE_MIRROR;
    P3D r;
    element->set(TAG_X, _mirrorAxes.x);
    element->set(TAG_Y, _mirrorAxes.y);
    element->set(TAG_Z, _mirrorAxes.z);
    VLOG(100) << "found " << _mirrorAxes.x << " " << _mirrorAxes.y << " " << _mirrorAxes.z;
  }

  if(element->opening(TAG_MUTATION))
  {
    if(_mutation != NULL) delete _mutation;
    _mutation = new CfgMutation(this);
    current = _mutation;
    current->add(element);
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
  optionA->add(NE(TAG_MUTATION,         TAG_MUTATION_DEFINITION,    0, 1));
  optionA->add(NE(TAG_MODULE_ROTATE,    TAG_MODULE_P3D_DEFINITION,  0, 1));
  optionA->add(NE(TAG_MODULE_TRANSLATE, TAG_MODULE_P3D_DEFINITION,  0, 1));
  optionA->add(NE(TAG_MODULE_NODE,      TAG_MODULE_NODE_DEFINITION, 1, TAG_XSD_UNBOUNDED));
  optionA->add(NE(TAG_MODULE_EDGE,      TAG_MODULE_EDGE_DEFINITION, 0, TAG_XSD_UNBOUNDED));
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
  CfgMutation::createXsd(spec);
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

void Module::update()
{
  _copiedEdges.clear();
  _copiedNodes.clear();

}

bool Module::isCopy()
{
  return _isCopy;
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
  if(m._name != _name) return false;
  FORC(Nodes, a, _nodes)
  {
    bool foundMissmatch = false;
    FORC(Nodes, b, mn)
    {
      if(**a != **b)
      {
        foundMissmatch = false;
        break;
      }
    }
    if(foundMissmatch == true) return true;
  }
  return false;
}

bool Module::removeNode(Node *n) throw (NMODEException)
{
  if(n->type() != TAG_HIDDEN) throw NMODEException("Attempting to remove non-hidden node");
  Nodes::iterator i;

  VLOG(50) << "   Removing neuron \"" << n->label() << "\"";

  REMOVE_NEURON_FROM_LIST(_nodes,        n, "nodes");
  REMOVE_NEURON_FROM_LIST(_hidden,       n, "hidden");
  REMOVE_NEURON_FROM_LIST(_sensor,       n, "sensors");
  REMOVE_NEURON_FROM_LIST(_actuator,     n, "actuators");
  REMOVE_NEURON_FROM_LIST(_connector,    n, "connectors");
  REMOVE_NEURON_FROM_LIST(_moduleInput,  n, "module input");
  REMOVE_NEURON_FROM_LIST(_moduleOutput, n, "module output");

  Edges toBeRemoved;
  FORC(Edges, e, _edges)
  {
    if((*e)->sourceNode()->label()      == n->label() ||
       (*e)->destinationNode()->label() == n->label())
    {
      VLOG(50) << "    Removing edge with "
        << (*e)->source()      << " -> "
        << (*e)->destination() << " with "
        << (*e)->weight();
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


Edge* Module::addEdge(Node *src, Node *dst, double weight) throw (NMODEException)
{
  if(dst->contains(src))
  {
    cerr << "Warning:" << endl;
    cerr << "  Source node "      << src->label() << ", " << src->type() << endl;
    cerr << "  Destination node " << dst->label() << ", " << dst->type() << endl;
    throw NMODEException("Module::addEdge: The destination node already contains an edge from the source node");
  }

  Edge *e = new Edge(NULL);
  e->setSourceNode(src);
  e->setDestinationNode(dst);
  e->setWeight(weight);
  e->setSourceLabel(src->label());
  e->setDestinationLabel(dst->label());

  dst->addEdge(e);

  _edges.push_back(e);

  return e;
}

Node* Module::node(int index)
{
  if(index >= (int)_nodes.size())
  {
    stringstream oss;
    oss << "Module::node. Index out of range: " << index << " > " << _nodes.size() << endl;
    throw NMODEException(oss.str());
  }
  return _nodes[index];
}

Node* Module::nodeByName(string name)
{
  FORC(Nodes, n, _nodes) if((*n)->label() == name) return (*n);
  return NULL;
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
  VLOG(50) << "returning global id " << i;
  _globalId++;
  return i;
}

int Module::getCurrentNodeId()
{
  return _globalId;
}

Edge* Module::edge(int index)
{
  return _edges[index];
}

void Module::addNode(Node *node)
{
  _nodes.push_back(node);
  if(node->type() == TAG_HIDDEN)
  {
    _hidden.push_back(node);
  }
  else if(node->type() == TAG_INPUT)
  {
    _moduleInput.push_back(node);
  }
  else if(node->type() == TAG_OUTPUT)
  {
    _moduleOutput.push_back(node);
  }
  else if(node->type() == TAG_SENSOR)
  {
    _sensor.push_back(node);
  }
  else if(node->type() == TAG_ACTUATOR)
  {
    _actuator.push_back(node);
  }
  else if(node->type() == TAG_CONNECTOR)
  {
    _connector.push_back(node);
  }
}

void Module::setName(string name)
{
  _name = name;
}

void Module::__applyMirror()
{
  FORC(Nodes, n, _nodes)
  {
    P3D p = (*n)->position();
    if(_mirrorAxes.x == true) p.x = -p.x;
    if(_mirrorAxes.y == true) p.y = -p.y;
    if(_mirrorAxes.z == true) p.z = -p.z;
    (*n)->setPosition(p);
  }
}

void Module::__applyTranslation()
{
  FORC(Nodes, n, _nodes)
  {
    P3D p = (*n)->position();
    p += _rotation;
    p += _translation;
    (*n)->setPosition(p);
  }
}

// Module& Module::operator=(const Module &m)
// {
  // copy and apply transformation
  // _name        = m._name;
  // _ref         = m._ref;
  // _isCopy      = m._isCopy;
  // _modified    = m._modified;
  // _globalId    = m._globalId;
  // _translation = m._translation;
  // _rotation    = m._rotation;
  // _mutation    = NULL;

  // FORC(Nodes, n, _nodes) delete (*n);
  // FORC(Edges, e, _edges) delete (*e);

  // FORCC(Nodes, n, m._nodes) addNode((*n)->copy());
  // FORCC(Edges, e, m._edges)
  // {
    // Node *src = nodeByName((*e)->sourceNode()->label());
    // Node *dst = nodeByName((*e)->destinationNode()->label());
    // addEdge(src, dst, (*e)->weight());
  // }

  // __applyMirror();
  // if(_isCopy == false)
  // {
    // __applyTranslation();
    // _mutation = m._mutation;
  // }

  // return *this;
// }

void Module::setMirrorAxes(bool x, bool y, bool z)
{
  _mirrorAxes.x = x;
  _mirrorAxes.y = y;
  _mirrorAxes.z = z;
}

void Module::setTranslation(P3D t)
{
  _translation = t;
}

void Module::setRotation(P3D r)
{
  _rotation = r;
}

void Module::copyAndApplyTransition(Module *m)
{
  _nodes.clear();
  _sensor.clear();
  _actuator.clear();
  _moduleInput.clear();
  _moduleOutput.clear();
  _hidden.clear();
  _connector.clear();
  _edges.clear();

  FORC(Nodes, n, _nodes) delete (*n);
  FORC(Edges, e, _edges) delete (*e);

  FORCC(Nodes, n, m->_nodes) addNode((*n)->copy());
  FORC(Edges,  e, m->_edges)
  {
    Node *srcNode = nodeByName((*e)->sourceNode()->label());
    Node *dstNode = nodeByName((*e)->destinationNode()->label());
    addEdge(srcNode, dstNode, (*e)->weight());
  }

  __applyMirror();
  __applyTranslation();
}

Node* Module::moduleInputNode(int index)
{
  return _moduleInput[index];
}

Nodes Module::moduleInputNodes()
{
  return _moduleInput;
}

Nodes::iterator Module::i_begin()
{
  return _moduleInput.begin();
}

Nodes::iterator Module::i_end()
{
  return _moduleInput.end();
}

int Module::i_size()
{
  return _moduleInput.size();
}

Node* Module::moduleOutputNode(int index)
{
  return _moduleOutput[index];
}

Nodes Module::moduleOutputNodes()
{
  return _moduleOutput;
}

Nodes::iterator Module::o_begin()
{
  return _moduleOutput.begin();
}

Nodes::iterator Module::o_end()
{
  return _moduleOutput.end();
}

int Module::o_size()
{
  return _moduleOutput.size();
}


Module* Module::copy()
{
  Module *copy = new Module(NULL);

  copy->_globalId    = _globalId;
  copy->_isCopy      = _isCopy;
  copy->_modified    = _modified;

  copy->_name        = _name;
  copy->_ref         = _ref;

  copy->_rotation    = _rotation;
  copy->_translation = _translation;

  copy->_mirrorAxes  = _mirrorAxes;
  copy->_mutation    = NULL;

  if(_isCopy == false)   copy->_mutation = _mutation;
  FORC(Nodes, n, _nodes) copy->addNode((*n)->copy());

  // cout << "*****" << endl;
  // FORC(Edges, e, _edges)
  // {
    // cout << "module " << _name << ": "
      // << (*e)->sourceNode()->label() << " -> "
      // << (*e)->sourceNode()->label() << " = "
      // << (*e)->weight() << endl;
  // }
  // cout << "#####" << endl;
  FORC(Edges, e, _edges)
  {
    Node *src = copy->nodeByName((*e)->sourceNode()->label());
    Node *dst = copy->nodeByName((*e)->destinationNode()->label());
    // cout << "module " << _name << " adding edge: "
      // << src->label() << " -> "
      // << dst->label() << " weight " << (*e)->weight() << endl;
    FORC(Edges, ee, copy->_edges)
    {
      if((*ee)->sourceNode() == src && (*ee)->destinationNode() == dst)
      {
        cerr << "module: " << _name << " duplicate edge: " << src->label() << " -> " << dst->label() << " weight " << (*e)->weight() << endl;
      }
    }
    copy->addEdge(src, dst, (*e)->weight());
  }

  return copy;
}


MirrorAxes Module::mirrorAxes()
{
  return _mirrorAxes;
}

P3D Module::translation()
{
  return _translation;
}

Quaternion Module::rotation()
{
  return _rotation;
}

void Module::setIsCopy(bool c)
{
  _isCopy = c;
}

void Module::setTarget(string t)
{
  _ref = t;
}

CfgMutation* Module::mutation()
{
  return _mutation;
}

void Module::setMutation(CfgMutation* cfg)
{
  _mutation = cfg;
}

void Module::removeMutation()
{
  if(_mutation != NULL) delete _mutation;
  _mutation = NULL;
}

