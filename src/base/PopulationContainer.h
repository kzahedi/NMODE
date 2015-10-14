#ifndef __POPULATION_CONTAINER_H__
#define __POPULATION_CONTAINER_H__
#include "Population.h"
#include "Observable.h"

#include <pthread.h>


class PopulationContainer : public Observable
{
  public:
    PopulationContainer();

    void update(Population *p);
    void evaluationCompleted();

    Individual* getNextIndividual();

  private:
    pthread_mutex_t _mutex;
    Population*     _population;
    int             _nextIndividual;
    int             _openEvaluations;
  
};

#endif // __POPULATION_CONTAINER_H__
