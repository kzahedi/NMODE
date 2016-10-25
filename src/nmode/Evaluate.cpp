#include <nmode/Evaluate.h>
#include <nmode/RnnFromIndividual.h>
#include <nmode/Data.h>
#include <nmode/Timer.h>

#include <ctime>

#include <sstream>

Evaluate::Evaluate()
{
  fitness               = 0.0;
  _com                  = NULL;
  nrOfSensors           = 0;
  nrOfActuators         = 0;
  lifeTime              = Data::instance()->specification()->evaluation()->lifeTime();
  _workingDirectory     = Data::instance()->specification()->simulator()->workingDirectory();
  _xml                  = Data::instance()->specification()->simulator()->xml();
  _options              = Data::instance()->specification()->simulator()->options();
  _population           = Population::instance();
  _successfulEvaluation = false;
}

void Evaluate::nogui()
{
  stringstream sst;
  sst << _options << " --nogui";
  _options = sst.str();
}

void Evaluate::run()
{
  while(true)
  {
    _individual = _population->getNextIndividual();
    _rnn = RnnFromIndividual::create(_individual);
    unsigned long begin = Timer::getTime();
    __evaluate();
    unsigned long end = Timer::getTime();
    double elapsed_secs = double(end - begin) / 1000.0;
    _individual->setRawFitness(fitness);
    cout << "Individual " << _individual->nr() << " / "
      <<  _population->i_size() << ": " << fitness << " " << elapsed_secs << "s" << endl;

    double nc = EVA->nodeCost() * _rnn->nrOfNeurons();
    double ec = EVA->edgeCost() * _rnn->nrOfSynapses();

    _individual->setNodeCost(nc);
    _individual->setEdgeCost(ec);
    _individual->setNrOfSynapses(_rnn->nrOfSynapses());
    _individual->setNrOfNeurons(_rnn->nrOfHidden());

    fitness -= nc + ec;

    _individual->setFitness(fitness);

    _population->evaluationCompleted();

    delete _rnn;
  }
}

void Evaluate::__evaluate()
{
  _successfulEvaluation = false;
  int n = _individual->nr();
  int s = _population->i_size();
  while(_successfulEvaluation == false)
  {
    lifeTime = Data::instance()->specification()->evaluation()->lifeTime();
    fitness  = 0.0;
    try
    {
      if(_com == NULL)
      {
        _com = new YarsClientCom();
        _com->throwException(true);
        stringstream sst;
        sst << _options << " " << _xml;
        _com->init(_workingDirectory, sst.str());
        nrOfSensors   = _com->numberOfSensorsValues();
        nrOfActuators = _com->numberOfActuatorsValues();
        cout << "nr of sensors:   " << nrOfSensors << endl;
        cout << "nr of actuators: " << nrOfActuators << endl;
        _com->printSensorMotorConfiguration();
        sensorValues.resize(nrOfSensors);
        actuatorValues.resize(nrOfActuators);
      }

      newIndividual();

      for(int i = 0; i < lifeTime; i++)
      {
        t = i;
        _com->update();

        for(int j = 0; j < nrOfSensors; j++)
        {
          sensorValues[j] = _com->getSensorValue(j);
        }

        if(abort())
        {
          evaluationCompleted();
          _com->sendReset();
          _successfulEvaluation = true;
          return;
        }


        updateController();


        _rnn->setInputs(networkInput);
        _rnn->update();
        _rnn->getOutput(actuatorValues);

        _message.str("");
        _message << "Generation " << _population->generation() << "\n";
        _message << "Individual " << n << " / " << s << "\n";
        _message << "Fitness " << fitness;

        updateFitnessFunction();

        if(i % 10 == 0)
        {
          _com->sendMessage(_message.str());
        }

        for(int j = 0; j < nrOfActuators; j++)
        {
          _com->setActuatorValue(j, actuatorValues[j]);
        }
      }

      evaluationCompleted();
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
