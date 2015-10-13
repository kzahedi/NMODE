#include "Population.h"
#include "Observable.h"

#include <pthread.h>


class PopulationContainer : public Observable
{
  public:
    PopulationContainer();

    void update(Population *p);

    Individual* getNextIndividual();

  private:
    pthread_mutex_t _mutex;
    Population*     _population;
    int             _nextIndividual;
  
};


