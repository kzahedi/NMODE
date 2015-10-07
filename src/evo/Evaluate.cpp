#include "Evaluate.h"


Evaluate::Evaluate()
{
  _fitness         = 0.0;
  _fitnessFunction = FF_DISTANCE;
  _com             = NULL;
  _nrOfSensors     = 0;
  _nrOfActuators   = 0;
}

double Evaluate::evaluate(RNN *rnn)
{
  if(_com == NULL)
  {
    _com = new YarsClientCom();
    _com->init();
    _nrOfSensors   = _com->numberOfSensors();
    _nrOfActuators = _com->numberOfJoints();
    _sensorValues.resize(_nrOfSensors);
    _actuatorValues.resize(_nrOfActuators);
  }

  for(int i = 0; i < _lifeTime; i++)
  {
    _com->update();

    for(int j = 0; j < _nrOfSensors; j++)
    {
      _com->getSensorValue(&_sensorValues[j], j);
    }

    rnn->setInputs(_sensorValues);
    rnn->update();
    rnn->setInputs(_actuatorValues);

    for(int j = 0; j < _nrOfActuators; j++)
    {
      _com->setJointValue(_actuatorValues[j], j);
    }
  }

  _com->reset();

  return 0.0;
}

void Evaluate::setFitnessFunction(int ff)
{
  _fitnessFunction = ff;
}

