#include "PopulationContainer.h"
#include "mutex.h"

#include <unistd.h>

PopulationContainer::PopulationContainer()
{
  ENP_INIT;
  _population      = NULL;
  _nextIndividual  = 0;
  _openEvaluations = 0;
}

void PopulationContainer::update(Population *p)
{
  // if(_population != NULL)
  // {
  // delete _population;
  // }
  _population     = p;
  _nextIndividual = 0;
}

void PopulationContainer::evaluationCompleted()
{
  _openEvaluations--;
}

Individual* PopulationContainer::getNextIndividual()
{
  ENP_LOCK;

  while(_population == NULL) usleep(500); // wait for the first update

  if(_nextIndividual >= _population->i_size())
  {
    while(_openEvaluations > 0) usleep(500); // wait for the others to complete
    notifyObservers(_m_next_generation);
  }

  Individual *i = _population->individual(_nextIndividual);
  _nextIndividual++;
  _openEvaluations++;

  ENP_UNLOCK;
  return i;
}
