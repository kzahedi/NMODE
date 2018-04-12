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
  for(int i = 0; i < _population->i_size(); i++)
  {
    _population->individual(i)->setNrOfOffspring(5);
  }
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

  while(_population->i_size() < _populationSize)
  {
    __createOffspring();
  }

  __createRandomOffspring();

  _population->reproductionCompleted();
}

void Reproduction::__createRandomOffspring()
{
  Individual *ind = CFG->individual()->copy();
  ind->setAge(0);
  _mutation->mutate(ind);
  _population->addIndividual(ind);
}

void Reproduction::__select()
{
  Individuals paretoFront;

  int populationSize = REP->populationSize();
  int populationSizeCmp = _population->i_size();
  int tournamentSize = (int)(REP->tournamentPercentage() * populationSize);
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
      paretoFront[i]->setSelected(false);

    for(int i = 0; i < paretoFront.size(); i++)
    {
      for(int j = 0; j < paretoFront.size(); j++)
      {
        if(i != j)
        {
          bool dominantInAge     = paretoFront[j]->age()     <  paretoFront[i]->age();
          bool dominantInFitness = paretoFront[j]->fitness() >= paretoFront[i]->fitness();
          if(AGE(i) <  AGE(j) && FITNESS(i) >= FITNESS(j)) paretoFront[j]->setSelected(true);
          if(AGE(i) == AGE(j) && FITNESS(i) >= FITNESS(j)) paretoFront[j]->setSelected(true);
        }
      }
    }

    FORC(Individuals, ind, paretoFront)
    {
      cout << "Individual: " << (*ind)->id()
        << " Fitness: " << (*ind)->fitness()
        << " Age: " << (*ind)->age()
        << " Selected: " << (((*ind)->isSelected()?"true":"false")) << endl;
    }

    FORC(Individuals, ind, paretoFront)
      if((*ind)->isSelected() == true) // selected for removal
        _population->i_remove(*ind);

    populationSizeCmp = _population->i_size();
  }

  _population->incAge();
}

void Reproduction::__randomPairing()
{
  FORF(Individuals, i, _population, i_begin(), i_end())
  {
    for(int j = 0; j < (*i)->nrOfOffspring(); j++)
    {
      Individual *mom = *i;
      Individual *dad = NULL;
      if(_population->i_size() > 1)
      {
        int n = 0;
        do { dad = __getRandomMate(); } while (dad == mom && (n++ < 100));
      }
      else
      {
        dad = mom;
      }
      Parents *parents = new Parents(mom, dad);
      _parents.push_back(parents);
    }
  }
}

Individual* Reproduction::__getRandomMate()
{
  // int index = (int)(Random::unit() * _population->i_size());
  // return _population->individual(index);
  double dice = Random::unit();
  double s = 0.0;
  FORF(Individuals, i, _population, i_begin(), i_end())
  {
    s += (*i)->reproductionFactor();
    if(dice < s)
    {
      return *i;
    }
  }
  return NULL;
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
    // child->setAge(0);
  }
  else
  {
    child = p->mom->copy(true);
    child->setAge(p->mom->age());
  }
  child->setEvaluated(false);

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
