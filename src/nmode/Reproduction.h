#ifndef __REPRODUCTION_H__
#define __REPRODUCTION_H__

#include <nmode/Population.h>
#include <nmode/Mutation.h>

#define PAIRING_METHOD_RANDOM 1001

#define SELECTION_METHOD_RANK 2001

class Parents
{
  public:
    Parents(Individual *m, Individual *d)
    {
      mom = m;
      dad = d;
      fitness = mom->fitness();
    };

    Individual *mom;
    Individual *dad;
    double      fitness;
};

typedef vector<Parents*> ListOfParents;

class Reproduction
{
  public:
    Reproduction();
    ~Reproduction();

    void reproduce();
    void firstReproduction();
    void setCrossoverProbability(double p);

  private:

    void        __select();
    void        __randomPairing();
    void        __createOffspring();
    void        __createRandomOffspring();
    void        __adaptNodeConfigurationFromCfg();
    Individual* __getRandomMate();
    Parents*    __randomlySelectParent();
    Individual* __cross(Individual*, Individual*);

    double        _selectionPressure;
    double        _crossoverProbability;
    int           _pairingMethod;
    int           _populationSize;
    ListOfParents _parents;
    Population*   _population;
    Mutation*     _mutation;
};

#endif // __REPRODUCTION_H__
