#include  <nmode/EvaluateTemplate.h>
#include  <nmode/RnnFromIndividual.h>
#include  <nmode/Data.h>

#include <sstream>

EvaluateTemplate::EvaluateTemplate()
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

void EvaluateTemplate::run()
{
  while(true)
  {
    cout << "hier 0" << endl;
    Individual *i = _population->getNextIndividual();
    cout << "hier 1" << endl;
    _rnn = RnnFromIndividual::create(i);
    cout << "hier 2" << endl;
    __evaluate();
    cout << "hier 3" << endl;
    i->setRawFitness(_fitness);
    cout << "hier 4" << endl;

    double nc = EVA->nodeCost() * _rnn->nrOfNeurons();
    cout << "hier 5" << endl;
    double ec = EVA->edgeCost() * _rnn->nrOfSynapses();
    cout << "hier 6" << endl;

    i->setNodeCost(nc);
    cout << "hier 7" << endl;
    i->setEdgeCost(ec);
    cout << "hier 8" << endl;
    i->setNrOfSynapses(_rnn->nrOfSynapses());
    cout << "hier 9" << endl;
    i->setNrOfNeurons(_rnn->nrOfHidden());
    cout << "hier 10" << endl;

    _fitness -= nc + ec;
    cout << "hier 11" << endl;

    i->setFitness(_fitness);
    cout << "hier 12" << endl;

    _population->evaluationCompleted();
    cout << "hier 13" << endl;

    delete _rnn;
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

void EvaluateTemplate::quit()
{
  _com->sendQuit();
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
