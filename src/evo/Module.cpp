#include "Module.h"
#include "base/macros.h"
#include "base/data/DataModule.h"

#include <iostream>
#include <map>
#include <glog/logging.h>


Module::Module(string name)
{
  _name     = name;
  _globalId = 0;
  _isCopy   = false;
}

Module::~Module()
{
  FORC(Nodes, n, _nodes) delete (*n);
  _nodes.clear();
}

void Module::addNode(Node *node) throw (ENPException)
{
  _nodes.push_back(node);
  switch(node->type())
  {
    case NODE_TYPE_SENSOR:
      _sensors.push_back(node);
      VLOG(50) << "adding sensor node: " << node->label();
      break;
    case NODE_TYPE_ACTUATOR:
      _actuators.push_back(node);
      VLOG(50) << "adding actuator node: " << node->label();
      break;
    case NODE_TYPE_HIDDEN:
      _hidden.push_back(node);
      VLOG(50) << "adding hidden node: " << node->label();
      break;
    case NODE_TYPE_INPUT:
      _input.push_back(node);
      VLOG(50) << "adding input node: " << node->label();
      break;
    case NODE_TYPE_OUTPUT:
      _output.push_back(node);
      VLOG(50) << "adding output node: " << node->label();
      break;
    case NODE_TYPE_CONNECTOR:
      _output.push_back(node);
      VLOG(50) << "adding output node: " << node->label();
      break;
    default:
      throw ENPException("Module::addNode: unknown node type");
  }
}

string Module::name()
{
  return _name;
}

void Module::linkTo(Module *target)
{
  _isCopy = true;
  _target = target;
}


bool Module::operator==(const Module m)
{
  Nodes mn = m._nodes;
  FORC(Nodes, a, _nodes)
  {
    bool foundNode = false;
    FORC(Nodes, b, mn)
    {
      if(**a == **b)
      {
        foundNode = true;
        break;
      }
    }
    if(foundNode == false) return false;
  }
  return true;
}

bool Module::operator!=(const Module m)
{
  Nodes mn = m._nodes;
  FORC(Nodes, a, _nodes)
  {
    bool foundNode = true;
    FORC(Nodes, b, mn)
    {
      if(**a != **b)
      {
        foundNode = false;
        break;
      }
    }
    if(foundNode == false) return true;
  }
  return false;
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

int Module::s_size()
{
  return _sensors.size();
}

int Module::a_size()
{
  return _actuators.size();
}

int Module::h_size()
{
  return _hidden.size();
}


Edge* Module::addEdge(Node *src, Node *dst, double weight) throw (ENPException)
{
  if(dst->contains(src)) throw ENPException("Module::addEdge: The destination node already contains an edge from the source node");
  Edge *e = new Edge();
  e->setSource(src);
  e->setDestination(dst);
  e->setWeight(weight);

  dst->addEdge(e);

  _edges.push_back(e);

  return e;
}

Node* Module::hiddenNode(int index)
{
  return _hidden[index];
}

Node* Module::node(int index)
{
  return _nodes[index];
}

Edge* Module::edge(int index)
{
  return _edges[index];
}

void Module::setName(string name)
{
  _name = name;
  VLOG(100) << "setting name to " << _name;
}

void Module::initialise(DataModule *data)
{
  _data   = data;
  _isCopy = data->isCopy();

  if(_isCopy == false)
  {
    std::map<string, Node*> nodeMap;

    for(DataModuleNodes::iterator n = data->n_begin(); n != data->n_end(); n++)
    {
      Node *node = new Node();
      node->setType((*n)->type());
      node->setBias((*n)->bias());
      node->setLabel((*n)->label());
      node->setPosition((*n)->position());
      nodeMap.insert(std::make_pair(node->label(), node));
      addNode(node);
    }

    for(DataModuleEdges::iterator e = data->e_begin(); e != data->e_end(); e++)
    {
      Edge *edge = new Edge();
      Node *src  = nodeMap[(*e)->source()];
      Node *dst  = nodeMap[(*e)->destination()];
      edge->setSource(src);
      edge->setDestination(dst);
      edge->setWeight((*e)->weight());
      _edges.push_back(edge);
    }
  }
}

bool Module::modified()
{
  return _modified;
}

void Module::setModified(bool m)
{
  _modified = m;
}

bool Module::removeNode(Node *n) throw (ENPException)
{
  if(n->type() != NODE_TYPE_HIDDEN) throw ENPException("Attempting to remove non-hidden node");
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
    if((*e)->source()->label()      == n->label() ||
       (*e)->destination()->label() == n->label())
    {
      VLOG(50) << "    Removing edge with "
        << (*e)->source()->label() << " -> "
        << (*e)->destination()->label() << " with " << (*e)->weight();
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

int Module::getNewNodeId()
{
  int i = _globalId;
  _globalId++;
  return i;
}

bool Module::isCopy()
{
  return _isCopy;
}


void Module::updateFromLink()
{

}
