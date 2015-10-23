#include "Evaluation.h"

#include <iostream>
#include <glog/logging.h>

using namespace std;

# define TAG_LIFE_TIME              (char*)"lifetime"
# define TAG_LIFE_TIME_DEFINITION   (char*)"lifetime_evaluation_definition"
# define TAG_ITERATIONS             (char*)"iterations"

# define TAG_COST                   (char*)"cost"
# define TAG_COST_DEFINITION        (char*)"cost_evaluation_definition"

# define TAG_GENERATIONS            (char*)"generations"
# define TAG_GENERATIONS_DEFINITION (char*)"generations_evaluation_definition"

# define TAG_EDGE                   (char*)"edge"
# define TAG_NODE                   (char*)"node"

Evaluation::Evaluation(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _lifeTime    = -1;
  _nodeCost    = 0.0;
  _edgeCost    = 0.0;
  _generations = -1;
}

// Evaluation::~Evaluation()
// { }


void Evaluation::add(ParseElement *element)
{
  VLOG(100) << "parsing: " << element->name();

  if(element->closing(TAG_EVALUATION))
  {
    current = parent;
    return;
  }

  if(element->opening(TAG_LIFE_TIME))
  {
    element->set(TAG_ITERATIONS, _lifeTime);
  }

  if(element->opening(TAG_GENERATIONS))
  {
    element->set(TAG_ITERATIONS, _generations);
  }

  if(element->opening(TAG_COST))
  {
    element->set(TAG_NODE, _nodeCost);
    element->set(TAG_EDGE, _edgeCost);
  }

}

void Evaluation::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_EVALUATION_DEFINITION);
  root->add(NE(TAG_LIFE_TIME,   TAG_LIFE_TIME_DEFINITION,   1, 1));
  root->add(NE(TAG_GENERATIONS, TAG_GENERATIONS_DEFINITION, 0, 1));
  root->add(NE(TAG_COST,        TAG_COST_DEFINITION,        1, 1));
  spec->add(root);

  XsdSequence *lifeTime = new XsdSequence(TAG_LIFE_TIME_DEFINITION);
  lifeTime->add(NA(TAG_ITERATIONS, TAG_POSITIVE_INTEGER, true));
  spec->add(lifeTime);

  XsdSequence *generations = new XsdSequence(TAG_GENERATIONS_DEFINITION);
  generations->add(NA(TAG_ITERATIONS, TAG_POSITIVE_INTEGER, true));
  spec->add(generations);

  XsdSequence *cost = new XsdSequence(TAG_COST_DEFINITION);
  cost->add(NA(TAG_NODE, TAG_POSITIVE_DECIMAL, false));
  cost->add(NA(TAG_EDGE, TAG_POSITIVE_DECIMAL, false));
  spec->add(cost);

}

int Evaluation::lifeTime()
{
  return _lifeTime;
}

int Evaluation::generations()
{
  return _generations;
}

double Evaluation::nodeCost()
{
  return _nodeCost;
}

double Evaluation::edgeCost()
{
  return _edgeCost;
}

