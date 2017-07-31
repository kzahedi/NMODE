#include <nmode/OpenAICom.h>
#include <nmode/Data.h>

#include <unistd.h>

void* read_stdout(void* ydf)
{
  char buf[1];
  FILE* yarsFD = (FILE*)ydf;
  stringstream sst;
  while(feof(yarsFD) == 0)
  {
    fread(buf, 1, 1, yarsFD);
    sst << buf[0];
    if(buf[0] == '\n')
    {
      cout << sst.str();
      sst.str("");
    }
  }
  cout << sst.str();
  return NULL;
}


OpenAICom::OpenAICom()
{
  _reward = 0.0;
}

void OpenAICom::throwException(bool  b)
{
}

int OpenAICom::numberOfSensorsValues()
{
  return _nrOfSensorValues;
}

int OpenAICom::numberOfActuatorsValues()
{
  return _nrOfActuatorValues;
}

void OpenAICom::printSensorMotorConfiguration()
{
}

void OpenAICom::update()
{
  _socket << "ACTUATORS";
  _socket << _actuatorValues;
  _socket << "SENSORS";
  _socket >> _sensorValues;
  _socket << "REWARD";
  _socket >> _reward;
}

double OpenAICom::getSensorValue(int index)
{
  return _sensorValues[index];
}

void OpenAICom::sendReset()
{
  _socket << "RESET";
}

void OpenAICom::sendMessage(string msg)
{
}

void OpenAICom::setActuatorValue(int index, double value)
{
  _actuatorValues[index] = value;
}

void OpenAICom::sendQuit()
{
  _socket << "QUIT";
}

void OpenAICom::init(string workingDirectory, string experimentName, string path)
{
  chdir(workingDirectory.c_str());

  string token;
  int l = 0;
  char buf[1];
  bool lookForPort = false;
  int port = -1;
  string pstring = "port";
  stringstream sts;

  _experimentName = experimentName;
  stringstream sst;
  // sst << path << "openai";
  sst << path << "openai.py";
#if __APPLE__
  if((_openAIFD = popen(sst.str().c_str(), "r")) == NULL)
#else // __APPLE__
  if((_openAIFD = popen(sst.str().c_str(), "r")) == NULL)
#endif // __APPLE__
  {
    cout << "Cannot open \"" << sst.str() << "\"" << endl;
    cout << "Error Nr.: " << strerror(errno) << endl;
    exit(-1);
  }
  sst.str("");
  while(feof(_openAIFD) == 0)
  {
    // fread(buf, 1, 1, _openAIFD);
    buf[0] = fgetc(_openAIFD);
    sts << buf[0];
    if(buf[0] == '\n')
    {
      cout << sts.str();
      sts.str("");
    }

    if(buf[0] != ' ' || buf[0] == '\n')
    {
      sst << buf[0];
    }
    else
    {
      cout << sst.str() << endl;
      if(lookForPort)
      {
        string token = sst.str();
        sst.str("");
        port = atoi(token.c_str());
        cout << endl << ">>> found port: " << port << endl;
        break;
      }
      else
      {
        string token = sst.str();
        sst.str("");
        if(token == "port")
        {
          lookForPort = true;
        }
      }
    }
    if(buf[0] == 0)
    {
      break;
    }
  }

  init("localhost", port);

  pthread_create(&_thread, NULL, read_stdout, (void*)_openAIFD);
}

void OpenAICom::init(const string host, const int port)
{
  _socket.connect(host, port);
  // _socket << "HalfCheetah-v1";
  _socket << _experimentName;
  _socket >> _nrOfSensorValues ;
  _nrOfActuatorValues = _nrOfSensorValues;
  _sensorValues.resize(_nrOfSensorValues);
  _actuatorValues.resize(_nrOfActuatorValues);
  // cout << "Nr. of sensor values: " << _nrOfSensorValues << endl;
}

double OpenAICom::reward()
{
  return _reward;
}
