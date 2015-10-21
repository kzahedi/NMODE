#include "Evaluate.h"
#include "enp/RnnFromIndividual.h"
#include "enp/Data.h"

#include <sstream>

Evaluate::Evaluate()
  : EvaluateTemplate()
{
  _networkInput.resize(30);

  _x     = 0.0;
  _y     = 0.0;
  _lastX = 0.0;
  _lastY = 0.0;
}


void Evaluate::updateController()
{
  for(int i = 0; i < (int)_networkInput.size(); i++)
  {
    _networkInput[i] = _sensorValues[i];
  }
  // cout << "input:";
  // for(int i = 0; i < (int)_networkInput.size(); i++)
  // {
    // cout << " " << _networkInput[i];
  // }
  // cout << endl;
}

void Evaluate::updateFitnessFunction()
{
  // cout << _sensorValues.size() << endl;
  _x = _sensorValues[31];
  _y = _sensorValues[32];

  _dist =  sqrt(_x * _x + _y * _y);

  // cout << "output:";
  // for(int i = 0; i < (int)_actuatorValues.size(); i++)
  // {
    // cout << " " << _actuatorValues[i];
  // }
  // cout << endl;

  _fitness += _dist;

}
