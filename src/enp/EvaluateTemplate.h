#include "RNN.h"
#include "Population.h"

#include <yars/cppClientCom/YarsClientCom.h>

# define FF_DISTANCE 3001

#include <sstream>

class EvaluateTemplate
{
  public:
    EvaluateTemplate();

    void run();

    void setFitnessFunction(int);
    virtual void updateController()      = 0;
    virtual void updateFitnessFunction() = 0;

  protected:
    double         _fitness;
    int            _fitnessFunction;
    int            _nrOfActuators;
    int            _nrOfSensors;
    vector<double> _actuatorValues;
    vector<double> _sensorValues;
    vector<double> _networkInput;

  private:
    void __evaluate();

    Population*    _population;
    YarsClientCom* _com;
    int            _lifeTime;
    string         _options;
    string         _workingDirectory;
    string         _xml;
    stringstream   _message;
    bool           _successfulEvaluation;
    RNN*           _rnn;

};
