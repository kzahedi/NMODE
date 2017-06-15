#define BOOST_TEST_MODULE gis_test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <nmode/RNN.h>
#include <nmode/NMODEException.h>
#include <nmode/Individual.h>
#include <nmode/RnnFromIndividual.h>

#include <iostream>

using namespace std;

BOOST_AUTO_TEST_SUITE(RNN_FROM_INDIVIDUAL)

BOOST_AUTO_TEST_CASE(TEST_RNN_FROM_INDIVIDUAL)
{
  Module *a = new Module();
  a->setName("module 1");

  Node *aa = new Node();
  aa->setType("sensor");
  aa->setLabel("sensor 1");
  aa->setPosition(P3D(0.0,0.0,0.0));
  aa->setTransferfunction("id");

  Node *ab = new Node();
  ab->setType("sensor");
  ab->setLabel("sensor 2");
  ab->setPosition(P3D(1.0,0.0,0.0));
  ab->setTransferfunction("id");

  Node *ac = new Node();
  ac->setType("sensor");
  ac->setLabel("sensor 3");
  ac->setPosition(P3D(2.0,0.0,0.0));
  ac->setTransferfunction("id");

  Node *ad = new Node();
  ad->setType("actuator");
  ad->setLabel("actuator 1");
  ad->setPosition(P3D(0.5,1.0,0.0));
  ad->setTransferfunction("sigm");

  Node *ae = new Node();
  ae->setType("actuator");
  ae->setLabel("actuator 2");
  ae->setPosition(P3D(1.5,1.0,0.0));
  ae->setTransferfunction("sigm");

  Node *af = new Node();
  af->setType("hidden");
  af->setLabel("hidden 1");
  af->setPosition(P3D(1.5,1.0,1.0));
  af->setTransferfunction("tanh");

  a->addNode(aa);
  a->addNode(ab);
  a->addNode(ac);
  a->addNode(ad);
  a->addNode(ae);
  a->addNode(af);

  a->addEdge(aa, ab, 1.0);
  a->addEdge(ab, ac, 2.0);
  a->addEdge(ac, ad, 3.0);
  a->addEdge(ad, ae, 4.0);
  a->addEdge(ae, af, 5.0);
  a->addEdge(af, aa, 6.0);

  Module *b = new Module();
  b->setName("module 2");
  b->setIsCopy(true);
  b->setTarget("module 1");
  b->setMirrorAxes(true, false, false);

  Individual *i = new Individual();
  i->addModule(a);
  i->addModule(b);

  RNN *rnn = RnnFromIndividual::create(i);

  BOOST_TEST(12 == rnn->nrOfNeurons());
  BOOST_TEST(2  == rnn->nrOfHidden());
  BOOST_TEST(6  == rnn->nrOfSensors());
  BOOST_TEST(4  == rnn->nrOfActuators());

  for(int i = 0; i < rnn->nrOfSensors(); i++)
  {
    BOOST_TEST(NEURON_TRANSFER_FUNCTION_ID ==
               rnn->getSensorNeuron(i)->transferfunction());
  }

  for(int i = 0; i < rnn->nrOfActuators(); i++)
  {
    BOOST_TEST(NEURON_TRANSFER_FUNCTION_SIGM ==
               rnn->getActuatorNeuron(i)->transferfunction());
  }

  for(int i = 0; i < rnn->nrOfHidden(); i++)
  {
    BOOST_TEST(NEURON_TRANSFER_FUNCTION_TANH ==
                         rnn->getHiddenNeuron(i)->transferfunction());
  }

  for(int i = 0; i < rnn->nrOfNeurons(); i++)
  {
    BOOST_TEST(1 == rnn->getNeuron(i)->nrOfSynapses());
  }

}

