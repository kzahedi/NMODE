#include "Evolution.h"

#include <iostream>
#include <glog/logging.h>

using namespace std;

Evolution::Evolution(XsdParseNode *parent)
  : XsdParseNode(parent)
{ }

Evolution::~Evolution()
{
  delete _node;
  // delete _edge;
}


void Evolution::add(ParseElement *element)
{
  VLOG(100) << "parsing: " << element->name();
  if(element->closing(TAG_EVOLUTION))
  {
    current = parent;
    return;
  }

  if(element->opening(TAG_EVOLUTION))
  {
  }

  if(element->opening(TAG_EVOLUTION_NODE))
  {
    _node = new EvolutionNode(this);
    current = _node;
    current->add(element);
  }

  if(element->opening(TAG_EVOLUTION_EDGE))
  {
    _edge = new EvolutionEdge(this);
    current  = _edge;
    current->add(element);
  }

}

void Evolution::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_EVOLUTION_DEFINITION);
  root->add(NE(TAG_EVOLUTION_NODE, TAG_EVOLUTION_NODE_DEFINITION, 1, 1));
  root->add(NE(TAG_EVOLUTION_EDGE, TAG_EVOLUTION_EDGE_DEFINITION, 1, 1));
  spec->add(root);

  EvolutionNode::createXsd(spec);
  EvolutionEdge::createXsd(spec);
}

EvolutionNode* Evolution::node()
{
  return _node;
}

EvolutionEdge* Evolution::edge()
{
  return _edge;
}

