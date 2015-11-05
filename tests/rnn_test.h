#ifndef __RNN_TEST_H__
#define __RNN_TEST_H__

#include <cppunit/extensions/HelperMacros.h>

class rnnTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(rnnTest);
  CPPUNIT_TEST(testNeuronWithoutSynapses);
  CPPUNIT_TEST(testSynapse);
  CPPUNIT_TEST(testNeuronWithSynapses);
  CPPUNIT_TEST(testRNNUpdate);
  CPPUNIT_TEST_SUITE_END();

  public:

  void testNeuronWithoutSynapses();
  void testSynapse();
  void testNeuronWithSynapses();
  void testRNNUpdate();

};

#endif // __RNN_H__
