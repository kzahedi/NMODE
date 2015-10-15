#include "Evaluation.h"

#include <iostream>
#include <glog/logging.h>

using namespace std;

# define TAG_LIFE_TIME                  (char*)"lifetime"
# define TAG_LIFE_TIME_DEFINITION       (char*)"lifetime_definition"
# define TAG_ITERATIONS                 (char*)"iterations"

Evaluation::Evaluation(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _lifeTime       = -1;
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

}

void Evaluation::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_EVALUATION_DEFINITION);
  root->add(NE(TAG_LIFE_TIME,       TAG_LIFE_TIME_DEFINITION,       1, 1));
  spec->add(root);

  XsdSequence *lifeTime = new XsdSequence(TAG_LIFE_TIME_DEFINITION);
  lifeTime->add(NA(TAG_ITERATIONS, TAG_POSITIVE_INTEGER, true));
  spec->add(lifeTime);

}

int Evaluation::lifeTime()
{
  return _lifeTime;
}
