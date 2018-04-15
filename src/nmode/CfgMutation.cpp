#include <nmode/CfgMutation.h>

#include <iostream>
#include <glog/logging.h>

using namespace std;

CfgMutation::CfgMutation(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _node    = NULL;
  _edge    = NULL;
  _changed = false;
}

CfgMutation::~CfgMutation()
{
  if(_node != NULL) delete _node;
  if(_edge != NULL) delete _edge;
}

void CfgMutation::add(ParseElement *element)
{
  VLOG(100) << "parsing: " << element->name();
  if(element->closing(TAG_MUTATION))
  {
    _changed = _node->changed() || _edge->changed();
    current = parent;
    return;
  }

  if(element->opening(TAG_MUTATION))
  {
    if(_node != NULL) delete _node;
    if(_edge != NULL) delete _edge;
  }

  if(element->opening(TAG_MUTATION_NODE))
  {
    _node = new CfgMutationNode(this);
    current = _node;
    current->add(element);
  }

  if(element->opening(TAG_MUTATION_EDGE))
  {
    _edge = new CfgMutationEdge(this);
    current  = _edge;
    current->add(element);
  }
}

void CfgMutation::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_MUTATION_DEFINITION);
  root->add(NE(TAG_MUTATION_NODE, TAG_MUTATION_NODE_DEFINITION, 1, 1));
  root->add(NE(TAG_MUTATION_EDGE, TAG_MUTATION_EDGE_DEFINITION, 1, 1));
  spec->add(root);

  CfgMutationNode::createXsd(spec);
  CfgMutationEdge::createXsd(spec);
}

CfgMutationNode* CfgMutation::node()
{
  return _node;
}

CfgMutationEdge* CfgMutation::edge()
{
  return _edge;
}

CfgMutation* CfgMutation::copy()
{
  CfgMutation *copy = new CfgMutation(NULL);
  if(_node != NULL) copy->setNode(_node->copy());
  if(_edge != NULL) copy->setEdge(_edge->copy());
  return copy;
}

void CfgMutation::setNode(CfgMutationNode* n)
{
  _node = n;
}

void CfgMutation::setEdge(CfgMutationEdge* e)
{
  _edge = e;
}

