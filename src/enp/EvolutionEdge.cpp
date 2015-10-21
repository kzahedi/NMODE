#include "EvolutionEdge.h"

#include <iostream>
#include <glog/logging.h>


#define TAG_MODIFY            (char*)"modify"
#define TAG_MODIFY_DEFINITION (char*)"modify_definition"

#define TAG_ADD               (char*)"add"
#define TAG_ADD_DEFINITION    (char*)"add_definition"

#define TAG_DEL               (char*)"delete"
#define TAG_DEL_DEFINITION    (char*)"delete_definition"

#define TAG_PROBABILITY       (char*)"probability"
#define TAG_MAX               (char*)"maximum"
#define TAG_DELTA             (char*)"delta"

using namespace std;

EvolutionEdge::EvolutionEdge(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _modifyProbability = 0.1;
  _modifyMaxValue    = 4.0;
  _modifyDelta       = 0.5;

  _addProbability    = 0.01;
  _addMaxValue       = 1.0;

  _delProbability    = 0.1;
}

EvolutionEdge::~EvolutionEdge()
{
  // nothing to be done
}

void EvolutionEdge::add(ParseElement *element)
{
  VLOG(100) << "parsing: " << element->name();
  if(element->closing(TAG_EVOLUTION_EDGE))
  {
    current = parent;
  }

  if(element->opening(TAG_EVOLUTION_EDGE))
  {
  }

  if(element->opening(TAG_MODIFY))
  {
    element->set(TAG_PROBABILITY, _modifyProbability);
    element->set(TAG_MAX,         _modifyMaxValue);
    element->set(TAG_DELTA,       _modifyDelta);
    VLOG(100) << "set modify probability to: " << _modifyProbability;
    VLOG(100) << "set modify max to: " << _modifyMaxValue;
    VLOG(100) << "set modify delta to: " << _modifyDelta;
  }

  if(element->opening(TAG_ADD))
  {
    element->set(TAG_PROBABILITY, _addProbability);
    element->set(TAG_MAX,         _addMaxValue);
    VLOG(100) << "set add probability to: " << _addProbability;
    VLOG(100) << "set add max to: " << _addMaxValue;
  }

  if(element->opening(TAG_DEL))
  {
    element->set(TAG_PROBABILITY, _delProbability);
    VLOG(100) << "set del probability to: " << _delProbability;
  }

}

void EvolutionEdge::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_EVOLUTION_EDGE_DEFINITION);
  root->add(NE(TAG_MODIFY, TAG_MODIFY_DEFINITION, 1, 1));
  root->add(NE(TAG_ADD,    TAG_ADD_DEFINITION,    1, 1));
  root->add(NE(TAG_DEL,    TAG_DEL_DEFINITION,    1, 1));
  spec->add(root);

  XsdSequence *modify = new XsdSequence(TAG_MODIFY_DEFINITION);
  modify->add(NA(TAG_PROBABILITY, TAG_UNIT_INTERVAL,    true));
  modify->add(NA(TAG_MAX,         TAG_POSITIVE_DECIMAL, true));
  modify->add(NA(TAG_DELTA,       TAG_POSITIVE_DECIMAL, true));
  spec->add(modify);
  
  XsdSequence *add = new XsdSequence(TAG_ADD_DEFINITION);
  add->add(NA(TAG_PROBABILITY, TAG_UNIT_INTERVAL,    true));
  add->add(NA(TAG_MAX,         TAG_POSITIVE_DECIMAL, true));
  spec->add(add);

  XsdSequence *del = new XsdSequence(TAG_DEL_DEFINITION);
  del->add(NA(TAG_PROBABILITY, TAG_UNIT_INTERVAL, true));
  spec->add(del);

}

double EvolutionEdge::modifyProbability()
{
  return _modifyProbability;
}

double EvolutionEdge::modifyMaxValue()
{
  return _modifyMaxValue;
}

double EvolutionEdge::modifyDelta()
{
  return _modifyDelta;
}

double EvolutionEdge::addProbability()
{
  return _addProbability;
}

double EvolutionEdge::addMaxValue()
{
  return _addMaxValue;
}

double EvolutionEdge::delProbability()
{
  return _delProbability;
}
