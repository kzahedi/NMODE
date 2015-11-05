#include "xml_test.h"

#include <nmode/Data.h>
#include <nmode/macros.h>

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
  
  NMODE              *nmode  = d->specification();

  Simulator        *sim = nmode->simulator();


  CPPUNIT_ASSERT("working directory" == sim->workingDirectory());
  CPPUNIT_ASSERT("xml file"          == sim->xml());
  CPPUNIT_ASSERT(42                  == sim->nr());


  CfgMutation     *mutation  = nmode->mutation();

  CfgMutationNode *mn = mutation->node();
  CfgMutationEdge *me = mutation->edge();
  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.11, mn->modifyProbability(), 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.12, mn->modifyMaxValue(),    0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.13, mn->modifyDelta(),       0.000001);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.21, me->modifyProbability(), 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.22, me->modifyMaxValue(),    0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.23, me->modifyDelta(),       0.000001);

  DataConfiguration *conf = nmode->configuration();
  Modules            mods = conf->modules();

  CPPUNIT_ASSERT(3 == mods.size());
  CPPUNIT_ASSERT("module 1" == mods[0]->name());

  Nodes mod_1_nodes = mods[0]->nodes();
  CPPUNIT_ASSERT(9 == mod_1_nodes.size());

  CPPUNIT_ASSERT("sensor"           == mod_1_nodes[0]->type());
  CPPUNIT_ASSERT("sensor 1"         == mod_1_nodes[0]->label());
  CPPUNIT_ASSERT(P3D(0.0, 0.0, 0.0) == mod_1_nodes[0]->position());
  CPPUNIT_ASSERT("id"               == mod_1_nodes[0]->transferfunction());

  CPPUNIT_ASSERT("sensor"           == mod_1_nodes[1]->type());
  CPPUNIT_ASSERT("sensor 2"         == mod_1_nodes[1]->label());
  CPPUNIT_ASSERT(P3D(1.0, 0.0, 0.0) == mod_1_nodes[1]->position());
  CPPUNIT_ASSERT("id"               == mod_1_nodes[1]->transferfunction());

  CPPUNIT_ASSERT("sensor"           == mod_1_nodes[2]->type());
  CPPUNIT_ASSERT("sensor 3"         == mod_1_nodes[2]->label());
  CPPUNIT_ASSERT(P3D(2.0, 0.0, 0.0) == mod_1_nodes[2]->position());
  CPPUNIT_ASSERT("id"               == mod_1_nodes[2]->transferfunction());

  CPPUNIT_ASSERT("actuator"         == mod_1_nodes[3]->type());
  CPPUNIT_ASSERT("actuator 1"       == mod_1_nodes[3]->label());
  CPPUNIT_ASSERT(P3D(0.5, 1.0, 0.0) == mod_1_nodes[3]->position());
  CPPUNIT_ASSERT("tanh"             == mod_1_nodes[3]->transferfunction());

  CPPUNIT_ASSERT("actuator"         == mod_1_nodes[4]->type());
  CPPUNIT_ASSERT("actuator 2"       == mod_1_nodes[4]->label());
  CPPUNIT_ASSERT(P3D(1.5, 1.0, 0.0) == mod_1_nodes[4]->position());
  CPPUNIT_ASSERT("sigm"             == mod_1_nodes[4]->transferfunction());

  CPPUNIT_ASSERT("module 2" == mods[1]->name());
  Nodes mod_2_nodes = mods[1]->nodes();
  CPPUNIT_ASSERT(3 == mod_2_nodes.size());

  CPPUNIT_ASSERT("sensor"           == mod_2_nodes[0]->type());
  CPPUNIT_ASSERT("sensor 1"         == mod_2_nodes[0]->label());
  CPPUNIT_ASSERT(P3D(0.0, 0.0, 0.0) == mod_2_nodes[0]->position());
  CPPUNIT_ASSERT("sigm"             == mod_2_nodes[0]->transferfunction());

  CPPUNIT_ASSERT("sensor"           == mod_2_nodes[1]->type());
  CPPUNIT_ASSERT("sensor 2"         == mod_2_nodes[1]->label());
  CPPUNIT_ASSERT(P3D(1.0, 0.0, 0.0) == mod_2_nodes[1]->position());
  CPPUNIT_ASSERT("id"               == mod_2_nodes[1]->transferfunction());

  CPPUNIT_ASSERT("actuator"         == mod_2_nodes[2]->type());
  CPPUNIT_ASSERT("actuator 1"       == mod_2_nodes[2]->label());
  CPPUNIT_ASSERT(P3D(0.5, 1.0, 0.0) == mod_2_nodes[2]->position());
  CPPUNIT_ASSERT("tanh"             == mod_2_nodes[2]->transferfunction());


}
