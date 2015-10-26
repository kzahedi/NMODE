/*************************************************************************
 *                                                                       *
 * This file is part of Evolution of Neural Pathways (NMODE).              *
 * Copyright (C) 2003-2015 Keyan Ghazi-Zahedi.                           *
 * All rights reserved.                                                  *
 * Email: keyan.zahedi@googlemail.com                                    *
 * Web: https://github.com/kzahedi/NMODE                                   *
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
#include "nmode/Random.h"
#include "nmode/Node.h"
#include "nmode/Module.h"

#include <iostream>
#include <string>
#include <glog/logging.h>

using namespace std;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( modulesTest );


void modulesTest::setUp()
{
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
  CPPUNIT_ASSERT(TAG_SENSOR         == a->type());

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


  Module *b = new Module();
  b->setName("module 2");

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

  Module *b = new Module();
  b->setName("module 2");

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

  CPPUNIT_ASSERT((*a != *b) == false);
}


void modulesTest::testMutateModuleOperator()
{
  Random::initialise();
}


void modulesTest::testModuleAddEdge()
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

  a->addNode(aa);
  a->addNode(ab);

  a->addEdge(aa, ab, 1.0);

  CPPUNIT_ASSERT(a->e_size()               == 1);
  CPPUNIT_ASSERT(ab->e_size()              == 1);
  CPPUNIT_ASSERT(aa->e_size()              == 0);
  CPPUNIT_ASSERT(ab->edge(0)->sourceNode() == aa);

  CPPUNIT_ASSERT_THROW(a->addEdge(aa, ab, 1.0), NMODEException);
}


void modulesTest::testModuleCopyConstructor()
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

  Module b = *a;
  CPPUNIT_ASSERT(*a == b);
}

void modulesTest::testModuleCopyOperator()
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

  CPPUNIT_ASSERT_EQUAL(5, a->n_size());

  Module *b = new Module(NULL);
  (*b) = (*a);
  CPPUNIT_ASSERT(*a == *b);
  CPPUNIT_ASSERT_EQUAL(a->n_size(), b->n_size());
}


void modulesTest::testModuleApplyMirror()
{
  Module *a = new Module();
  a->setName("module 1");

  Node *aa = new Node();
  aa->setType("sensor");
  aa->setLabel("sensor 1");
  aa->setPosition(P3D(1.0,1.0,1.0));
  aa->setTransferfunction("id");

  Node *ab = new Node();
  ab->setType("sensor");
  ab->setLabel("sensor 2");
  ab->setPosition(P3D(2.0,2.0,2.0));
  ab->setTransferfunction("id");

  a->addNode(aa);
  a->addNode(ab);

  CPPUNIT_ASSERT(a->n_size() == 2);

  Module *b = new Module();
  b->setMirrorAxes(true, true, true);
  b->copyAndApplyTransition(a);

  CPPUNIT_ASSERT_EQUAL(-1.0, b->node(0)->position().x);
  CPPUNIT_ASSERT_EQUAL(-1.0, b->node(0)->position().y);
  CPPUNIT_ASSERT_EQUAL(-1.0, b->node(0)->position().z);

  CPPUNIT_ASSERT_EQUAL(-2.0, b->node(1)->position().x);
  CPPUNIT_ASSERT_EQUAL(-2.0, b->node(1)->position().y);
  CPPUNIT_ASSERT_EQUAL(-2.0, b->node(1)->position().z);
}

void modulesTest::testModuleTranslation()
{
  Module *a = new Module();
  a->setName("module 1");

  Node *aa = new Node();
  aa->setType("sensor");
  aa->setLabel("sensor 1");
  aa->setPosition(P3D(1.0,1.0,1.0));
  aa->setTransferfunction("id");

  Node *ab = new Node();
  ab->setType("sensor");
  ab->setLabel("sensor 2");
  ab->setPosition(P3D(2.0,2.0,2.0));
  ab->setTransferfunction("id");

  a->addNode(aa);
  a->addNode(ab);

  CPPUNIT_ASSERT(a->n_size() == 2);

  Module *b = new Module();
  b->setMirrorAxes(false, false, false);
  b->setTranslation(P3D(1.0, -1.0, 5.0));
  b->copyAndApplyTransition(a);

  CPPUNIT_ASSERT_EQUAL( 2.0, b->node(0)->position().x);
  CPPUNIT_ASSERT_EQUAL( 0.0, b->node(0)->position().y);
  CPPUNIT_ASSERT_EQUAL( 6.0, b->node(0)->position().z);

  CPPUNIT_ASSERT_EQUAL( 3.0, b->node(1)->position().x);
  CPPUNIT_ASSERT_EQUAL( 1.0, b->node(1)->position().y);
  CPPUNIT_ASSERT_EQUAL( 7.0, b->node(1)->position().z);
}

void modulesTest::testModuleRotation()
{
  Module *a = new Module();
  a->setName("module 1");

  Node *aa = new Node();
  aa->setType("sensor");
  aa->setLabel("sensor 1");
  aa->setPosition(P3D(1.0,1.0,1.0));
  aa->setTransferfunction("id");

  Node *ab = new Node();
  ab->setType("sensor");
  ab->setLabel("sensor 2");
  ab->setPosition(P3D(2.0,2.0,2.0));
  ab->setTransferfunction("id");

  a->addNode(aa);
  a->addNode(ab);

  CPPUNIT_ASSERT(a->n_size() == 2);

  Module *b = new Module();
  b->setMirrorAxes(false, false, false);
  b->setRotation(P3D(0.0, M_PI_2, 0.0));
  b->copyAndApplyTransition(a);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0, b->node(0)->position().x, 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0, b->node(0)->position().y, 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, b->node(0)->position().z, 0.000001);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( 2.0, b->node(1)->position().x, 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 2.0, b->node(1)->position().y, 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-2.0, b->node(1)->position().z, 0.000001);
}

void modulesTest::testModuleTransition()
{
  Module *a = new Module();
  a->setName("module 1");

  Node *aa = new Node();
  aa->setType("sensor");
  aa->setLabel("sensor 1");
  aa->setPosition(P3D(1.0,1.0,1.0));
  aa->setTransferfunction("id");

  Node *ab = new Node();
  ab->setType("sensor");
  ab->setLabel("sensor 2");
  ab->setPosition(P3D(2.0,2.0,2.0));
  ab->setTransferfunction("id");

  a->addNode(aa);
  a->addNode(ab);

  CPPUNIT_ASSERT(a->n_size() == 2);

  Module *b = new Module();
  b->setMirrorAxes(false, false, false);
  b->setRotation(P3D(0.0, M_PI_2, 0.0));
  b->setTranslation(P3D(1.0, -1.0, 5.0));
  b->copyAndApplyTransition(a);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( 2.0, b->node(0)->position().x, 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.0, b->node(0)->position().y, 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 4.0, b->node(0)->position().z, 0.000001);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( 3.0, b->node(1)->position().x, 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0, b->node(1)->position().y, 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 3.0, b->node(1)->position().z, 0.000001);
}

void modulesTest::testModuleCopy()
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

  a->addEdge(aa, ab, 1.0);
  a->addEdge(ab, ac, 2.0);
  a->addEdge(ac, ad, 3.0);
  a->addEdge(ad, ae, 4.0);
  a->addEdge(ae, aa, 5.0);
  
  Module *b = a->copy();

  CPPUNIT_ASSERT(b != a);
  for(int i = 0; i < 5; i++) CPPUNIT_ASSERT(b->node(i)          != a->node(i));
  for(int i = 0; i < 5; i++) CPPUNIT_ASSERT(b->edge(i)          != a->edge(i));
  for(int i = 0; i < 5; i++) CPPUNIT_ASSERT(b->node(i)->label() == a->node(i)->label());
  for(int i = 0; i < 5; i++) CPPUNIT_ASSERT(b->node(i)->bias()  == a->node(i)->bias());
  for(int i = 0; i < 5; i++) CPPUNIT_ASSERT(b->node(i)->position() == a->node(i)->position());
  for(int i = 0; i < 5; i++) CPPUNIT_ASSERT(b->node(i)->transferfunction() ==
                                            a->node(i)->transferfunction());
}
