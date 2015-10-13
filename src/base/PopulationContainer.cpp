#include "PopulationContainer.h"
#include "mutex.h"

#include <unistd.h>

PopulationContainer::PopulationContainer()
{
  ENP_INIT;
  _nextIndividual = 0;
}

void PopulationContainer::update(Population *p)
{
  // if(_population != NULL)
  // {
  // delete _population;
  // }
  _population = p;
  _nextIndividual = 0;
}

Individual* PopulationContainer::getNextIndividual()
{
  ENP_LOCK;

  cout << "CII: " << _nextIndividual << " " << _population->i_size() << endl;

  if(_nextIndividual >= _population->i_size())
  {
    notifyObservers(_m_next_generation);
  }

  while(_nextIndividual >= _population->i_size()) usleep(100);

  Individual *i = _population->individual(_nextIndividual);
  _nextIndividual++;

  ENP_UNLOCK;
  return i;
}
