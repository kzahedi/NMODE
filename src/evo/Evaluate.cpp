#include "Evaluate.h"


Evaluate::Evaluate()
{
  _fitness         = 0.0;
  _fitnessFunction = FF_DISTANCE;
  _com             = NULL;
  _nrOfSensors     = 0;
  _nrOfActuators   = 0;
  _lifeTime        = 2000;
  _sensors.resize(2);
}

double Evaluate::evaluate(RNN *rnn)
{
  if(_com == NULL)
  {
    _com = new YarsClientCom();
    _com->init();
    _nrOfSensors   = _com->numberOfSensors();
    _nrOfActuators = _com->numberOfActuators();
    _sensorValues.resize(_nrOfSensors);
    _actuatorValues.resize(_nrOfActuators);
  }

  for(int i = 0; i < _lifeTime; i++)
  {
    _com->update();

    for(int j = 0; j < _nrOfSensors; j++)
    {
      _com->getSensorValue(&_sensorValues[j], j);
      cout << "sensor value " << j << ": " << _sensorValues[j] << endl;
    }

    _sensors[0] = 0.0;
    _sensors[1] = 0.0;
    for(int j = 0; j < 3; j++)
    {
      _sensors[0] += _sensorValues[j];
      _sensors[1] += _sensorValues[3 + j];
    }

    _sensors[0] /= 3.0;
    _sensors[1] /= 3.0;

    rnn->setInputs(_sensors);
    rnn->update();
    rnn->getOutput(_actuatorValues);

    for(int j = 0; j < _nrOfActuators; j++)
    {
      _com->setActuatorValue(_actuatorValues[j], j);
      cout << "acutator value " << j << ": " << _actuatorValues[j] << endl;
    }
  }

  _com->reset();

  return 0.0;
}

void Evaluate::setFitnessFunction(int ff)
{
  _fitnessFunction = ff;
}

