#include "Reproduction.h"

#include "base/Random.h"
#include "base/macros.h"
#include "base/Data.h"

#include "Mutation.h"

#include <glog/logging.h>

Reproduction::Reproduction()
{
  _pairingMethod        = PAIRING_METHOD_RANDOM;
  _selectionMethod      = SELECTION_METHOD_RANK;
  _population           = Population::instance();
  _crossoverProbability = 0.0;
  _mutation             = new Mutation();
  _populationSize       = Data::instance()->specification()->reproduction()->populationSize();
  _selectionPressure    = Data::instance()->specification()->reproduction()->selectionPressure();
}

Reproduction::~Reproduction()
{
  // if(_next_generation != NULL) delete _next_generation;
}

void Reproduction::setCrossoverProbability(double p)
{
  _crossoverProbability = p;
}

void Reproduction::reproduce()
{
  switch(_selectionMethod)
  {
    case SELECTION_METHOD_RANK:
      VLOG(100) << "using rank based selection";
      __select();
      break;
  }

  _population->incGeneration();
  _population->calculateSelectionProbabilities();

  _parents.clear();

  switch(_pairingMethod)
  {
    case PAIRING_METHOD_RANDOM:
      VLOG(100) << "using random pairing";
      __randomPairing();
      break;
  }

  while(_population->i_size() < _populationSize)
  {
    __createOffspring();
  }
  cout << "Population size after generation of offspring: " << _population->i_size() << endl;
}

void Reproduction::__select()
{
  int nrOfParents = int(_population->i_size() * _selectionPressure + 0.5);
  nrOfParents = MAX(1, nrOfParents);
  nrOfParents = MIN(nrOfParents, _population->i_size());

  VLOG(100) << "number of parents: " << nrOfParents;

  _population->sortByFitness();
  _population->resize(nrOfParents);
  cout << "Population size after selection: " << _population->i_size() << endl;
}

void Reproduction::__randomPairing()
{
  FORF(Individuals, i, _population, i_begin(), i_end())
  {
    Individual *dad = *i;
    Individual *mom = NULL;
    if(_population->i_size() > 1)
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
  FORF(Individuals, i, _population, i_begin(), i_end())
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
  _population->addIndividual(child);
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
