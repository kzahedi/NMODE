#define BOOST_TEST_MODULE gis_test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <nmode/RNN.h>
#include <nmode/NMODEException.h>

#include <iostream>

using namespace std;
using namespace boost::test_tools;

BOOST_AUTO_TEST_SUITE(RNN_TESTS)

BOOST_AUTO_TEST_CASE(NEURON_WITHOUT_SYNAPSE)
{
  Neuron *n = new Neuron();

  // BOOST_CHECK_THROW(n->setTransferfunction(12), NMODEException);

  n->setTransferfunction(NEURON_TRANSFER_FUNCTION_TANH);

  for(double i = -100.0; i <=100.0; i = i + 1.0)
  {
    n->setBias(i/100.0);
    n->updateActivity();
    n->updateOutput();
    BOOST_TEST(tanh(i/100.0) == n->output(), tolerance(0.000001));
  }

  n->setTransferfunction(NEURON_TRANSFER_FUNCTION_SIGM);

  for(double i = -100.0; i <=100.0; i = i + 1.0)
  {
    n->setBias(i/100.0);
    n->updateActivity();
    n->updateOutput();
    BOOST_TEST((1.0 / (1.0 + exp(-i/100.0))) == n->output(), tolerance(0.000001));
  }

  n->setTransferfunction(NEURON_TRANSFER_FUNCTION_ID);

  for(double i = -100.0; i <=100.0; i = i + 1.0)
  {
    n->setBias(i/100.0);
    n->updateActivity();
    n->updateOutput();
    BOOST_TEST((i/100.0) == n->output(), tolerance(0.000001));
  }
  delete n;
}

BOOST_AUTO_TEST_CASE(TEST_SYNAPSE)
{
  Neuron *n = new Neuron();

  n->setTransferfunction(NEURON_TRANSFER_FUNCTION_ID);
  n->setBias(2.0);
  n->updateActivity();
  n->updateOutput();

  Synapse *s = new Synapse();
  s->setSource(n);
  s->setWeight(2.0);

  BOOST_TEST(4.0 == s->value(), tolerance(0.000001));

  delete s;
}

BOOST_AUTO_TEST_CASE(NEURON_WITH_SYNAPSE)
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

  BOOST_TEST(dst->output() == 2.46, tolerance(0.000001));

  delete src;
  delete dst;
}

BOOST_AUTO_TEST_CASE(RNNUpdate)
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

BOOST_AUTO_TEST_SUITE_END()
