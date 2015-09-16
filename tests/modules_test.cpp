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



#include "modules_test.h"

// #include "main/Configuration.h"
// #include "data/Data.h"
#include "base/Random.h"
#include "base/DataModuleNode.h"
#include "base/Module.h"

#include <iostream>
#include <string>
#include <glog/logging.h>

using namespace std;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( modulesTest );


void modulesTest::setUp()
{
  cout << "HIER HIER" << endl;
}

void modulesTest::testModules()
{
  // string file = "../bin/test.xml";
  // Data *data = Data::instance();
  // data->read(file);


}

void modulesTest::testNodeEquality()
{
  Node *a = new Node();
  a->setTransferfunction("tanh");
  a->setPosition(P3D(1.0, 1.0, 1.0));
  a->setLabel("label");
  a->setType("sensor");

  CPPUNIT_ASSERT("tanh"             == a->transferfunction());
  CPPUNIT_ASSERT(P3D(1.0, 1.0, 1.0) == a->position());
  CPPUNIT_ASSERT("label"            == a->label());
  CPPUNIT_ASSERT(NODE_TYPE_SENSOR   == a->type());

  Node *b = new Node();
  b->setTransferfunction("tanh");
  b->setPosition(P3D(1.0, 1.0, 1.0));
  b->setLabel("label");
  b->setType("sensor");

  CPPUNIT_ASSERT(*a == *b);

  b->setType("actuator");

  CPPUNIT_ASSERT((*a == *b) == false);
  CPPUNIT_ASSERT(*a != *b);

  b->setType("sensor");
  b->setPosition(P3D(1.0, 1.0, 0.0));

  CPPUNIT_ASSERT((*a == *b) == false);
  CPPUNIT_ASSERT(*a != *b);
}


void modulesTest::testModuleEquality()
{
  Module *a = new Module("module 1");

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
  ad->setTransferfunction("tanh");

  Node *ae = new Node();
  ae->setType("actuator");
  ae->setLabel("actuator 2");
  ae->setPosition(P3D(1.5,1.0,0.0));
  ae->setTransferfunction("sigm");

  a->addNode(aa);
  a->addNode(ab);
  a->addNode(ac);
  a->addNode(ad);
  a->addNode(ae);


  Module *b = new Module("module 2");

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
  bc->setType("sensor");
  bc->setLabel("sensor 3");
  bc->setPosition(P3D(2.0,0.0,0.0));
  bc->setTransferfunction("id");

  Node *bd = new Node();
  bd->setType("actuator");
  bd->setLabel("actuator 1");
  bd->setPosition(P3D(0.5,1.0,0.0));
  bd->setTransferfunction("tanh");

  Node *be = new Node();
  be->setType("actuator");
  be->setLabel("actuator 2");
  be->setPosition(P3D(1.5,1.0,0.0));
  be->setTransferfunction("sigm");

  b->addNode(ba);
  b->addNode(bb);
  b->addNode(bc);
  b->addNode(bd);
  b->addNode(be);

  CPPUNIT_ASSERT(*aa == *ba);

  CPPUNIT_ASSERT(*a == *b);

}

void modulesTest::testModuleInequality()
{
  Module *a = new Module("module 1");

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
  ad->setTransferfunction("tanh");

  Node *ae = new Node();
  ae->setType("actuator");
  ae->setLabel("actuator 2");
  ae->setPosition(P3D(1.5,1.0,0.0));
  ae->setTransferfunction("sigm");

  a->addNode(aa);
  a->addNode(ab);
  a->addNode(ac);
  a->addNode(ad);
  a->addNode(ae);


  Module *b = new Module("module 2");

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
  bc->setType("sensor");
  bc->setLabel("sensor 3");
  bc->setPosition(P3D(2.0,0.0,0.0));
  bc->setTransferfunction("id");

  Node *bd = new Node();
  bd->setType("actuator");
  bd->setLabel("actuator 1");
  bd->setPosition(P3D(0.5,1.0,0.0));
  bd->setTransferfunction("tanh");

  Node *be = new Node();
  be->setType("actuator");
  be->setLabel("actuator 2");
  be->setPosition(P3D(2.5,1.0,0.0));
  be->setTransferfunction("sigm");

  b->addNode(ba);
  b->addNode(bb);
  b->addNode(bc);
  b->addNode(bd);
  b->addNode(be);

  CPPUNIT_ASSERT(*a != *b);
}


void modulesTest::testMutateModuleOperator()
{
  Random::initialise();
}


void modulesTest::testModuleAddEdge()
{
  Module *a = new Module("module 1");

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

  a->addNode(aa);
  a->addNode(ab);

  a->addEdge(aa, ab, 1.0);

  CPPUNIT_ASSERT(a->e_size()           == 1);
  CPPUNIT_ASSERT(ab->e_size()          == 1);
  CPPUNIT_ASSERT(aa->e_size()          == 0);
  CPPUNIT_ASSERT(ab->edge(0)->source() == aa);

  CPPUNIT_ASSERT_THROW(a->addEdge(aa, ab, 1.0), ENPException);
}
