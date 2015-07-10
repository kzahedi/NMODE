#include "DataPopulation.h"

#include "glog/logging.h"

#define TAG_GENERATION (char*)"generation"

DataPopulation::DataPopulation(DataNode *parent)
  : DataNode(parent)
{
  _generation = 1;
}

void DataPopulation::add(DataParseElement *element)
{
  VLOG(100) << "parsing " << element->name();
  if(element->closing(TAG_POPULATION))
  {
    current = parent;
  }

  if(element->opening(TAG_POPULATION))
  {
    element->set(TAG_GENERATION, _generation);
    VLOG(100) << "set generation to " << _generation;
  }

  if(element->opening(TAG_INDIVIDUAL))
  {
    VLOG(100) << "found " << TAG_INDIVIDUAL;
    DataIndividual *i = new DataIndividual(this);
    _individuals.push_back(i);
    current = i;
    current->add(element);
  }
}

void DataPopulation::createXsd(XsdSpecification *spec)
{
  XsdSequence *_root = new XsdSequence(TAG_POPULATION_DEFINITION);
  _root->add(NA(TAG_GENERATION, TAG_POSITIVE_INTEGER,      false));
  _root->add(NE(TAG_INDIVIDUAL, TAG_INDIVIDUAL_DEFINITION, 1, TAG_XSD_UNBOUNDED));
  spec->add(_root);

  DataModule::createXsd(spec);
}

DataIndividuals::iterator DataPopulation::i_begin()
{
  return _individuals.begin();
}

DataIndividuals::iterator DataPopulation::i_end()
{
  return _individuals.end();
}

int DataPopulation::i_size()
{
  return _individuals.size();
}

DataIndividuals DataPopulation::individuals()
{
  return _individuals;
}

