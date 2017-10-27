#include "Hexaboard.h"

#include <nmode/RnnFromIndividual.h>
#include <nmode/Data.h>

#include <sstream>

#ifndef MIN3
# define MIN3(a,c,b) ((a<b)?((c<a)?c:a):(c<b)?c:b)
#endif

# define SIGN(y) ((y<0)?-1:1)

Hexaboard::Hexaboard()
  : Evaluate()
{
  networkInput.resize(31);
  _intermediateFitness = 0.0;
}

void Hexaboard::updateController()
{
  _gamma = sensorValues[23];

  if(fabs(_gamma) > 90.0)
  {
    _abort = true;
  }

  for(int i = 0; i < (int)networkInput.size(); i++)
  {
    networkInput[i] = sensorValues[i];
  }
}

void Hexaboard::updateFitnessFunction()
{
  _y     = sensorValues[19]; // checked 13.10.2017

  _intermediateFitness += _y;

  fitness = _intermediateFitness;
}

bool Hexaboard::abort()
{
  return _abort;
}

void Hexaboard::newIndividual()
{
  _abort = false;
  stringstream sst;
  _intermediateFitness = 0.0;
}

void Hexaboard::evaluationCompleted()
{
  fitness = _intermediateFitness;
}

// the class factories
extern "C" Evaluate* create()
{
  Hexaboard *e = new Hexaboard();
  return (Evaluate*)e;
}

extern "C" void destroy(Evaluate*) {}
