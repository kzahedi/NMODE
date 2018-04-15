#include "CfgMutationNode.h"

#include <iostream>


#define TAG_MODIFY               (char*)"modify"
#define TAG_MODIFY_DEFINITION    (char*)"node_modify_definition"
#define TAG_ADD                  (char*)"add"
#define TAG_ADD_DEFINITION       (char*)"node_add_definition"
#define TAG_DEL                  (char*)"delete"
#define TAG_DEL_DEFINITION       (char*)"node_delete_definition"
#define TAG_PROBABILITY          (char*)"probability"
#define TAG_MAX                  (char*)"maximum"
#define TAG_DELTA                (char*)"delta"


using namespace std;

CfgMutationNode::CfgMutationNode(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _modifyProbability = 0.1;
  _modifyMaxValue    = 4.0;
  _modifyDelta       = 0.5;
  _addProbability    = 0.01;
  _addMaxValue       = 1.0;
  _delProbability    = 0.1;
  _changed           = false;
}

CfgMutationNode::~CfgMutationNode()
{
  // nothing to be done
}

void CfgMutationNode::add(ParseElement *element)
{
  if(element->opening(TAG_MUTATION_NODE))
  {
    current = parent;
    _changed = false;
  }

  if(element->closing(TAG_MUTATION_NODE))
  {
    current = parent;
  }

  if(element->opening(TAG_MUTATION_NODE))
  {
  }

  if(element->opening(TAG_MODIFY))
  {
    _changed |= element->set(TAG_PROBABILITY, _modifyProbability);
    _changed |= element->set(TAG_MAX,         _modifyMaxValue);
    _changed |= element->set(TAG_DELTA,       _modifyDelta);
  }

  if(element->opening(TAG_ADD))
  {
    _changed |= element->set(TAG_PROBABILITY, _addProbability);
    _changed |= element->set(TAG_MAX,         _addMaxValue);
  }

  if(element->opening(TAG_DEL))
  {
    _changed |= element->set(TAG_PROBABILITY, _delProbability);
  }

}

void CfgMutationNode::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_MUTATION_NODE_DEFINITION);
  root->add(NE(TAG_MODIFY, TAG_MODIFY_DEFINITION,    1, 1));
  root->add(NE(TAG_ADD,    TAG_ADD_DEFINITION,       1, 1));
  root->add(NE(TAG_DEL,    TAG_DEL_DEFINITION,       1, 1));
  spec->add(root);

  XsdSequence *modify = new XsdSequence(TAG_MODIFY_DEFINITION);
  modify->add(NA(TAG_PROBABILITY, TAG_UNIT_INTERVAL, true));
  modify->add(NA(TAG_MAX,         TAG_POSITIVE_DECIMAL, true));
  modify->add(NA(TAG_DELTA,       TAG_POSITIVE_DECIMAL, true));
  spec->add(modify);

  XsdSequence *add = new XsdSequence(TAG_ADD_DEFINITION);
  add->add(NA(TAG_PROBABILITY, TAG_UNIT_INTERVAL, true));
  add->add(NA(TAG_MAX,         TAG_POSITIVE_DECIMAL, true));
  spec->add(add);

  XsdSequence *del = new XsdSequence(TAG_DEL_DEFINITION);
  del->add(NA(TAG_PROBABILITY, TAG_UNIT_INTERVAL, true));
  spec->add(del);
}

double CfgMutationNode::modifyProbability()
{
  return _modifyProbability;
}

double CfgMutationNode::modifyMaxValue()
{
  return _modifyMaxValue;
}

double CfgMutationNode::modifyDelta()
{
  return _modifyDelta;
}

double CfgMutationNode::addProbability()
{
  return _addProbability;
}

double CfgMutationNode::addMaxValue()
{
  return _addMaxValue;
}

double CfgMutationNode::delProbability()
{
  return _delProbability;
}

CfgMutationNode* CfgMutationNode::copy()
{
  CfgMutationNode *copy = new CfgMutationNode();

  copy->_modifyProbability = _modifyProbability;
  copy->_modifyMaxValue    = _modifyMaxValue;
  copy->_modifyDelta       = _modifyDelta;
  copy->_addProbability    = _addProbability;
  copy->_addMaxValue       = _addMaxValue;
  copy->_delProbability    = _delProbability;

  return copy;
}
