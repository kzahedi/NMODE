#include "rnn_test.h"

#include <nmode/RNN.h>
#include <nmode/NMODEException.h>

#include <iostream>

using namespace std;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( rnnTest );


void rnnTest::testNeuronWithoutSynapses()
{
  Neuron *n = new Neuron();

  CPPUNIT_ASSERT_THROW(n->setTransferfunction(12), NMODEException);

  n->setTransferfunction(NEURON_TRANSFER_FUNCTION_TANH);

  for(double i = -100.0; i <=100.0; i = i + 1.0)
  {
    n->setBias(i/100.0);
    n->updateActivity();
    n->updateOutput();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(tanh(i/100.0), n->output(), 0.000001);
  }

  n->setTransferfunction(NEURON_TRANSFER_FUNCTION_SIGM);

  for(double i = -100.0; i <=100.0; i = i + 1.0)
  {
    n->setBias(i/100.0);
    n->updateActivity();
    n->updateOutput();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0 / (1.0 + exp(-i/100.0)), n->output(), 0.000001);
  }

  n->setTransferfunction(NEURON_TRANSFER_FUNCTION_ID);

  for(double i = -100.0; i <=100.0; i = i + 1.0)
  {
    n->setBias(i/100.0);
    n->updateActivity();
    n->updateOutput();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(i/100.0, n->output(), 0.000001);
  }

  delete n;
}

void rnnTest::testSynapse()
{
  Neuron *n = new Neuron();

  n->setTransferfunction(NEURON_TRANSFER_FUNCTION_ID);
  n->setBias(2.0);
  n->updateActivity();
  n->updateOutput();

  Synapse *s = new Synapse();
  s->setSource(n);
  s->setWeight(2.0);
  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(4.0, s->value(), 0.000001);

  delete s;
}

void rnnTest::testNeuronWithSynapses()
{
  Neuron *src = new Neuron();
  Neuron *dst = new Neuron();

  src->setBias(2.0);

  src->setTransferfunction(NEURON_TRANSFER_FUNCTION_ID);
  dst->setTransferfunction(NEURON_TRANSFER_FUNCTION_ID);
  
  Synapse *s = new Synapse();
  s->setSource(src);
  s->setWeight(1.23);

  dst->addSynapse(s);

  src->updateActivity();
  src->updateOutput();
  dst->updateActivity();
  dst->updateOutput();

  CPPUNIT_ASSERT_DOUBLES_EQUAL(dst->output(), 2.46, 0.000001);

  delete src;
  delete dst;
}

void rnnTest::testRNNUpdate()
{
  // Neuron *src = new Neuron();
  // Neuron *dst = new Neuron();

  // src->setBias(2.0);

  // src->setTransferfunction(NEURON_TRANSFER_FUNCTION_ID);
  // dst->setTransferfunction(NEURON_TRANSFER_FUNCTION_ID);
  
  // Synapse *s = new Synapse();
  // s->setSource(src);
  // s->setWeight(1.23);

  // dst->addSynapse(s);

  // RNN *rnn = new RNN();
  // rnn->addNeuron(src);
  // rnn->addNeuron(dst);

  // rnn->update();
  // rnn->update();

  // CPPUNIT_ASSERT_DOUBLES_EQUAL(dst->output(), 2.46, 0.000001);

  // delete rnn;
}
