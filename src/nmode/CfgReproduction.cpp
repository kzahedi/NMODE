#include <nmode/CfgReproduction.h>

#include <nmode/XsdSpecification.h>
#include <nmode/macros.h>

#include <iostream>
#include <glog/logging.h>

using namespace std;

# define TAG_PROBABILITY                (char*)"probability"
# define TAG_PROBABILITY_DEFINITION     (char*)"probability_definition"

# define TAG_CROSSOVER                  (char*)"crossover"
# define TAG_CROSSOVER_DEFINTION        (char*)"crossover_cfg_definition"

# define TAG_POPULATION_SIZE            (char*)"population"
# define TAG_POPULATION_SIZE_DEFINITION (char*)"population_size_definition"
# define TAG_SIZE                       (char*)"size"
# define TAG_LOG                        (char*)"log"
# define TAG_TOURNAMENT                 (char*)"tournament"

CfgReproduction::CfgReproduction(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _populationSize       = 100;
  _loggingSize          = 100;
  _crossoverProbability = 0.0;
  _tournament           = 0.1;
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

  if(element->opening(TAG_CROSSOVER))
  {
    element->set(TAG_PROBABILITY, _crossoverProbability);
  }

  if(element->opening(TAG_POPULATION_SIZE))
  {
    element->set(TAG_SIZE,       _populationSize);
    element->set(TAG_TOURNAMENT, _tournament);
    element->set(TAG_LOG,        _loggingSize);
    _loggingSize = MIN(_populationSize, _loggingSize);
  }
}

void CfgReproduction::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_REPRODUCTION_DEFINITION);
  root->add(NE(TAG_POPULATION_SIZE, TAG_POPULATION_SIZE_DEFINITION, 1, 1));
  root->add(NE(TAG_CROSSOVER,       TAG_CROSSOVER_DEFINTION,        1, 1));
  spec->add(root);

  XsdSequence *pop = new XsdSequence(TAG_POPULATION_SIZE_DEFINITION);
  pop->add(NA(TAG_SIZE,       TAG_POSITIVE_INTEGER, true));
  pop->add(NA(TAG_TOURNAMENT, TAG_UNIT_INTERVAL,    true));
  pop->add(NA(TAG_LOG,        TAG_POSITIVE_INTEGER, true));
  spec->add(pop);


}

int CfgReproduction::populationSize()
{
  return _populationSize;
}

double CfgReproduction::crossoverProbability()
{
  return _crossoverProbability;
}

double CfgReproduction::tournamentPercentage()
{
  return _tournament;
}

int CfgReproduction::loggingSize()
{
  return _loggingSize;
}
