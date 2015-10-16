#include "Evaluate.h"
#include "base/RnnFromIndividual.h"
#include "base/Data.h"

#include <sstream>

Evaluate::Evaluate()
{
  _fitness          = 0.0;
  _fitnessFunction  = -1;
  _com              = NULL;
  _nrOfSensors      = 0;
  _nrOfActuators    = 0;
  _lifeTime         = Data::instance()->specification()->evaluation()->lifeTime();
  _workingDirectory = Data::instance()->specification()->simulator()->workingDirectory();
  _xml              = Data::instance()->specification()->simulator()->xml();
  _options          = Data::instance()->specification()->simulator()->options();
  _population       = Population::instance();
  _networkInput.resize(2);
}

void Evaluate::run()
{
  while(true)
  {
    Individual *i = _population->getNextIndividual();
    RNN *rnn = RnnFromIndividual::create(i);
    __evaluate(rnn);
    i->setRawFitness(_fitness);

    double nc = EVA->nodeCost() * rnn->nrOfNeurons();
    double ec = EVA->edgeCost() * rnn->nrOfSynapses();

    i->setNodeCost(nc);
    i->setEdgeCost(ec);

    _fitness -= nc + ec;

    i->setFitness(_fitness);

    _population->evaluationCompleted();
  }
}

void Evaluate::__evaluate(RNN *rnn)
{
  _lifeTime = Data::instance()->specification()->evaluation()->lifeTime();
  _fitness  = 0.0;

  if(_com == NULL)
  {
    _com = new YarsClientCom();
    stringstream sst;
    sst << _options << " " << _xml;
    _com->init(_workingDirectory, sst.str());
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
    }

    _networkInput[0] = 0.0;
    _networkInput[1] = 0.0;

    for(int j = 0; j < 3; j++)
    {
      _networkInput[0] += _sensorValues[j];
      _networkInput[1] += _sensorValues[3 + j];
    }

    _networkInput[0] /= 3.0;
    _networkInput[1] /= 3.0;

    rnn->setInputs(_networkInput);
    rnn->update();
    rnn->getOutput(_actuatorValues);

    _fitness += _sensorValues[6] + _sensorValues[7];
    _message.str("");
    _message << "Fitness " << _fitness;
    if(i % 100 == 0)
    {
      _com->sendMessage(_message.str());
    }

    for(int j = 0; j < _nrOfActuators; j++)
    {
      _com->setActuatorValue(_actuatorValues[j], j);
    }
  }

  _com->sendReset();
}

void Evaluate::setFitnessFunction(int ff)
{
  _fitnessFunction = ff;
}
