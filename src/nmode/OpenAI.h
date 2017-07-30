#ifndef __OPEN_AI_H__
#define __OPEN_AI_H__

#include <nmode/Com.h>

#include <string>
#include <iostream>
#include <sstream>
#include <pthread.h>

using namespace std;

class OpenAI
{
  public:
    OpenAI();

    void   throwException(bool  b);
    void   init(const string host, const int port);
    void   init(string workingDirectory, string experimentName, string path);
    int    numberOfSensorsValues();
    int    numberOfActuatorsValues();
    void   printSensorMotorConfiguration();
    void   update();
    double getSensorValue(int index);
    void   sendReset();
    void   sendMessage(string   msg);
    void   setActuatorValue(int index, double value);
    void   sendQuit();

  private:

    FILE*               _openAIFD;
    pthread_t           _thread;
    Com                 _socket;
    std::vector<double> _actuatorValues;
    std::vector<double> _sensorValues;
    string              _name;
    string              _options;
    string              _experimentName;
    string              _workingDirectory;
    int                 _nrOfSensorValues;
    int                 _nrOfActuatorValues;
    double              _reward;

};

#endif // __OPEN_AI_H__
