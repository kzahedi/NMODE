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
  _path                 = Data::instance()->specification()->simulator()->path();
  _options              = Data::instance()->specification()->simulator()->options();
  _population           = Population::instance();
  _successfulEvaluation = false;
  _useCapture           = false;
  _printConfiguration   = false;

  // cout << "Options: " << _options << endl << "XML: " << _xml << endl << "PATH: " << _path << endl;
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
    _individual         = _population->getNextIndividual();
    _rnn                = RnnFromIndividual::create(_individual);
    unsigned long begin = Timer::getTime();
    logging.str("");
    __evaluate();
    unsigned long end   = Timer::getTime();
    double elapsed_secs = double(end - begin) / 1000.0;
    _individual->setRawFitness(fitness);
    cout.precision(8);
    cout.unsetf(ios_base::floatfield);
    cout << "Individual " << _individual->nr() << " / "
      <<  _population->i_size() << ": "
      << fitness;

    if(logging.str().size() > 0)
    {
      cout << " (" << logging.str() << ") ";
    }

    double nc = EVA->nodeCost() * _rnn->nrOfNeurons();
    double ec = EVA->edgeCost() * _rnn->nrOfSynapses();

    _individual->setNodeCost(nc);
    _individual->setEdgeCost(ec);
    _individual->setNrOfSynapses(_rnn->nrOfSynapses());
    _individual->setNrOfNeurons(_rnn->nrOfHidden());

    if(EVA->nodeCost() > 0.0 || EVA->edgeCost() > 0.0)
    {
      fitness -= nc + ec;
      cout << " -> " << fitness;
    }
    cout << " " << elapsed_secs << "s" << endl;

    _individual->setFitness(fitness);

    _population->evaluationCompleted();

    delete _rnn;
  }
}

void Evaluate::runOne(Individual *individual)
{
  _individual = individual;
  // cout << "evaluating " << _individual->id() << endl;
  _rnn        = RnnFromIndividual::create(individual);
  __evaluate();
  delete _rnn;
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
        sst << _options << " ";
        if(_useCapture)
        {
          sst << " --capture ";
        }
        sst << _xml;
        // cout << _path << "yars " << sst.str() << endl;
        _com->init(_workingDirectory, sst.str(), _path);
        nrOfSensors   = _com->numberOfSensorsValues();
        nrOfActuators = _com->numberOfActuatorsValues();
        // cout << "nr of sensors:   " << nrOfSensors << endl;
        // cout << "nr of actuators: " << nrOfActuators << endl;
        if(_printConfiguration)
        {
          _com->printSensorMotorConfiguration();
        }
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
        _message.unsetf(ios_base::floatfield);
        _message << "Generation " << _population->generation() << "\n";
        if(s > 1)
        {
          _message << "Individual " << n << " / " << s << "\n";
        }
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
      _com->init(_workingDirectory, sst.str(), _path);
    }
  }
}

void Evaluate::quit()
{
  _com->sendQuit();
}

void Evaluate::setUseCapture(bool uc)
{
  _useCapture = uc;
}

void Evaluate::printConfiguration(bool pc)
{
  _printConfiguration = pc;
}
