#include "Reproduction.h"

#include "base/Random.h"
#include "base/macros.h"

#include "Mutation.h"

#include <glog/logging.h>

Reproduction::Reproduction()
{
  _pairingMethod        = PAIRING_METHOD_RANDOM;
  _selectionMethod      = SELECTION_METHOD_RANK;
  _next_generation      = NULL;
  _crossoverProbability = 0.1;
  _mutation             = new Mutation();
}

Reproduction::~Reproduction()
{
  // if(_next_generation != NULL) delete _next_generation;
}

void Reproduction::setCrossoverProbability(double p)
{
  _crossoverProbability = p;
}

Population* Reproduction::reproduce(Population *p)
{
  switch(_selectionMethod)
  {
    case SELECTION_METHOD_RANK:
      VLOG(100) << "using rank based selection";
      __select(p);
      break;
  }

  _next_generation->incGeneration();
  _next_generation->calculateSelectionProbabilities();

  _parents.clear();

  switch(_pairingMethod)
  {
    case PAIRING_METHOD_RANDOM:
      VLOG(100) << "using random pairing";
      __randomPairing();
      break;
  }

  while(_next_generation->i_size() < _populationSize)
  {
    __createOffspring();
  }

  return _next_generation;
}

void Reproduction::__select(Population *p)
{
  if(_next_generation != NULL)
  {
    _next_generation = new Population();
  }

  int nrOfParents = int(p->i_size() * _selectionPressure + 0.5);
  VLOG(100) << "number of parents: " << nrOfParents;

  p->sortByFitness();

  for(int i = 0; i < nrOfParents; i++)
  {
    _next_generation->addIndividual(p->individual(i));
  }
}

void Reproduction::__randomPairing()
{
  FORF(Individuals, i, _next_generation, i_begin(), i_end())
  {
    Individual *dad = *i;
    Individual *mom = NULL;
    if(_next_generation->i_size() > 0)
    {
      do { mom = __getRandomMate(); } while (mom == dad);
    }
    else
    {
      mom = dad;
    }
    Parents *parents = new Parents(dad, mom);
    _parents.push_back(parents);
  }
}

Individual* Reproduction::__getRandomMate()
{
  double dice = Random::unit();
  double s = 0.0;
  FORF(Individuals, i, _next_generation, i_begin(), i_end())
  {
    s += (*i)->probability();
    if(s > dice)
    {
      return *i;
    }
  }
  return NULL;
}


Parents* Reproduction::__randomlySelectParent()
{
  return _parents[0];
}

void Reproduction::__createOffspring()
{
  Parents *p = __randomlySelectParent();

  Individual *child = NULL;
  if(_crossoverProbability > 0.0)
  {
    child = __cross(p->mom, p->dad);
  }
  else
  {
    child = p->mom->copy();
  }

  _mutation->mutate(child);
  _next_generation->addIndividual(child);
}

Individual* Reproduction::__cross(Individual *mom, Individual *dad)
{
  Individual *child = new Individual();
  FORI(0, mom->m_size(), i)
  {
    if(dad->module(i)->isCopy() == false &&
       Random::unit() < _crossoverProbability)
    {
      VLOG(100) << "crossing module " << dad->module(i)->name();
      child->addModule(dad->module(i)->copy());
    }
    else
    {
      child->addModule(mom->module(i)->copy());
    }
  }
  return child;
}
