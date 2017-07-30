#include <nmode/OpenAI.h>
#include <nmode/Data.h>

#include <unistd.h>

void* read_stdout(void* ydf)
{
  cout << "hier 0" << endl;
  char buf[1];
  FILE* yarsFD = (FILE*)ydf;
  stringstream sst;
  while(feof(yarsFD) == 0)
  {
    fread(buf, 1, 1, yarsFD);
    sst << buf[0];
    cout << sst.str() << endl;
    if(buf[0] == '\n')
    {
      cout << sst.str();
      sst.str("");
    }
  }
  cout << sst.str();
  return NULL;
}


OpenAI::OpenAI()
{
}

void OpenAI::throwException(bool  b)
{
}

int OpenAI::numberOfSensorsValues()
{
  return 0;
}

int OpenAI::numberOfActuatorsValues()
{
  return 0;
}

void OpenAI::printSensorMotorConfiguration()
{
}

void OpenAI::update()
{
}

double OpenAI::getSensorValue(int index)
{
  return 0.0;
}

void OpenAI::sendReset()
{
}

void OpenAI::sendMessage(string msg)
{
}

void OpenAI::setActuatorValue(int index, double value)
{
}

void OpenAI::sendQuit()
{
}

void OpenAI::init(string workingDirectory, string experimentName, string path)
{
  // cout << "chaining to working directory: " << workingDirectory << endl;
  chdir(workingDirectory.c_str());

  string token;
  int l = 0;
  char buf[1];
  bool lookForPort = false;
  int port = -1;
  string pstring = "port";
  stringstream sts;
  cout << "hier hier 3" << endl;

  stringstream sst;
  // sst << path << "openai";
  sst << path << "openai.py";
  cout << sst.str() << endl;
#if __APPLE__
  cout << "hier hier 0" << endl;
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
  cout << "hier hier 4" << endl;
    // fread(buf, 1, 1, _openAIFD);
    buf[0] = fgetc(_openAIFD);
  cout << "hier hier 5" << endl;
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

void OpenAI::init(const string host, const int port)
{
}
