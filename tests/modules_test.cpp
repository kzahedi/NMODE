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
#include "evo/ModuleNeuron.h"
#include "evo/Module.h"

#include <iostream>
#include <string>

using namespace std;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( modulesTest );


void modulesTest::testModules()
{
  // string file = "../bin/test.xml";
  // Data *data = Data::instance();
  // data->read(file);


}

void modulesTest::testModuleNeuronEquality()
{
  ModuleNeuron *a = new ModuleNeuron();
  a->setTransferfunction("tanh");
  a->setPosition(P3D(1.0, 1.0, 1.0));
  a->setLabel("label");
  a->setType("sensor");

  CPPUNIT_ASSERT("tanh"                    == a->transferfunction());
  CPPUNIT_ASSERT(P3D(1.0, 1.0, 1.0)        == a->position());
  CPPUNIT_ASSERT("label"                   == a->label());
  CPPUNIT_ASSERT(MODULE_NEURON_TYPE_SENSOR == a->type());

  ModuleNeuron *b = new ModuleNeuron();
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

  ModuleNeuron *aa = new ModuleNeuron();
  aa->setType("sensor");
  aa->setLabel("sensor 1");
  aa->setPosition(P3D(0.0,0.0,0.0));
  aa->setTransferfunction("id");

  ModuleNeuron *ab = new ModuleNeuron();
  ab->setType("sensor");
  ab->setLabel("sensor 2");
  ab->setPosition(P3D(1.0,0.0,0.0));
  ab->setTransferfunction("id");

  ModuleNeuron *ac = new ModuleNeuron();
  ac->setType("sensor");
  ac->setLabel("sensor 3");
  ac->setPosition(P3D(2.0,0.0,0.0));
  ac->setTransferfunction("id");

  ModuleNeuron *ad = new ModuleNeuron();
  ad->setType("actuator");
  ad->setLabel("actuator 1");
  ad->setPosition(P3D(0.5,1.0,0.0));
  ad->setTransferfunction("tanh");

  ModuleNeuron *ae = new ModuleNeuron();
  ae->setType("actuator");
  ae->setLabel("actuator 2");
  ae->setPosition(P3D(1.5,1.0,0.0));
  ae->setTransferfunction("sigm");

  a->addNeuron(aa);
  a->addNeuron(ab);
  a->addNeuron(ac);
  a->addNeuron(ad);
  a->addNeuron(ae);


  Module *b = new Module("module 2");

  ModuleNeuron *ba = new ModuleNeuron();
  ba->setType("sensor");
  ba->setLabel("sensor 1");
  ba->setPosition(P3D(0.0,0.0,0.0));
  ba->setTransferfunction("id");

  ModuleNeuron *bb = new ModuleNeuron();
  bb->setType("sensor");
  bb->setLabel("sensor 2");
  bb->setPosition(P3D(1.0,0.0,0.0));
  bb->setTransferfunction("id");

  ModuleNeuron *bc = new ModuleNeuron();
  bc->setType("sensor");
  bc->setLabel("sensor 3");
  bc->setPosition(P3D(2.0,0.0,0.0));
  bc->setTransferfunction("id");

  ModuleNeuron *bd = new ModuleNeuron();
  bd->setType("actuator");
  bd->setLabel("actuator 1");
  bd->setPosition(P3D(0.5,1.0,0.0));
  bd->setTransferfunction("tanh");

  ModuleNeuron *be = new ModuleNeuron();
  be->setType("actuator");
  be->setLabel("actuator 2");
  be->setPosition(P3D(1.5,1.0,0.0));
  be->setTransferfunction("sigm");

  b->addNeuron(ba);
  b->addNeuron(bb);
  b->addNeuron(bc);
  b->addNeuron(bd);
  b->addNeuron(be);

  CPPUNIT_ASSERT(*aa == *ba);

  CPPUNIT_ASSERT(*a == *b);

}

void modulesTest::testModuleInequality()
{
  Module *a = new Module("module 1");

  ModuleNeuron *aa = new ModuleNeuron();
  aa->setType("sensor");
  aa->setLabel("sensor 1");
  aa->setPosition(P3D(0.0,0.0,0.0));
  aa->setTransferfunction("id");

  ModuleNeuron *ab = new ModuleNeuron();
  ab->setType("sensor");
  ab->setLabel("sensor 2");
  ab->setPosition(P3D(1.0,0.0,0.0));
  ab->setTransferfunction("id");

  ModuleNeuron *ac = new ModuleNeuron();
  ac->setType("sensor");
  ac->setLabel("sensor 3");
  ac->setPosition(P3D(2.0,0.0,0.0));
  ac->setTransferfunction("id");

  ModuleNeuron *ad = new ModuleNeuron();
  ad->setType("actuator");
  ad->setLabel("actuator 1");
  ad->setPosition(P3D(0.5,1.0,0.0));
  ad->setTransferfunction("tanh");

  ModuleNeuron *ae = new ModuleNeuron();
  ae->setType("actuator");
  ae->setLabel("actuator 2");
  ae->setPosition(P3D(1.5,1.0,0.0));
  ae->setTransferfunction("sigm");

  a->addNeuron(aa);
  a->addNeuron(ab);
  a->addNeuron(ac);
  a->addNeuron(ad);
  a->addNeuron(ae);


  Module *b = new Module("module 2");

  ModuleNeuron *ba = new ModuleNeuron();
  ba->setType("sensor");
  ba->setLabel("sensor 1");
  ba->setPosition(P3D(0.0,0.0,0.0));
  ba->setTransferfunction("id");

  ModuleNeuron *bb = new ModuleNeuron();
  bb->setType("sensor");
  bb->setLabel("sensor 2");
  bb->setPosition(P3D(1.0,0.0,0.0));
  bb->setTransferfunction("id");

  ModuleNeuron *bc = new ModuleNeuron();
  bc->setType("sensor");
  bc->setLabel("sensor 3");
  bc->setPosition(P3D(2.0,0.0,0.0));
  bc->setTransferfunction("id");

  ModuleNeuron *bd = new ModuleNeuron();
  bd->setType("actuator");
  bd->setLabel("actuator 1");
  bd->setPosition(P3D(0.5,1.0,0.0));
  bd->setTransferfunction("tanh");

  ModuleNeuron *be = new ModuleNeuron();
  be->setType("actuator");
  be->setLabel("actuator 2");
  be->setPosition(P3D(2.5,1.0,0.0));
  be->setTransferfunction("sigm");

  b->addNeuron(ba);
  b->addNeuron(bb);
  b->addNeuron(bc);
  b->addNeuron(bd);
  b->addNeuron(be);

  CPPUNIT_ASSERT(*a != *b);
}
