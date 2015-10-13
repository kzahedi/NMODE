#include "Population.h"

class PopulationContainer
{
  public:
    PopulationContainer();

    void update(Population *p);

    Individual* getNextIndividual();

  private:
    Population *_population;
};


