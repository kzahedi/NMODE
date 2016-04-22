#ifndef __NMODE_EVALUATE_H__
#define __NMODE_EVALUATE_H__

#include <nmode/RNN.h>
#include <nmode/Population.h>

#include <yars/cppClientCom/YarsClientCom.h>

#include <sstream>

class Evaluate
{
  public:

    Evaluate();

    void run();
    void quit();
    void nogui();

    virtual void updateController()      = 0;
    virtual void updateFitnessFunction() = 0;
    virtual bool abort()                 = 0;
    virtual void newIndividual()         = 0;
    virtual void evaluationCompleted()   = 0;

  protected:

    double         fitness;
    int            nrOfActuators;
    int            nrOfSensors;
    int            lifeTime;
    int            t;
    vector<double> actuatorValues;
    vector<double> sensorValues;
    vector<double> networkInput;

  private:

    void           __evaluate();

    Population*    _population;
    YarsClientCom* _com;
    string         _options;
    string         _workingDirectory;
    string         _xml;
    stringstream   _message;
    bool           _successfulEvaluation;
    RNN*           _rnn;
    Individual*    _individual;

};

typedef Evaluate* create_e();

#endif // __EVALUATE_H__
