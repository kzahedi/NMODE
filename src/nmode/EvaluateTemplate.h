#include  <nmode/RNN.h>
#include  <nmode/Population.h>

#include <yars/cppClientCom/YarsClientCom.h>

#include <sstream>

class EvaluateTemplate
{
  public:
    EvaluateTemplate();

    void run();

    void quit();

    virtual void updateController()      = 0;
    virtual void updateFitnessFunction() = 0;
    virtual bool abort()                 = 0;
    virtual void newIndividual()         = 0;

  protected:
    double         _fitness;
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
