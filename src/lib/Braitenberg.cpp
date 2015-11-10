#include "Braitenberg.h"

#include <nmode/RnnFromIndividual.h>
#include <nmode/Data.h>

#include <sstream>

Braitenberg::Braitenberg()
  : Evaluate()
{
  networkInput.resize(2);
}


void Braitenberg::updateController()
{
  networkInput[0] = 0.0;
  networkInput[1] = 0.0;

  for(int j = 0; j < 3; j++)
  {
    networkInput[0] += sensorValues[j];
    networkInput[1] += sensorValues[3 + j];
  }

  networkInput[0] /= 3.0;
  networkInput[1] /= 3.0;
}

void Braitenberg::updateFitnessFunction()
{
  fitness += sensorValues[8] - sensorValues[9];
}

bool Braitenberg::abort()
{
  return false;
}

void Braitenberg::newIndividual()
{ }

void Braitenberg::evaluationCompleted()
{ }

// the class factories
extern "C" Evaluate* create()
{
  Braitenberg *e = new Braitenberg();
  return (Evaluate*)e;
}

extern "C" void destroy(Evaluate* controller) {}
