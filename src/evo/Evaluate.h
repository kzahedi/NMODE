#include "base/RNN.h"
#include "base/PopulationContainer.h"

#include <yars/cppClientCom/YarsClientCom.h>

# define FF_DISTANCE 3001

class Evaluate
{
  public:
    Evaluate();

    void setPopulationContainer(PopulationContainer *p);

    void run();

    void setFitnessFunction(int);

  private:
    void __evaluate(RNN*);

    PopulationContainer* _pc;
    YarsClientCom*       _com;
    double               _fitness;
    int                  _fitnessFunction;
    int                  _lifeTime;
    int                  _nrOfActuators;
    int                  _nrOfSensors;
    string               _options;
    string               _workingDirectory;
    string               _xml;
    vector<double>       _actuatorValues;
    vector<double>       _sensorValues;
    vector<double>       _networkInput;
};
