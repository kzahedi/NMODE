#include <nmode/CfgReproduction.h>

#include <nmode/XsdSpecification.h>

#include <iostream>
#include <glog/logging.h>


using namespace std;

# define TAG_SELECTION                       (char*)"selection"
# define TAG_SELECTION_DEFINTION             (char*)"selection_cfg_definition"

# define TAG_PROBABILITY                     (char*)"probability"
# define TAG_PROBABILITY_DEFINITION          (char*)"probability_definition"

# define TAG_CROSSOVER                       (char*)"crossover"
# define TAG_CROSSOVER_DEFINTION             (char*)"crossover_cfg_definition"

# define TAG_ELITE                    (char*)"elite"
# define TAG_ELITE_PRESSURE_DEFINTION (char*)"elite_pressure_cfg_definition"

# define TAG_PRESSURE                        (char*)"pressure"

# define TAG_POPULATION_SIZE                 (char*)"population"
# define TAG_POPULATION_SIZE_DEFINITION      (char*)"population_size_definition"
# define TAG_SIZE                            (char*)"size"


CfgReproduction::CfgReproduction(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _populationSize    = 100;
  _selectionPressure = 0.1;
  _elitePressure = 0.1;
  _crossoverProbability = 0.0;
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

  if(element->opening(TAG_ELITE))
  {
    element->set(TAG_PRESSURE, _elitePressure);
  }

  if(element->opening(TAG_CROSSOVER))
  {
    element->set(TAG_PROBABILITY, _crossoverProbability);
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
  root->add(NE(TAG_ELITE,           TAG_ELITE_PRESSURE_DEFINTION,   1, 1));
  root->add(NE(TAG_CROSSOVER,       TAG_CROSSOVER_DEFINTION,        1, 1));
  spec->add(root);

  XsdSequence *selection = new XsdSequence(TAG_SELECTION_DEFINTION);
  selection->add(NA(TAG_PRESSURE, TAG_POSITIVE_NON_ZERO_DECIMAL, true));
  spec->add(selection);

  XsdSequence *reproduction = new XsdSequence(TAG_ELITE_PRESSURE_DEFINTION);
  reproduction->add(NA(TAG_PRESSURE, TAG_POSITIVE_NON_ZERO_DECIMAL, true));
  spec->add(reproduction);

  XsdSequence *crossover = new XsdSequence(TAG_CROSSOVER_DEFINTION);
  crossover->add(NA(TAG_PROBABILITY, TAG_UNIT_INTERVAL, true));
  spec->add(crossover);

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

double CfgReproduction::elitePressure()
{
  return _elitePressure;
}

double CfgReproduction::crossoverProbability()
{
  return _crossoverProbability;
}
