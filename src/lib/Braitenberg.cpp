#include "Braitenberg.h"

#include <nmode/RnnFromIndividual.h>
#include <nmode/Data.h>

#include <sstream>

Braitenberg::Braitenberg()
  : Evaluate()
{
  _networkInput.resize(2);
}


void Braitenberg::updateController()
{
  _networkInput[0] = 0.0;
  _networkInput[1] = 0.0;

  for(int j = 0; j < 3; j++)
  {
    _networkInput[0] += _sensorValues[j];
    _networkInput[1] += _sensorValues[3 + j];
  }

  _networkInput[0] /= 3.0;
  _networkInput[1] /= 3.0;
}

void Braitenberg::updateFitnessFunction()
{
  _fitness += _sensorValues[8] - _sensorValues[9];
}

bool Braitenberg::abort()
{
  return false;
}

void Braitenberg::newIndividual()
{
}

// the class factories
extern "C" Evaluate* create()
{
  Braitenberg *e = new Braitenberg();
  return (Evaluate*)e;
}

extern "C" void destroy(Evaluate* controller) {}
