#include "DataModule.h"

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

DataModule::DataModule(DataNode *parent)
  : DataNode(parent)
{
  _mirrorAxes   = new bool[3];
  _isCopy   = false;
  _isLinked = false;
  _globalId = 0;
  _modified = false;
}

DataModule::~DataModule()
{
  delete _mirrorAxes;
}

void DataModule::add(DataParseElement *element)
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
    DataModuleNode *node = new DataModuleNode(this);
    _nodes.push_back(node);
    current = node;
    node->add(element);
  }

  if(element->opening(TAG_MODULE_EDGE))
  {
    VLOG(100) << "found " << TAG_MODULE_EDGE;
    DataModuleEdge *edge = new DataModuleEdge(this);
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

void DataModule::createXsd(XsdSpecification *spec)
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

  DataModuleNode::createXsd(spec);
}

string DataModule::name()
{
  return _name;
}

DataModuleNodes::iterator DataModule::n_begin()
{
  return _nodes.begin();
}

DataModuleNodes::iterator DataModule::n_end()
{
  return _nodes.end();
}

int DataModule::n_size()
{
  return _nodes.size();
}

DataModuleNodes DataModule::nodes()
{
  return _nodes;
}

DataModuleEdges::iterator DataModule::e_begin()
{
  return _edges.begin();
}

DataModuleEdges::iterator DataModule::e_end()
{
  return _edges.end();
}

int DataModule::e_size()
{
  return _edges.size();
}

DataModuleEdges DataModule::edges()
{
  return _edges;
}

string DataModule::ref()
{
  return _ref;
}

// void DataModule::__linkConnectorNeurons()
// {
  // FORC(DataModuleNodes, n, _nodes)
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

void DataModule::update()
{
  _copiedEdges.clear();
  _copiedNodes.clear();

}

bool DataModule::isCopy()
{
  return _isCopy;
}

bool DataModule::isLinked()
{
  return _isLinked;
}

void DataModule::linkTo(DataModule* t)
{
  _target = t;
}

bool DataModule::operator==(const DataModule m)
{
  DataModuleNodes mn = m._nodes;
  FORC(DataModuleNodes, a, _nodes)
  {
    bool foundDataNode = false;
    FORC(DataModuleNodes, b, mn)
    {
      if(**a == **b)
      {
        foundDataNode = true;
        break;
      }
    }
    if(foundDataNode == false) return false;
  }
  return true;
}

bool DataModule::operator!=(const DataModule m)
{
  DataModuleNodes mn = m._nodes;
  FORC(DataModuleNodes, a, _nodes)
  {
    bool foundDataNode = true;
    FORC(DataModuleNodes, b, mn)
    {
      if(**a != **b)
      {
        foundDataNode = false;
        break;
      }
    }
    if(foundDataNode == false) return true;
  }
  return false;
}

bool DataModule::removeNode(DataModuleNode *n) throw (ENPException)
{
  if(n->type() != TAG_HIDDEN) throw ENPException("Attempting to remove non-hidden node");
  DataModuleNodes::iterator i;

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

  DataModuleEdges toBeRemoved;
  FORC(DataModuleEdges, e, _edges)
  {
    if((*e)->source()      == n->label() ||
       (*e)->destination() == n->label())
    {
      VLOG(50) << "    Removing edge with "
        << (*e)->source()      << " -> "
        << (*e)->destination() << " with " << (*e)->weight();
      DataModuleEdges::iterator ei = std::find(_edges.begin(), _edges.end(), *e);
      if(ei != _edges.end()) toBeRemoved.push_back(*e);
    }
  }

  for(DataModuleEdges::iterator e = toBeRemoved.begin(); e != toBeRemoved.end(); e++)
  {
    DataModuleEdges::iterator ei = std::find(_edges.begin(), _edges.end(), *e);
    _edges.erase(ei);
  }

  FORC(DataModuleNodes, nn, _nodes) (*nn)->removeEdge(n);
  return true;
}

bool DataModule::removeEdge(DataModuleEdge *e)
{
  FORC(DataModuleEdges, i, _edges)
  {
    if((**i) == *e)
    {
      _edges.erase(i);
      return true;
    }
  }
  return false;
}


DataModuleEdge* DataModule::addEdge(DataModuleNode *src, DataModuleNode *dst, double weight) throw (ENPException)
{
  if(dst->contains(src)) throw ENPException("Module::addEdge: The destination node already contains an edge from the source node");
  DataModuleEdge *e = new DataModuleEdge(NULL);
  e->setSourceNode(src);
  e->setDestinationNode(dst);
  e->setWeight(weight);

  dst->addEdge(e);

  _edges.push_back(e);

  return e;
}

DataModuleNode* DataModule::node(int index)
{
  return _nodes[index];
}



DataModuleNodes::iterator DataModule::s_begin()
{
  return _sensors.begin();
}

DataModuleNodes::iterator DataModule::s_end()
{
  return _sensors.end();
}

int DataModule::s_size()
{
  return _sensors.size();
}

DataModuleNodes DataModule::sensorNodes()
{
  return _sensors;
}



DataModuleNodes::iterator DataModule::a_begin()
{
  return _actuators.begin();
}

DataModuleNodes::iterator DataModule::a_end()
{
  return _actuators.end();
}

int DataModule::a_size()
{
  return _actuators.size();
}

DataModuleNodes DataModule::actuatorNodes()
{
  return _actuators;
}

DataModuleNode* DataModule::sensorNode(int index)
{
  return _sensors[index];
}

DataModuleNode* DataModule::actuatorNode(int index)
{
  return _actuators[index];
}

DataModuleNode* DataModule::hiddenNode(int index)
{
  return _hidden[index];
}

bool DataModule::modified()
{
  return _modified;
}

void DataModule::setModified(bool m)
{
  _modified = m;
}

int DataModule::getNewNodeId()
{
  int i = _globalId;
  _globalId++;
  return i;
}

void DataModule::updateFromLink()
{
  // TODO
}
