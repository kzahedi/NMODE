#ifndef __NMODE_EVALUATE_H__
#define __NMODE_EVALUATE_H__

#include <nmode/RNN.h>
#include <nmode/Population.h>
#include <nmode/SimulatorCommunication.h>

#include <yars/cppClientCom/YarsClientCom.h>

#include <sstream>

class Evaluate
{
  public:

    Evaluate();

    void run();
    void runOne(Individual*);
    void quit();
    void nogui();
    void setUseCapture(bool uc);

    void printConfiguration(bool pc);

    virtual void updateController()      = 0;
    virtual void updateFitnessFunction() = 0;
    virtual bool abort()                 = 0;
    virtual void newIndividual()         = 0;
    virtual void evaluationCompleted()   = 0;

  protected:

    double         fitness;
    vector<double> fitnessComponents;
    vector<string> fitnessComponentNames;
    int            nrOfActuators;
    int            nrOfSensors;
    int            lifeTime;
    int            t;
    vector<double> actuatorValues;
    vector<double> sensorValues;
    vector<double> networkInput;
    stringstream   logging;

  private:

    void           __evaluate();

    Population*    _population;
    // YarsClientCom* _com;
    SimulatorCommunication* _com;
    string         _options;
    string         _workingDirectory;
    string         _xml;
    string         _path;
    stringstream   _message;
    bool           _successfulEvaluation;
    RNN*           _rnn;
    Individual*    _individual;
    bool           _useCapture;
    bool           _printConfiguration;
};

typedef Evaluate* create_e();

#endif // __EVALUATE_H__
