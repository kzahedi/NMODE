#include "DataModule.h"

#include "base/macros.h"

#include <iostream>
#include <glog/logging.h>

#define TAG_NAME (char*)"name"

using namespace std;

DataModule::DataModule(DataNode *parent)
  : DataNode(parent)
{ }

DataModule::~DataModule()
{
}

void DataModule::add(DataParseElement *element)
{

  VLOG(100) << "parsing " << element->name();
  if(element->closing(TAG_MODULE))
  {
    current = parent;
    return;
  }

  if(element->opening(TAG_MODULE))
  {
    element->set(TAG_NAME, _name);
    VLOG(100) << "setting name to " << _name;
  }

  VLOG(100) << "checking for " << TAG_MODULE_NODE;
  if(element->opening(TAG_MODULE_NODE))
  {
    VLOG(100) << "found " << TAG_MODULE_NODE;
    DataModuleNode *node = new DataModuleNode(this);
    _nodes.push_back(node);
    current = node;
    node->add(element);
  }

  VLOG(100) << "checking for " << TAG_MODULE_EDGE;
  if(element->opening(TAG_MODULE_EDGE))
  {
    VLOG(100) << "found " << TAG_MODULE_EDGE;
    DataModuleEdge *edge = new DataModuleEdge(this);
    _edges.push_back(edge);
    current = edge;
    edge->add(element);
  }

}

void DataModule::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_MODULE_DEFINITION);
  root->add(NA(TAG_NAME,        TAG_XSD_STRING,             true));
  root->add(NE(TAG_MODULE_NODE, TAG_MODULE_NODE_DEFINITION, 1, TAG_XSD_UNBOUNDED));
  root->add(NE(TAG_MODULE_EDGE, TAG_MODULE_EDGE_DEFINITION, 0, TAG_XSD_UNBOUNDED));
  spec->add(root);

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

