#include "Population.h"
#include "Individual.h"
#include "Module.h"

#include "base/data/Data.h"

#include <glog/logging.h>

Population::Population()
{
  _generation = 1;
}

Population::~Population()
{}

void Population::initialise()
{
  DataENP           *data = Data::instance()->specification();
  DataConfiguration *cfg  = data->configuration();
  DataPopulation    *pop  = data->population();

  if(pop != NULL && pop->i_size() > 0)
  {
    VLOG(100) << "initialising from stored population";
    for(DataIndividuals::iterator i = pop->i_begin(); i != pop->i_end(); i++)
    {
      VLOG(100) << "found individual with " << (*i)->fitness() << " and " << (*i)->id();
      Individual *ind = new Individual();
      ind->initialise(*i);
      _individuals.push_back(ind);
    }
  }
  else
  {
    VLOG(100) << "initialising from specification";
    Individual *ind = new Individual();
    _individuals.push_back(ind);
    for(DataModules::iterator m = cfg->m_begin(); m != cfg->m_end(); m++)
    {
      ind->add(*m);
    }
  }
}


Individual* Population::individual(int index)
{
  return _individuals[index];
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

int Population::generation()
{
  return _generation;
}
