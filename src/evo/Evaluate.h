#include "base/RNN.h"

#include <yars/cppClientCom/YarsClientCom.h>

# define FF_DISTANCE 3001

class Evaluate
{
  public:
    Evaluate();

    double evaluate(RNN*);
    void   setFitnessFunction(int);

  private:

    double         _fitness;
    int            _fitnessFunction;
    int            _nrOfSensors;
    int            _nrOfActuators;
    int            _lifeTime;
    YarsClientCom *_com;
    
    vector<double> _sensorValues;
    vector<double> _actuatorValues;

};
