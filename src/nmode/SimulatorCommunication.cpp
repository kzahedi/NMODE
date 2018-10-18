#include <nmode/SimulatorCommunication.h>

#include <nmode/Data.h>

# define IS_YARS   if(_simulator == USE_YARS)
# define IS_OPENAI if(_simulator == USE_OPENAI)
# define USE_YARS   1000
# define USE_OPENAI 1001
# define USE_NONE   1002

SimulatorCommunication::SimulatorCommunication()
{
  _simulator = -1;
  if(Data::instance()->specification()->simulator()->env() == "YARS")   _simulator = USE_YARS;
  if(Data::instance()->specification()->simulator()->env() == "OpenAI") _simulator = USE_OPENAI;
  if(Data::instance()->specification()->simulator()->env() == "none")   _simulator = USE_NONE;
  if(_simulator == -1)
  {
    cerr << "unknown environment given: " << Data::instance()->specification()->simulator()->env() << endl;
    exit(-1);
  }

  IS_YARS   _yars   = new YarsClientCom();
  IS_OPENAI _openai = new OpenAICom();

}

void SimulatorCommunication::throwException(bool b)
{
  IS_YARS _yars->throwException(b);
}

void SimulatorCommunication::init(string wd, string opt, string path)
{
  _wd = wd;
  _opt = opt;
  _path = path;
  IS_YARS   _yars->init(wd,   opt, path);
  IS_OPENAI _openai->init(wd, opt, path);
}

int SimulatorCommunication::numberOfSensorsValues()
{
  IS_YARS   return _yars->numberOfSensorsValues();
  IS_OPENAI return _openai->numberOfSensorsValues();
  return -1;
}

int SimulatorCommunication::numberOfActuatorsValues()
{
  IS_YARS   return _yars->numberOfActuatorsValues();
  IS_OPENAI return _openai->numberOfActuatorsValues();
  return -1;
}

void SimulatorCommunication::printSensorMotorConfiguration()
{
  IS_YARS _yars->printSensorMotorConfiguration();
}

void SimulatorCommunication::update()
{
  IS_YARS   _yars->update();
  IS_OPENAI _openai->update();
}

double SimulatorCommunication::getSensorValue(int index)
{
  IS_YARS   return _yars->getSensorValue(index);
  IS_OPENAI return _openai->getSensorValue(index);
  return -1.0;
}

void SimulatorCommunication::sendReset()
{
  // IS_YARS   _yars->sendReset(); // reset current not working
  IS_YARS
  {
    _yars->sendQuit();
    _yars->init(_wd, _opt, _path);
  }
  IS_OPENAI _openai->sendReset();
}

void SimulatorCommunication::sendMessage(string msg)
{
  IS_YARS   _yars->sendMessage(msg);
  IS_OPENAI _openai->sendMessage(msg);
}

void SimulatorCommunication::setActuatorValue(int index, double value)
{
  IS_YARS   _yars->setActuatorValue(index, value);
  IS_OPENAI _openai->setActuatorValue(index, value);
}

void SimulatorCommunication::sendQuit()
{
  IS_YARS   _yars->sendQuit();
  IS_OPENAI _openai->sendQuit();
}

double SimulatorCommunication::reward()
{
  IS_YARS   return 0.0;
  IS_OPENAI return _openai->reward();
  return 0.0;
}

