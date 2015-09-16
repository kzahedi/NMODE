#include "Population.h"

#include "glog/logging.h"

#define TAG_GENERATION (char*)"generation"

Population::Population(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _generation = 1;
}

void Population::add(DataParseElement *element)
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
    Individual *i = new Individual(this);
    _individuals.push_back(i);
    current = i;
    current->add(element);
  }
}

void Population::createXsd(XsdSpecification *spec)
{
  XsdSequence *_root = new XsdSequence(TAG_POPULATION_DEFINITION);
  _root->add(NA(TAG_GENERATION, TAG_POSITIVE_INTEGER,      false));
  _root->add(NE(TAG_INDIVIDUAL, TAG_INDIVIDUAL_DEFINITION, 1, TAG_XSD_UNBOUNDED));
  spec->add(_root);

  Module::createXsd(spec);
}

Individuals::iterator Population::i_begin()
{
  return _individuals.begin();
}

Individuals::iterator Population::i_end()
{
  return _individuals.end();
}

int Population::i_size()
{
  return _individuals.size();
}

Individuals Population::individuals()
{
  return _individuals;
}

Individual Population::individual(int index)
{
  return _individuals[index];
}

int Population::generation()
{
  return _generation;
}

