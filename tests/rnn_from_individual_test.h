#ifndef __RNN_FROM_INDIVIDUAL_TEST_H__
#define __RNN_FROM_INDIVIDUAL_TEST_H__

#include <cppunit/extensions/HelperMacros.h>

class rnnFromIndividualTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(rnnFromIndividualTest);
  CPPUNIT_TEST(testRnnFromIndividual);
  CPPUNIT_TEST(testRnnFromIndividualWithConnectorNodes);
  CPPUNIT_TEST_SUITE_END();

  public:

  void testRnnFromIndividual();
  void testRnnFromIndividualWithConnectorNodes();

};

#endif // __RNN_FROM_INDIVIDUAL_H__
