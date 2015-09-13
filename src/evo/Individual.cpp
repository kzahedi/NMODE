#include "Individual.h"
#include "base/data/DataModule.h"
#include "Module.h"

#include <glog/logging.h>

Individual::Individual()
{}

Individual::~Individual()
{}

void Individual::setFitness(double fitness)
{
  _fitness = fitness;
  VLOG(100) << "setting fitness to " << _fitness;
}

void Individual::setId(int id)
{
  _id = id;
  VLOG(100) << "setting id to " << _id;
}

double Individual::fitness()
{
  return _fitness;
}

int Individual::id()
{
  return _id;
}

void Individual::initialise(DataIndividual *data)
{
  _fitness = data->fitness();
  _id      = data->id();
}

void Individual::add(DataModule *data)
{
  Module *mod = new Module(data->name());
  mod->initialise(data);
  _modules.push_back(mod);
}

Module* Individual::module(int index)
{
  return _modules[index];
}

Modules::iterator Individual::m_begin()
{
  return _modules.begin();
}

Modules::iterator Individual::m_end()
{
  return _modules.end();
}

int Individual::m_size()
{
  return _modules.size();
}

