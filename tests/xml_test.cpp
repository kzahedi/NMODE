#define BOOST_TEST_MODULE gis_test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <nmode/Data.h>
#include <nmode/macros.h>

#include <iostream>
#include <string>

using namespace std;
using namespace boost::test_tools;

BOOST_AUTO_TEST_SUITE(XML)

BOOST_AUTO_TEST_CASE(TEST_XML)
{
  string file = "../bin/test.xml";
  Data *d = Data::instance();
  d->read(file);

  NMODE              *nmode  = d->specification();

  Simulator        *sim = nmode->simulator();


  BOOST_TEST(string("working directory") == sim->workingDirectory());
  BOOST_TEST(string("xml file")          == sim->xml());
  BOOST_TEST(42                          == sim->nr());


  CfgMutation     *mutation  = nmode->mutation();

  CfgMutationNode *mn = mutation->node();
  CfgMutationEdge *me = mutation->edge();

  BOOST_TEST(0.11 == mn->modifyProbability(), tolerance(0.000001));
  BOOST_TEST(0.12 == mn->modifyMaxValue(),    tolerance(0.000001));
  BOOST_TEST(0.13 == mn->modifyDelta(),       tolerance(0.000001));

  BOOST_TEST(0.21 == me->modifyProbability(), tolerance(0.000001));
  BOOST_TEST(0.22 == me->modifyMaxValue(),    tolerance(0.000001));
  BOOST_TEST(0.23 == me->modifyDelta(),       tolerance(0.000001));

  Configuration* conf = nmode->configuration();
  Modules        mods = conf->modules();

  BOOST_TEST(3 == mods.size());
  BOOST_TEST(string("module 1") == mods[0]->name());

  Nodes mod_1_nodes = mods[0]->nodes();
  BOOST_TEST(9 == mod_1_nodes.size());

  BOOST_TEST(string("sensor")     == mod_1_nodes[0]->type());
  BOOST_TEST(string("sensor 1")   == mod_1_nodes[0]->label());
  BOOST_TEST(P3D(0.0, 0.0, 0.0)   == mod_1_nodes[0]->position());
  BOOST_TEST(string("id")         == mod_1_nodes[0]->transferfunction());

  BOOST_TEST(string("sensor")     == mod_1_nodes[1]->type());
  BOOST_TEST(string("sensor 2")   == mod_1_nodes[1]->label());
  BOOST_TEST(P3D(1.0, 0.0, 0.0)   == mod_1_nodes[1]->position());
  BOOST_TEST(string("id")         == mod_1_nodes[1]->transferfunction());

  BOOST_TEST(string("sensor")     == mod_1_nodes[2]->type());
  BOOST_TEST(string("sensor 3")   == mod_1_nodes[2]->label());
  BOOST_TEST(P3D(2.0, 0.0, 0.0)   == mod_1_nodes[2]->position());
  BOOST_TEST(string("id")         == mod_1_nodes[2]->transferfunction());

  BOOST_TEST(string("actuator")   == mod_1_nodes[3]->type());
  BOOST_TEST(string("actuator 1") == mod_1_nodes[3]->label());
  BOOST_TEST(P3D(0.5, 1.0, 0.0)   == mod_1_nodes[3]->position());
  BOOST_TEST(string("tanh")       == mod_1_nodes[3]->transferfunction());

  BOOST_TEST(string("actuator")   == mod_1_nodes[4]->type());
  BOOST_TEST(string("actuator 2") == mod_1_nodes[4]->label());
  BOOST_TEST(P3D(1.5, 1.0, 0.0)   == mod_1_nodes[4]->position());
  BOOST_TEST(string("sigm")       == mod_1_nodes[4]->transferfunction());

  BOOST_TEST(string("module 2")   == mods[1]->name());
  Nodes mod_2_nodes                = mods[1]->nodes();
  BOOST_TEST(3                    == mod_2_nodes.size());

  BOOST_TEST(string("sensor")     == mod_2_nodes[0]->type());
  BOOST_TEST(string("sensor 1")   == mod_2_nodes[0]->label());
  BOOST_TEST(P3D(0.0, 0.0, 0.0)   == mod_2_nodes[0]->position());
  BOOST_TEST(string("sigm")       == mod_2_nodes[0]->transferfunction());

  BOOST_TEST(string("sensor")     == mod_2_nodes[1]->type());
  BOOST_TEST(string("sensor 2")   == mod_2_nodes[1]->label());
  BOOST_TEST(P3D(1.0, 0.0, 0.0)   == mod_2_nodes[1]->position());
  BOOST_TEST(string("id")         == mod_2_nodes[1]->transferfunction());

  BOOST_TEST(string("actuator")   == mod_2_nodes[2]->type());
  BOOST_TEST(string("actuator 1") == mod_2_nodes[2]->label());
  BOOST_TEST(P3D(0.5, 1.0, 0.0)   == mod_2_nodes[2]->position());
  BOOST_TEST(string("tanh")       == mod_2_nodes[2]->transferfunction());
}

BOOST_AUTO_TEST_SUITE_END()
