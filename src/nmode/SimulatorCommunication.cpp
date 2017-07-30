#include <nmode/SimulatorCommunication.h>

#include <nmode/Data.h>

# define IS_YARS if(_simulator == USE_YARS)
# define ELSE_OPENAI if(_simulator == USE_OPENAI)
# define USE_YARS   1000
# define USE_OPENAI 1001

SimulatorCommunication::SimulatorCommunication()
{
  _simulator = -1;
  if(Data::instance()->specification()->simulator()->env() == "YARS")   _simulator = USE_YARS;
  if(Data::instance()->specification()->simulator()->env() == "OpenAI") _simulator = USE_OPENAI;

  IS_YARS
    _yars = new YarsClientCom();
  ELSE_OPENAI
    _openai = new OpenAI();

}

void SimulatorCommunication::throwException(bool b)
{
  IS_YARS
    _yars->throwException(b);
}

void SimulatorCommunication::init(string wd, string opt, string path)
{
  IS_YARS
    _yars->init(wd, opt, path);
  ELSE_OPENAI
    _openai->init(wd, opt, path);
}

int SimulatorCommunication::numberOfSensorsValues()
{
  IS_YARS
    return _yars->numberOfSensorsValues();
  return -1;
}

int SimulatorCommunication::numberOfActuatorsValues()
{
  IS_YARS
    return _yars->numberOfActuatorsValues();
  return -1;
}

void SimulatorCommunication::printSensorMotorConfiguration()
{
  IS_YARS
    _yars->printSensorMotorConfiguration();
}

void SimulatorCommunication::update()
{
  IS_YARS
    _yars->update();
}

double SimulatorCommunication::getSensorValue(int index)
{
  IS_YARS
    return _yars->getSensorValue(index);
  return 0.0;
}

void SimulatorCommunication::sendReset()
{
  IS_YARS
    _yars->sendReset();
}

void SimulatorCommunication::sendMessage(string msg)
{
  IS_YARS
    _yars->sendMessage(msg);
}

void SimulatorCommunication::setActuatorValue(int index, double value)
{
  IS_YARS
    _yars->setActuatorValue(index, value);
}

void SimulatorCommunication::sendQuit()
{
  IS_YARS
    _yars->sendQuit();
}

