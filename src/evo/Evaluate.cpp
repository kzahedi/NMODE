#include "Evaluate.h"
#include "base/RnnFromIndividual.h"

Evaluate::Evaluate(string workingDirectory, string options)
{
  _fitness          = 0.0;
  _fitnessFunction  = -1;
  _com              = NULL;
  _nrOfSensors      = 0;
  _nrOfActuators    = 0;
  _lifeTime         = 2000;
  _workingDirectory = workingDirectory;
  _options          = options;
  _pc               = NULL;
  _sensors.resize(2);
}

void Evaluate::setPopulationContainer(PopulationContainer *pc)
{
  _pc = pc;
}

void Evaluate::run()
{
  while(true)
  {
    Individual *i = _pc->getNextIndividual();
    RNN *rnn = RnnFromIndividual::create(i);
    __evaluate(rnn);
    i->setFitness(_fitness);
    cout << "1. evaluation done" << endl;
    _pc->evaluationCompleted();
    cout << "2. evaluation done" << endl;
  }
}

void Evaluate::__evaluate(RNN *rnn)
{
  if(_com == NULL)
  {
    _com = new YarsClientCom();
    _com->init(_workingDirectory, _options);
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
      // cout << "sensor value " << j << ": " << _sensorValues[j] << endl;
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
      // cout << "acutator value " << j << ": " << _actuatorValues[j] << endl;
    }
  }

  cout << "sending reset" << endl;
  _com->sendReset();
  cout << "done" << endl;
}

void Evaluate::setFitnessFunction(int ff)
{
  _fitnessFunction = ff;
}

