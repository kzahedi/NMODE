#include "Module.h"
#include "base/macros.h"
#include "base/data/DataModule.h"

#include <iostream>
#include <map>
#include <glog/logging.h>


Module::Module(string name)
{
  _name   = name;
  _linked = false;
}

Module::~Module()
{
  FORC(Nodes, n, _nodes) delete (*n);
  _nodes.clear();
}

void Module::addNode(Node *node) throw (ENPException)
{
  switch(node->type())
  {
    case NODE_TYPE_SENSOR:
      _sensors.push_back(node);
      _src_indices.push_back(_nodes.size());
      VLOG(50) << "adding sensor node: " << _sensors.size() << " " << _nodes.size();
      VLOG(50) << "  adding to sources: " << _src_indices.size();
      break;
    case NODE_TYPE_ACTUATOR:
      _actuators.push_back(node);
      _src_indices.push_back(_nodes.size());
      _dst_indices.push_back(_nodes.size());
      VLOG(50) << "adding actuator node: " << _actuators.size() << " " << _nodes.size();
      VLOG(50) << "  adding to sources: " << _src_indices.size();
      VLOG(50) << "  adding to destination: " << _dst_indices.size();
      break;
    case NODE_TYPE_HIDDEN:
      _hidden.push_back(node);
      _src_indices.push_back(_nodes.size());
      _dst_indices.push_back(_nodes.size());
      VLOG(50) << "adding hidden node: " << _hidden.size() << " " << _nodes.size();
      VLOG(50) << "  adding to sources: " << _src_indices.size();
      VLOG(50) << "  adding to destination: " << _dst_indices.size();
      break;
    case NODE_TYPE_INPUT:
      _input.push_back(node);
      _src_indices.push_back(_sensors.size());
      VLOG(50) << "adding input node: " << _input.size() << " " << _nodes.size();
      VLOG(50) << "  adding to sources: " << _src_indices.size();
      break;
    case NODE_TYPE_OUTPUT:
      _output.push_back(node);
      _dst_indices.push_back(_nodes.size());
      VLOG(50) << "adding output node: " << _output.size() << " " << _nodes.size();
      VLOG(50) << "  adding to destination: " << _dst_indices.size();
      break;
    default:
      throw ENPException("Module::addNode: unknown node type");
  }
  _nodes.push_back(node);
}

string Module::name()
{
  return _name;
}

void Module::linkTo(Module *target)
{
  _linked = true;
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

bool Module::modified()
{
  return _modified;
}

void Module::setModified(bool m)
{
  _modified = m;
}

vector<int>::iterator Module::src_indices_begin()
{
  return _src_indices.begin();
}

vector<int>::iterator Module::src_indices_end()
{
  return _src_indices.end();
}

int Module::src_indices_size()
{
  return _src_indices.size();
}

int Module::src_index(int index)
{
  return _src_indices[index];
}

vector<int>::iterator Module::dst_indices_begin()
{
  return _dst_indices.begin();
}

vector<int>::iterator Module::dst_indices_end()
{
  return _dst_indices.end();
}

int Module::dst_indices_size()
{
  return _dst_indices.size();
}

int Module::dst_index(int index)
{
  return _dst_indices[index];
}



