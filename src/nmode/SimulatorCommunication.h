#ifndef __SIMULATOR_COMMUNITCATION_H__
#define __SIMULATOR_COMMUNITCATION_H__

#include <yars/cppClientCom/YarsClientCom.h>
#include <nmode/OpenAI.h>

#include <string>

using namespace std;

class SimulatorCommunication
{
  public:
    SimulatorCommunication();

    void throwException(bool b);
    void init(string wd, string opt, string path);
    int  numberOfSensorsValues();
    int  numberOfActuatorsValues();
    void printSensorMotorConfiguration();
    void update();
    double getSensorValue(int index);
    void sendReset();
    void sendMessage(string msg);
    void setActuatorValue(int index, double value);
    void sendQuit();

  private:
    int            _simulator;
    YarsClientCom* _yars;
    OpenAI*        _openai;
};



#endif // __SIMULATOR_COMMUNITCATION_H__