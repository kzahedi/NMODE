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



#include "xml_test.h"

#include "data/Data.h"
#include "base/macros.h"

#include <iostream>
#include <string>

using namespace std;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( xmlTest );


void xmlTest::testXml()
{
  string file = "../bin/test.xml";
  Data *d = Data::instance();
  d->read(file);
  
  DataENP              *enp  = d->specification();
  DataEvolution        *evo  = enp->evolution();

  DataEvolutionNeuron  *evon = evo->neuron();
  DataEvolutionSynapse *evos = evo->synapse();
  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.10, evon->cost(),              0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.11, evon->modifyProbability(), 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.12, evon->modifyMaxValue(),    0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.13, evon->modifyDelta(),       0.000001);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.20, evos->cost(),              0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.21, evos->modifyProbability(), 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.22, evos->modifyMaxValue(),    0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.23, evos->modifyDelta(),       0.000001);

  DataConfiguration *conf = enp->configuration();
  DataModules        mods = conf->modules();


  CPPUNIT_ASSERT(2 == mods.size());
  CPPUNIT_ASSERT("module 1" == mods[0]->name());

  DataModuleNeurons mod_1_neurons = mods[0]->neurons();
  CPPUNIT_ASSERT(5 == mod_1_neurons.size());

  CPPUNIT_ASSERT("sensor"           == mod_1_neurons[0]->type());
  CPPUNIT_ASSERT("sensor 1"         == mod_1_neurons[0]->label());
  CPPUNIT_ASSERT(P3D(0.0, 0.0, 0.0) == mod_1_neurons[0]->position());
  CPPUNIT_ASSERT("id"               == mod_1_neurons[0]->transferfunction());

  CPPUNIT_ASSERT("sensor"           == mod_1_neurons[1]->type());
  CPPUNIT_ASSERT("sensor 2"         == mod_1_neurons[1]->label());
  CPPUNIT_ASSERT(P3D(1.0, 0.0, 0.0) == mod_1_neurons[1]->position());
  CPPUNIT_ASSERT("id"               == mod_1_neurons[1]->transferfunction());

  CPPUNIT_ASSERT("sensor"           == mod_1_neurons[2]->type());
  CPPUNIT_ASSERT("sensor 3"         == mod_1_neurons[2]->label());
  CPPUNIT_ASSERT(P3D(2.0, 0.0, 0.0) == mod_1_neurons[2]->position());
  CPPUNIT_ASSERT("id"               == mod_1_neurons[2]->transferfunction());

  CPPUNIT_ASSERT("actuator"         == mod_1_neurons[3]->type());
  CPPUNIT_ASSERT("actuator 1"       == mod_1_neurons[3]->label());
  CPPUNIT_ASSERT(P3D(0.5, 1.0, 0.0) == mod_1_neurons[3]->position());
  CPPUNIT_ASSERT("tanh"             == mod_1_neurons[3]->transferfunction());

  CPPUNIT_ASSERT("actuator"         == mod_1_neurons[4]->type());
  CPPUNIT_ASSERT("actuator 2"       == mod_1_neurons[4]->label());
  CPPUNIT_ASSERT(P3D(1.5, 1.0, 0.0) == mod_1_neurons[4]->position());
  CPPUNIT_ASSERT("sigm"             == mod_1_neurons[4]->transferfunction());

  CPPUNIT_ASSERT("module 2" == mods[1]->name());
  DataModuleNeurons mod_2_neurons = mods[1]->neurons();
  CPPUNIT_ASSERT(3 == mod_2_neurons.size());

  CPPUNIT_ASSERT("sensor"           == mod_2_neurons[0]->type());
  CPPUNIT_ASSERT("sensor 1"         == mod_2_neurons[0]->label());
  CPPUNIT_ASSERT(P3D(0.0, 0.0, 0.0) == mod_2_neurons[0]->position());
  CPPUNIT_ASSERT("sigm"             == mod_2_neurons[0]->transferfunction());

  CPPUNIT_ASSERT("sensor"           == mod_2_neurons[1]->type());
  CPPUNIT_ASSERT("sensor 2"         == mod_2_neurons[1]->label());
  CPPUNIT_ASSERT(P3D(1.0, 0.0, 0.0) == mod_2_neurons[1]->position());
  CPPUNIT_ASSERT("id"               == mod_2_neurons[1]->transferfunction());

  CPPUNIT_ASSERT("actuator"         == mod_2_neurons[2]->type());
  CPPUNIT_ASSERT("actuator 1"       == mod_2_neurons[2]->label());
  CPPUNIT_ASSERT(P3D(0.5, 1.0, 0.0) == mod_2_neurons[2]->position());
  CPPUNIT_ASSERT("tanh"             == mod_2_neurons[2]->transferfunction());


}
