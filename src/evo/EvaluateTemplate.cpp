#include "EvaluateTemplate.h"
#include "base/RnnFromIndividual.h"
#include "base/Data.h"

#include <sstream>

EvaluateTemplate::EvaluateTemplate()
{
  _fitness              = 0.0;
  _fitnessFunction      = -1;
  _com                  = NULL;
  _nrOfSensors          = 0;
  _nrOfActuators        = 0;
  _lifeTime             = Data::instance()->specification()->evaluation()->lifeTime();
  _workingDirectory     = Data::instance()->specification()->simulator()->workingDirectory();
  _xml                  = Data::instance()->specification()->simulator()->xml();
  _options              = Data::instance()->specification()->simulator()->options();
  _population           = Population::instance();
  _successfulEvaluation = false;
}

void EvaluateTemplate::run()
{
  while(true)
  {
    Individual *i = _population->getNextIndividual();
    _rnn = RnnFromIndividual::create(i);
    __evaluate();
    i->setRawFitness(_fitness);

    double nc = EVA->nodeCost() * _rnn->nrOfNeurons();
    double ec = EVA->edgeCost() * _rnn->nrOfSynapses();

    i->setNodeCost(nc);
    i->setEdgeCost(ec);

    _fitness -= nc + ec;

    i->setFitness(_fitness);

    _population->evaluationCompleted();
  }
}

void EvaluateTemplate::__evaluate()
{
  _successfulEvaluation = false;
  while(_successfulEvaluation == false)
  {
    _lifeTime = Data::instance()->specification()->evaluation()->lifeTime();
    _fitness  = 0.0;
    try
    {
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

        updateController();

        _rnn->setInputs(_networkInput);
        _rnn->update();
        _rnn->getOutput(_actuatorValues);

        _message.str("");
        _message << "Fitness " << _fitness;

        updateFitnessFunction();

        if(i % 10 == 0)
        {
          _com->sendMessage(_message.str());
        }

        for(int j = 0; j < _nrOfActuators; j++)
        {
          _com->setActuatorValue(_actuatorValues[j], j);
        }
      }

      _com->sendReset();
      _successfulEvaluation = true;
    }
    catch(YarsClientComException &e)
    {
      _successfulEvaluation = false;
      stringstream sst;
      sst << _options << " " << _xml;
      _com->init(_workingDirectory, sst.str());
}
  }
}

void EvaluateTemplate::setFitnessFunction(int ff)
{
  _fitnessFunction = ff;
}

// void EvaluateTemplate::updateController()
// {
  // _networkInput[0] = 0.0;
  // _networkInput[1] = 0.0;

  // for(int j = 0; j < 3; j++)
  // {
    // _networkInput[0] += _sensorValues[j];
    // _networkInput[1] += _sensorValues[3 + j];
  // }

  // _networkInput[0] /= 3.0;
  // _networkInput[1] /= 3.0;
// }

// void EvaluateTemplate::updateFitnessFunction()
// {
  // _fitness += _sensorValues[6] + _sensorValues[7];
// }
