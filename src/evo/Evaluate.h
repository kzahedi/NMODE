#include "base/RNN.h"
#include "base/Population.h"

#include <yars/cppClientCom/YarsClientCom.h>

# define FF_DISTANCE 3001

#include <sstream>

class Evaluate
{
  public:
    Evaluate();

    void run();

    void setFitnessFunction(int);

  private:
    void __evaluate(RNN*);

    Population*    _population;
    YarsClientCom* _com;
    double         _fitness;
    int            _fitnessFunction;
    int            _lifeTime;
    int            _nrOfActuators;
    int            _nrOfSensors;
    string         _options;
    string         _workingDirectory;
    string         _xml;
    vector<double> _actuatorValues;
    vector<double> _sensorValues;
    vector<double> _networkInput;
    stringstream   _message;
    bool           _successfulEvaluation;
};
