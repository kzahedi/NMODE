#include "Evaluate.h"
#include "base/RnnFromIndividual.h"
#include "base/Data.h"

#include <sstream>

Evaluate::Evaluate()
  : EvaluateTemplate()
{
  _networkInput.resize(2);
}


void Evaluate::updateController()
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

void Evaluate::updateFitnessFunction()
{
  _fitness += _sensorValues[6] + _sensorValues[7] - _networkInput[0] - _networkInput[1];
}
