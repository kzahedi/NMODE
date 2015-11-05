#include "Evaluate.h"
#include "RnnFromIndividual.h"
#include "Data.h"

#include <sstream>

Evaluate::Evaluate()
{
  _fitness              = 0.0;
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

void Evaluate::run()
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
    i->setNrOfSynapses(_rnn->nrOfSynapses());
    i->setNrOfNeurons(_rnn->nrOfHidden());

    _fitness -= nc + ec;

    i->setFitness(_fitness);

    _population->evaluationCompleted();

    delete _rnn;
  }
}

void Evaluate::__evaluate()
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
        _com->throwException(true);
        stringstream sst;
        sst << _options << " " << _xml;
        _com->init(_workingDirectory, sst.str());
        _nrOfSensors   = _com->numberOfSensorsValues();
        _nrOfActuators = _com->numberOfActuatorsValues();
        cout << "Number of sensors: " << _nrOfSensors << endl;
        _sensorValues.resize(_nrOfSensors);
        _actuatorValues.resize(_nrOfActuators);
      }

      newIndividual();

      for(int i = 0; i < _lifeTime; i++)
      {
        _com->update();

        for(int j = 0; j < _nrOfSensors; j++)
        {
          _sensorValues[j] = _com->getSensorValue(j);
        }

        if(abort())
        {
          _com->sendReset();
          _successfulEvaluation = true;
          return;
        }


        updateController();


        _rnn->setInputs(_networkInput);
        _rnn->update();
        _rnn->getOutput(_actuatorValues);

        _message.str("");
        _message << "Generation " << _population->generation() << "\n";
        _message << "Fitness " << _fitness;

        updateFitnessFunction();

        if(i % 10 == 0)
        {
          _com->sendMessage(_message.str());
        }

        for(int j = 0; j < _nrOfActuators; j++)
        {
          _com->setActuatorValue(j, _actuatorValues[j]);
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

void Evaluate::quit()
{
  _com->sendQuit();
}
