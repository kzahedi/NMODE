#include "CfgReproduction.h"

#include "XsdSpecification.h"

#include <iostream>
#include <glog/logging.h>


using namespace std;

# define TAG_SELECTION                  (char*)"selection"
# define TAG_SELECTION_DEFINTION        (char*)"selection_cfg_definition"
# define TAG_PRESSURE                   (char*)"pressure"

# define TAG_POPULATION_SIZE            (char*)"population"
# define TAG_POPULATION_SIZE_DEFINITION (char*)"population_size_definition"
# define TAG_SIZE                       (char*)"size"


CfgReproduction::CfgReproduction(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _populationSize    = 100;
  _selectionPressure = 0.1;
}

// CfgReproduction::~CfgReproduction()
// { }


void CfgReproduction::add(ParseElement *element)
{
  VLOG(100) << "parsing: " << element->name();

  if(element->closing(TAG_REPRODUCTION))
  {
    current = parent;
    return;
  }

  if(element->opening(TAG_SELECTION))
  {
    element->set(TAG_PRESSURE, _selectionPressure);
  }

  if(element->opening(TAG_POPULATION_SIZE))
  {
    element->set(TAG_SIZE, _populationSize);
  }

}

void CfgReproduction::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_REPRODUCTION_DEFINITION);
  root->add(NE(TAG_POPULATION_SIZE, TAG_POPULATION_SIZE_DEFINITION, 1, 1));
  root->add(NE(TAG_SELECTION,       TAG_SELECTION_DEFINTION,        1, 1));
  spec->add(root);

  XsdSequence *selection = new XsdSequence(TAG_SELECTION_DEFINTION);
  selection->add(NA(TAG_PRESSURE, TAG_POSITIVE_NON_ZERO_DECIMAL, true));
  spec->add(selection);

  XsdSequence *pop = new XsdSequence(TAG_POPULATION_SIZE);
  pop->add(NA(TAG_SIZE, TAG_POSITIVE_INTEGER, true));
  spec->add(pop);
}

int CfgReproduction::populationSize()
{
  return _populationSize;
}

double CfgReproduction::selectionPressure()
{
  return _selectionPressure;
}
