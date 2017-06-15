#define BOOST_TEST_MODULE gis_test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <nmode/Random.h>
#include <nmode/Node.h>
#include <nmode/Module.h>

#include <iostream>
#include <string>
#include <glog/logging.h>

using namespace std;
using namespace boost::test_tools;

BOOST_AUTO_TEST_SUITE(MODULES_TEST)

BOOST_AUTO_TEST_CASE(NODE_EUQALITY)
{
  Node *a = new Node();
  a->setTransferfunction("tanh");
  a->setPosition(P3D(1.0, 1.0, 1.0));
  a->setLabel("label");
  a->setType("sensor");

  BOOST_TEST(string("tanh")     == a->transferfunction());
  BOOST_TEST(P3D(1.0, 1.0, 1.0) == a->position());
  BOOST_TEST(string("label")    == a->label());
  BOOST_TEST(TAG_SENSOR         == a->type());

  Node *b = new Node();
  b->setTransferfunction("tanh");
  b->setPosition(P3D(1.0, 1.0, 1.0));
  b->setLabel("label");
  b->setType("sensor");

  BOOST_TEST((*a == *b) == true);

  b->setType("actuator");

  BOOST_TEST((*a == *b) == false);
  BOOST_TEST((*a != *b) == true);

  b->setType("sensor");
  b->setPosition(P3D(1.0, 1.0, 0.0));

  BOOST_TEST((*a == *b) == false);
  BOOST_TEST((*a != *b) == true);
}


BOOST_AUTO_TEST_CASE(MODULE_EUQALITY)
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

  BOOST_TEST((*aa == *ba) == true);

  BOOST_TEST((*a == *b) == true);

}

BOOST_AUTO_TEST_CASE(MODULE_INEUQALITY)
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

  BOOST_TEST((*a != *b) == false);
}


BOOST_AUTO_TEST_CASE(MUTATE_MODULE_OPERATOR)
{
  Random::initialise();
}


BOOST_AUTO_TEST_CASE(MODULE_ADD_EDGE)
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

  BOOST_TEST(a->e_size()               == 1);
  BOOST_TEST(ab->e_size()              == 1);
  BOOST_TEST(aa->e_size()              == 0);
  BOOST_TEST(ab->edge(0)->sourceNode() == aa);

  // BOOST_TEST_THROW(a->addEdge(aa, ab, 1.0), NMODEException);
}


BOOST_AUTO_TEST_CASE(MODULE_COPY_CONSTRUCTOR)
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
  BOOST_TEST((*a == b) == true);
}

BOOST_AUTO_TEST_CASE(MODULE_COPY_OPERATOR)
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

  BOOST_TEST(5 == a->n_size());

  Module *b = new Module(NULL);
  (*b) = (*a);
  BOOST_TEST((*a == *b) == true);
  BOOST_TEST(a->n_size() == b->n_size());
}


BOOST_AUTO_TEST_CASE(MODULE_APPLY_MIRROR)
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

  BOOST_TEST(a->n_size() == 2);

  Module *b = new Module();
  b->setMirrorAxes(true, true, true);
  b->copyAndApplyTransition(a);

  BOOST_TEST(-1.0 == b->node(0)->position().x);
  BOOST_TEST(-1.0 == b->node(0)->position().y);
  BOOST_TEST(-1.0 == b->node(0)->position().z);

  BOOST_TEST(-2.0 == b->node(1)->position().x);
  BOOST_TEST(-2.0 == b->node(1)->position().y);
  BOOST_TEST(-2.0 == b->node(1)->position().z);
}

BOOST_AUTO_TEST_CASE(MODULE_TRANSLATION)
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

  BOOST_TEST(a->n_size() == 2);

  Module *b = new Module();
  b->setMirrorAxes(false, false, false);
  b->setTranslation(P3D(1.0, -1.0, 5.0));
  b->copyAndApplyTransition(a);

  BOOST_TEST( 2.0 == b->node(0)->position().x);
  BOOST_TEST( 0.0 == b->node(0)->position().y);
  BOOST_TEST( 6.0 == b->node(0)->position().z);

  BOOST_TEST( 3.0 == b->node(1)->position().x);
  BOOST_TEST( 1.0 == b->node(1)->position().y);
  BOOST_TEST( 7.0 == b->node(1)->position().z);
}

BOOST_AUTO_TEST_CASE(MODULE_ROTATION)
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

  BOOST_TEST(a->n_size() == 2);

  Module *b = new Module();
  b->setMirrorAxes(false, false, false);
  b->setRotation(P3D(0.0, M_PI_2, 0.0));
  b->copyAndApplyTransition(a);

  BOOST_TEST( 1.0 == b->node(0)->position().x, tolerance(0.000001));
  BOOST_TEST( 1.0 == b->node(0)->position().y, tolerance(0.000001));
  BOOST_TEST(-1.0 == b->node(0)->position().z, tolerance(0.000001));

  BOOST_TEST( 2.0 == b->node(1)->position().x, tolerance(0.000001));
  BOOST_TEST( 2.0 == b->node(1)->position().y, tolerance(0.000001));
  BOOST_TEST(-2.0 == b->node(1)->position().z, tolerance(0.000001));
}

BOOST_AUTO_TEST_CASE(MODULE_TRANSITION)
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

  BOOST_TEST(a->n_size() == 2);

  Module *b = new Module();
  b->setMirrorAxes(false, false, false);
  b->setRotation(P3D(0.0, M_PI_2, 0.0));
  b->setTranslation(P3D(1.0, -1.0, 5.0));
  b->copyAndApplyTransition(a);

  BOOST_TEST( 2.0 == b->node(0)->position().x, tolerance(0.000001));
  BOOST_TEST( 0.0 == b->node(0)->position().y, tolerance(0.000001));
  BOOST_TEST( 4.0 == b->node(0)->position().z, tolerance(0.000001));

  BOOST_TEST( 3.0 == b->node(1)->position().x, tolerance(0.000001));
  BOOST_TEST( 1.0 == b->node(1)->position().y, tolerance(0.000001));
  BOOST_TEST( 3.0 == b->node(1)->position().z, tolerance(0.000001));
}

BOOST_AUTO_TEST_CASE(MODULE_COPY)
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

  BOOST_TEST((b != a) == true);
  for(int i = 0; i < 5; i++) BOOST_TEST(b->node(i)          != a->node(i));
  for(int i = 0; i < 5; i++) BOOST_TEST(b->edge(i)          != a->edge(i));
  for(int i = 0; i < 5; i++) BOOST_TEST(b->node(i)->label() == a->node(i)->label());
  for(int i = 0; i < 5; i++) BOOST_TEST(b->node(i)->bias()  == a->node(i)->bias());
  for(int i = 0; i < 5; i++) BOOST_TEST(b->node(i)->position() == a->node(i)->position());
  for(int i = 0; i < 5; i++) BOOST_TEST(b->node(i)->transferfunction() ==
                                            a->node(i)->transferfunction());
}

BOOST_AUTO_TEST_SUITE_END()