BOOST_AUTO_TEST_CASE(RNN_FROM_INDIVIDUAL_WITH_CONNECTOR_NODES)
{
  Module *a = new Module();
  a->setName("module 1");

  Node *aa = new Node();
  aa->setType("sensor");
  aa->setLabel("sensor 1");
  aa->setPosition(P3D(0.0,0.0,0.0));
  aa->setTransferfunction("id");

  Node *ab = new Node();
  ab->setType("sensor");
  ab->setLabel("sensor 2");
  ab->setPosition(P3D(1.0,0.0,0.0));
  ab->setTransferfunction("id");

  Node *ac = new Node();
  ac->setType("sensor");
  ac->setLabel("sensor 3");
  ac->setPosition(P3D(2.0,0.0,0.0));
  ac->setTransferfunction("id");

  Node *ad = new Node();
  ad->setType("actuator");
  ad->setLabel("actuator 1");
  ad->setPosition(P3D(0.5,1.0,0.0));
  ad->setTransferfunction("sigm");

  Node *ae = new Node();
  ae->setType("actuator");
  ae->setLabel("actuator 2");
  ae->setPosition(P3D(1.5,1.0,0.0));
  ae->setTransferfunction("sigm");

  Node *af = new Node();
  af->setType("hidden");
  af->setLabel("hidden 1");
  af->setPosition(P3D(1.5,1.0,1.0));
  af->setTransferfunction("tanh");

  Node *ag = new Node();
  ag->setType("input");
  ag->setLabel("input 1");
  ag->setPosition(P3D(1.5,1.0,2.0));
  ag->setTransferfunction("tanh");

  Node *ah = new Node();
  ah->setType("output");
  ah->setLabel("output 1");
  ah->setPosition(P3D(1.5,1.0,-2.0));
  ah->setTransferfunction("tanh");

  a->addNode(aa);
  a->addNode(ab);
  a->addNode(ac);
  a->addNode(ad);
  a->addNode(ae);
  a->addNode(af);
  a->addNode(ag);
  a->addNode(ah);

  a->addEdge(aa, ab, 1.0);
  a->addEdge(ab, ac, 2.0);
  a->addEdge(ac, ad, 3.0);
  a->addEdge(ad, ae, 4.0);
  a->addEdge(ae, af, 5.0);
  a->addEdge(af, ag, 6.0);
  a->addEdge(ag, ah, 7.0);
  a->addEdge(ah, aa, 8.0);

  Module *b = new Module();
  b->setName("cpg");

  Node *ba = new Node();
  ba->setType("sensor");
  ba->setLabel("sensor 1");
  ba->setPosition(P3D(0.0,0.0,0.0));
  ba->setTransferfunction("id");

  Node *bb = new Node();
  bb->setType("sensor");
  bb->setLabel("sensor 2");
  bb->setPosition(P3D(1.0,0.0,0.0));
  bb->setTransferfunction("id");

  Node *bc = new Node();
  bc->setType("actuator");
  bc->setLabel("actuator 1");
  bc->setPosition(P3D(0.5,1.0,0.0));
  bc->setTransferfunction("sigm");

  Node *bd = new Node();
  bd->setType("actuator");
  bd->setLabel("actuator 2");
  bd->setPosition(P3D(1.5,1.0,0.0));
  bd->setTransferfunction("sigm");

  Node *be = new Node();
  be->setType("connector");
  be->setLabel("module 1/input 1");
  be->setPosition(P3D(0.0,0.0,0.0));
  be->setTransferfunction("sigm");

  Node *bf = new Node();
  bf->setType("connector");
  bf->setLabel("module 1/output 1");
  bf->setPosition(P3D(0.0,0.0,0.0));
  bf->setTransferfunction("sigm");

  b->addNode(ba);
  b->addNode(bb);
  b->addNode(bc);
  b->addNode(bd);
  b->addNode(be);
  b->addNode(bf);

  b->addEdge(ba, bb, 11.0);
  b->addEdge(bb, bc, 12.0);
  b->addEdge(bc, bd, 13.0);
  b->addEdge(bd, be, 14.0);
  b->addEdge(be, bf, 15.0);
  b->addEdge(bf, ba, 16.0);

  Individual *i = new Individual();
  i->addModule(a);
  i->addModule(b);

  RNN *rnn = RnnFromIndividual::create(i);

  BOOST_TEST(12 == rnn->nrOfNeurons());
  BOOST_TEST(3  == rnn->nrOfHidden());
  BOOST_TEST(5  == rnn->nrOfSensors());
  BOOST_TEST(4  == rnn->nrOfActuators());

  for(int i = 0; i < rnn->nrOfSensors(); i++)
  {
    BOOST_TEST(NEURON_TRANSFER_FUNCTION_ID ==
               rnn->getSensorNeuron(i)->transferfunction());
  }

  for(int i = 0; i < rnn->nrOfActuators(); i++)
  {
    BOOST_TEST(NEURON_TRANSFER_FUNCTION_SIGM ==
               rnn->getActuatorNeuron(i)->transferfunction());
  }

  for(int i = 0; i < rnn->nrOfHidden(); i++)
  {
    BOOST_TEST(NEURON_TRANSFER_FUNCTION_TANH ==
               rnn->getHiddenNeuron(i)->transferfunction());
  }

  for(int i = 0; i < rnn->nrOfNeurons(); i++)
  {
    if(i == 6 || i == 7) BOOST_TEST(2 == rnn->getNeuron(i)->nrOfSynapses());
    else                 BOOST_TEST(1 == rnn->getNeuron(i)->nrOfSynapses());
  }
}

BOOST_AUTO_TEST_SUITE_END()
