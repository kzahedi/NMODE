#ifndef __CONFIGURATION_TEST_H__
#define __CONFIGURATION_TEST_H__

#include <cppunit/extensions/HelperMacros.h>

class cfgTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(cfgTest);
  CPPUNIT_TEST(testConfiguration);
  CPPUNIT_TEST_SUITE_END();

  public:

  void testConfiguration();

};

#endif // __RNN_H__
