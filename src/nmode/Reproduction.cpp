#include <nmode/Reproduction.h>

#include <nmode/Random.h>
#include <nmode/macros.h>
#include <nmode/Data.h>

#include <nmode/Mutation.h>

#include <glog/logging.h>

# define AGE(i)     paretoFront[i]->age()
# define FITNESS(i) paretoFront[i]->fitness()

Reproduction::Reproduction()
{
  _pairingMethod        = PAIRING_METHOD_RANDOM;
  _population           = Population::instance();
  _crossoverProbability = Data::instance()->specification()->reproduction()->crossoverProbability();
  _mutation             = new Mutation();
  _populationSize       = Data::instance()->specification()->reproduction()->populationSize();
}

Reproduction::~Reproduction()
{
  // if(_next_generation != NULL) delete _next_generation;
}

void Reproduction::firstReproduction()
{
  // Individual *ind = CFG->individual()->copy();
  // _population->addIndividual(ind);
  _population->incGeneration();
  _population->serialise();
  _population->plotLast();
  __randomPairing();
  _populationSize = REP->populationSize() + 1;
  while(_population->i_size() < _populationSize)
  {
    __createOffspring();
  }
  _population->removeFirstIndividual();
  _population->reproductionCompleted();
}

void Reproduction::reproduce()
{
  __select();
  __adaptNodeConfigurationFromCfg();

  _population->incGeneration();
  _population->serialise();
  _population->plotLast();

  _parents.clear();

  switch(_pairingMethod)
  {
    case PAIRING_METHOD_RANDOM:
      VLOG(100) << "using random pairing";
      __randomPairing();
      break;
  }

  _populationSize = Data::instance()->specification()->reproduction()->populationSize();

  while(_population->i_size() < _populationSize-1)
  {
    __createOffspring();
  }

  __createRandomOffspring();

  _population->incAge();

  _population->reproductionCompleted();
}

void Reproduction::__createRandomOffspring()
{
  Individual *ind = CFG->individual()->copy();
  ind->setAge(0);
  _mutation->mutate(ind);
  ind->setEvaluated(false);
  _population->addIndividual(ind);
}

void Reproduction::__select()
{
  Individuals paretoFront;

  int populationSize          = REP->populationSize();
  int populationSizeCmp       = _population->i_size();
  int tournamentSize          = (int)(populationSize * REP->tournamentPercentage());
  int nrOfSelectedIndividuals = MAX(5, tournamentSize);

  while(populationSize < populationSizeCmp)
  {
    while(paretoFront.size() < nrOfSelectedIndividuals)
    {
      int randomIndex = Random::randi(0, populationSize);
      Individual* i = _population->individual(randomIndex);
      bool found = false;
      FORC(Individuals, ind, paretoFront)
      {
        if((*ind)->id() == i->id())
        {
          found = true;
          break;
        }
      }
      if(found == false)
      {
        paretoFront.push_back(i);
      }
    }

    for(int i = 0; i < paretoFront.size(); i++)
      paretoFront[i]->setDominated(false);

    for(int i = 0; i < paretoFront.size(); i++)
    {
      for(int j = 0; j < paretoFront.size(); j++)
      {
        if(i != j)
        {
          if(AGE(i) <  AGE(j) && FITNESS(i) >= FITNESS(j)) paretoFront[j]->setDominated(true);
          if(AGE(i) == AGE(j) && FITNESS(i) >= FITNESS(j)) paretoFront[j]->setDominated(true);
        }
      }
    }

    // FORC(Individuals, ind, paretoFront)
    // {
      // cout << "Individual: " << (*ind)->id()
        // << " Fitness: " << (*ind)->fitness()
        // << " Age: " << (*ind)->age()
        // << " Dominated: " << (((*ind)->isDominated()?"true":"false")) << endl;
    // }

    FORC(Individuals, ind, paretoFront)
      if((*ind)->isDominated() == true) // selected for removal
        _population->i_remove(*ind);

    populationSizeCmp = _population->i_size();
  }

}

void Reproduction::__randomPairing()
{
  // -1 for the new random individual
  int nrOfPairings = REP->populationSize() - _population->i_size() - 1;
  if(_population->i_size() == 1)
  {
    for(int i = 0; i < nrOfPairings; i++)
    {
      Individual *ind = _population->individual(0);
      Parents *parents = new Parents(ind, ind);
      _parents.push_back(parents);
    }
    return;
  }

  // if there is more than one in the population
  for(int i = 0; i < nrOfPairings; i++)
  {
    Individual *mom = NULL;
    Individual *dad = NULL;
    while(mom == dad)
    {
      mom = __getRandomMate();
      dad = __getRandomMate();
    }
    Parents *parents = new Parents(mom, dad);
    _parents.push_back(parents);
  }
}

Individual* Reproduction::__getRandomMate()
{
  int index = Random::randi(0, _population->i_size()-1);
  return _population->individual(index);
}


Parents* Reproduction::__randomlySelectParent()
{
  int parentIndex = (int)(Random::unit() * _parents.size());
  return _parents[parentIndex];
}

void Reproduction::__createOffspring()
{
  Parents *p = __randomlySelectParent();

  Individual *child = NULL;
  if(_crossoverProbability > 0.0)
  {
    child = __cross(p->mom, p->dad);
    child->setAge(MAX(p->mom->age(), p->dad->age()));
    // cout << "mom's age: " << p->mom->age() << " id " << p->mom->id() << endl;
    // cout << "dad's age: " << p->dad->age() << " id " << p->dad->id() << endl;
    child->setEvaluated(false);
  }
  else
  {
    child = p->mom->copy(true);
    child->setAge(p->mom->age());
    // cout << "mom's age: " << p->mom->age() << endl;
    child->setEvaluated(false);
  }

  // cout << "Child: " << child->age() << endl;

  _mutation->mutate(child);

  _population->addIndividual(child);
}

Individual* Reproduction::__cross(Individual *mom, Individual *dad)
{
  // cout << "crossing module?" << endl;
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


void Reproduction::__adaptNodeConfigurationFromCfg()
{
  Configuration *cfg = Data::instance()->specification()->configuration();

  for(int m = 0; m < cfg->m_size(); m++)
  {
    for(int n = 0; n < cfg->module(m)->n_size(); n++)
    {
      Node *node = cfg->module(m)->node(n);
      if(node->type() != "hidden")
      {
        _population->setInactive(m, n, node->isInactive());
      }
    }
  }
}
