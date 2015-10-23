#include "RNN.h"

#include "macros.h"
#include "ENPException.h"

#include <math.h>

#include <glog/logging.h>

/***************************************************************************
 *                            Neuron functions                             *
 ***************************************************************************/

#define SIGM(x) (1.0 / (1.0 + exp(-x)))

Neuron::Neuron()
{
  _activity           = 0.0;
  _output             = 0.0;
  _bias               = 0.0;
}

Neuron::~Neuron()
{
  FORC(Synapses, s, _in) delete (*s);
  _in.clear();
}

void Neuron::updateActivity()
{
  _activity = _bias;
  FORC(Synapses, s, _in) _activity += (*s)->value();
}

void Neuron::updateOutput()
{
  switch(_transferfunction)
  {
    case NEURON_TRANSFER_FUNCTION_ID:
      _output = _activity;
      break;
    case NEURON_TRANSFER_FUNCTION_SIGM:
      _output = SIGM(_activity);
      break;
    case NEURON_TRANSFER_FUNCTION_TANH:
      _output = tanh(_activity);
      break;
    default:
      throw ENPException("Neuron::updateOutput: unknown transferfunction");
      break;
  }
}

double Neuron::output()
{
  return _output;
}

int Neuron::nrOfSynapses()
{
  return _in.size();
}

void Neuron::setBias(double value)
{
  _bias = value;
}

double Neuron::bias()
{
  return _bias;
}

void Neuron::setTransferfunction(int transferfunction) throw(ENPException)
{
  if(transferfunction != NEURON_TRANSFER_FUNCTION_ID &&
     transferfunction != NEURON_TRANSFER_FUNCTION_SIGM &&
     transferfunction != NEURON_TRANSFER_FUNCTION_TANH)
  {
    throw ENPException("Neuron::setTransferfunction: unknown transferfunction");
  }
  _transferfunction = transferfunction;
}

void Neuron::addSynapse(Synapse *s)
{
  _in.push_back(s);
}

int Neuron::transferfunction()
{
  return _transferfunction;
}

/***************************************************************************
 *                            Synapse functions                            *
 ***************************************************************************/


Synapse::Synapse() { }

double Synapse::value()
{
  return _weight * _src->output();
}

void Synapse::setSource(Neuron *s)
{
  _src = s;
}

void Synapse::setWeight(double w)
{
  _weight = w;
} 

/***************************************************************************
 *                              RNN Functions                              *
 ***************************************************************************/

RNN::RNN()
{
  // nothing
}

void RNN::update()
{
  FORC(Neurons, s, _sensors)   (*s)->updateActivity();
  FORC(Neurons, h, _hidden)    (*h)->updateActivity();
  FORC(Neurons, a, _actuators) (*a)->updateActivity();
  FORC(Neurons, n, _neurons)   (*n)->updateOutput();
}

void RNN::setInputs(vector<double>& inputs)
{
  // cout << ">>> start" << endl;
  for(int i = 0; i < (int)MIN(inputs.size(), _sensors.size()); i++)
  {
    _sensors[i]->setBias(inputs[i]);
    // cout << "sensor neuron " << i << " set to " << inputs[i] << " = " << _sensors[i]->bias() << endl;
  }
}

void RNN::getOutput(vector<double>& outputs)
{
  if(outputs.size() != _actuators.size())
  {
    outputs.resize(_actuators.size());
  }
  for(int i = 0; i < (int)_actuators.size(); i++)
  {
    outputs[i] = _actuators[i]->output();
  }
}

void RNN::addInputNeuron(Neuron *n)
{
  _sensors.push_back(n);
  _neurons.push_back(n);
}

void RNN::addOutputNeuron(Neuron *n)
{
  _actuators.push_back(n);
  _neurons.push_back(n);
}

void RNN::addHiddenNeuron(Neuron *n)
{
  _hidden.push_back(n);
  _neurons.push_back(n);
}

int RNN::nrOfNeurons()
{
  return _neurons.size();
}

int RNN::nrOfSensors()
{
  return _sensors.size();
}

int RNN::nrOfActuators()
{
  return _actuators.size();
}

int RNN::nrOfHidden()
{
  return _hidden.size();
}

Neuron* RNN::getSensorNeuron(int index)
{
  return _sensors[index];
}

Neuron* RNN::getActuatorNeuron(int index)
{
  return _actuators[index];
}

Neuron* RNN::getNeuron(int index)
{
  return _neurons[index];
}

Neuron* RNN::getHiddenNeuron(int index)
{
  return _hidden[index];
}

int RNN::nrOfSynapses()
{
  int s = 0;
  FORC(Neurons, n, _neurons) s += (*n)->nrOfSynapses();
  return s;
}

