/*************************************************************************
 *                                                                       *
 * This file is part of Evolution of Neural Pathways (ENP).              *
 * Copyright (C) 2003-2015 Keyan Ghazi-Zahedi.                           *
 * All rights reserved.                                                  *
 * Email: keyan.zahedi@googlemail.com                                    *
 * Web: https://github.com/kzahedi/ENP                                   *
 *                                                                       *
 * For a list of contributors see the file AUTHORS.                      *
 *                                                                       *
 * YARS is free software; you can redistribute it and/or modify it under *
 * the terms of the GNU General Public License as published by the Free  *
 * Software Foundation; either version 2 of the License, or (at your     *
 * option) any later version.                                            *
 *                                                                       *
 * YARS is distributed in the hope that it will be useful, but WITHOUT   *
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or *
 * FITNESS FOR A PARTICULAR PURPOSE.                                     *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with YARS in the file COPYING; if not, write to the Free        *
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor,               *
 * Boston, MA 02110-1301, USA                                            *
 *                                                                       *
 *************************************************************************/



#include "rnn_from_individual_test.h"

#include "base/RNN.h"
#include "base/ENPException.h"
#include "base/Individual.h"
#include "base/RnnFromIndividual.h"

#include <iostream>

using namespace std;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( rnnFromIndividualTest );

void rnnFromIndividualTest::testRnnFromIndividual()
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

  CPPUNIT_ASSERT_EQUAL(12, rnn->nrOfNeurons());
  CPPUNIT_ASSERT_EQUAL(2,  rnn->nrOfHidden());
  CPPUNIT_ASSERT_EQUAL(6,  rnn->nrOfSensors());
  CPPUNIT_ASSERT_EQUAL(4,  rnn->nrOfActuators());

  for(int i = 0; i < rnn->nrOfSensors(); i++)
  {
    CPPUNIT_ASSERT_EQUAL(NEURON_TRANSFER_FUNCTION_ID,
                         rnn->getSensorNeuron(i)->transferfunction());
  }

  for(int i = 0; i < rnn->nrOfActuators(); i++)
  {
    CPPUNIT_ASSERT_EQUAL(NEURON_TRANSFER_FUNCTION_SIGM,
                         rnn->getActuatorNeuron(i)->transferfunction());
  }

  for(int i = 0; i < rnn->nrOfHidden(); i++)
  {
    CPPUNIT_ASSERT_EQUAL(NEURON_TRANSFER_FUNCTION_TANH,
                         rnn->getHiddenNeuron(i)->transferfunction());
  }

  for(int i = 0; i < rnn->nrOfNeurons(); i++)
  {
    CPPUNIT_ASSERT_EQUAL(1, rnn->getNeuron(i)->nrOfSynapses());
  }

}

void rnnFromIndividualTest::testRnnFromIndividualWithConnectorNodes()
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

  CPPUNIT_ASSERT_EQUAL(12, rnn->nrOfNeurons());
  CPPUNIT_ASSERT_EQUAL(3,  rnn->nrOfHidden());
  CPPUNIT_ASSERT_EQUAL(5,  rnn->nrOfSensors());
  CPPUNIT_ASSERT_EQUAL(4,  rnn->nrOfActuators());

  for(int i = 0; i < rnn->nrOfSensors(); i++)
  {
    CPPUNIT_ASSERT_EQUAL(NEURON_TRANSFER_FUNCTION_ID,
                         rnn->getSensorNeuron(i)->transferfunction());
  }

  for(int i = 0; i < rnn->nrOfActuators(); i++)
  {
    CPPUNIT_ASSERT_EQUAL(NEURON_TRANSFER_FUNCTION_SIGM,
                         rnn->getActuatorNeuron(i)->transferfunction());
  }

  for(int i = 0; i < rnn->nrOfHidden(); i++)
  {
    CPPUNIT_ASSERT_EQUAL(NEURON_TRANSFER_FUNCTION_TANH,
                         rnn->getHiddenNeuron(i)->transferfunction());
  }

  for(int i = 0; i < rnn->nrOfNeurons(); i++)
  {
    if(i == 6 || i == 7) CPPUNIT_ASSERT_EQUAL(2, rnn->getNeuron(i)->nrOfSynapses());
    else                 CPPUNIT_ASSERT_EQUAL(1, rnn->getNeuron(i)->nrOfSynapses());
  }
}
