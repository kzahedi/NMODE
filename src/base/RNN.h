#ifndef __RNN_H__
#define __RNN_H__

#include "base/P3D.h"
#include "base/ENPException.h"

#include <vector>

using namespace std;

class Synapse;

#define NEURON_TRANSFER_FUNCTION_TANH 1
#define NEURON_TRANSFER_FUNCTION_SIGM 2
#define NEURON_TRANSFER_FUNCTION_ID   3

class Neuron
{
  public:
    Neuron();
    ~Neuron();

    //Neuron(const Neuron);
    //Neuron operator=(const Neuron);

    void updateActivity();
    void updateOutput();

    void addSynapse(Synapse *s);

    void setBias(double bias);
    void setTransferfunction(int transferfunction) throw(ENPException);

    double bias();
    double output();

  private:
    double           _activity;
    double           _output;
    double           _bias;
    int              _type;
    int              _transferfunction;
    P3D              _position;
    vector<Synapse*> _in;
};

class Synapse
{
  public:
    Synapse();
    // ~Synapse();

    //Synapse(const Synapse);
    //Synapse operator=(const Synapse);

    void setSource(Neuron *n);
    void setWeight(double w);

    double value();

  private:
    Neuron *_src;
    // Neuron *_dst;
    double _weight;
};

typedef vector<Neuron*>  Neurons;
typedef vector<Synapse*> Synapses;

class RNN
{
  public:
    RNN();
    // ~rnn();

    //rnn(const rnn);
    //rnn operator=(const rnn);

    void addNeuron(Neuron *n);
    void update();
  private:

    Neurons _neurons;
};

#endif // __RNN_H__
