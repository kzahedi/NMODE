#include "Population.h"
#include "macros.h"

#include <glog/logging.h>

#define TAG_GENERATION (char*)"generation"

Population* Population::_me = NULL;

Population::Population(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _generation   = 1;
  _individualId = 0;
  _me = this;
}

void Population::add(ParseElement *element)
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

Individual* Population::individual(int index)
{
  return _individuals[index];
}

int Population::generation()
{
  return _generation;
}

void Population::addIndividual(Individual *i)
{
  i->setId(_individualId);
  _individualId++;
  _individuals.push_back(i);
}

bool fnSortByFitness(Individual *a, Individual *b) {return (a->fitness() > b->fitness());}

void Population::sortByFitness()
{
  sort(_individuals.begin(), _individuals.end(), fnSortByFitness);
}

void Population::incGeneration()
{
  _generation++;
}


void Population::calculateSelectionProbabilities()
{
  double sum = 0.0;
  double min = _individuals[0]->fitness();
  vector<double> fitness(_individuals.size());

  FORI(0, _individuals.size(), i) fitness[i] = _individuals[i]->fitness();
  FORI(0, fitness.size(), i)      if(min > fitness[i]) min = fitness[i];
  FORI(0, fitness.size(), i)      fitness[i] += min;
  FORI(0, fitness.size(), i)      sum += fitness[i];
  FORI(0, fitness.size(), i)      _individuals[i]->setProbability(fitness[i] / sum);
}

Population* Population::instance()
{
  return _me;
}

void Population::resize(int size)
{
  _individuals.resize(size);
}

