#include "base/Population.h"

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

    Population* reproduce(Population *p);
    void setCrossoverProbability(double p);

  private:

    void        __select(Population *p);
    void        __randomPairing();
    void        __createOffspring();
    Individual* __getRandomMate();
    Parents*    __randomlySelectParent();
    Individual* __cross(Individual*, Individual*);

    double        _selectionPressure;
    double        _crossoverProbability;
    int           _pairingMethod;
    int           _selectionMethod;
    int           _populationSize;
    ListOfParents _parents;
    Population*   _next_generation;
};

