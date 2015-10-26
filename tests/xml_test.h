#ifndef __CONFIGURATION_TEST_H__
#define __CONFIGURATION_TEST_H__

#include <cppunit/extensions/HelperMacros.h>

class xmlTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(xmlTest);
  CPPUNIT_TEST(testXml);
  CPPUNIT_TEST_SUITE_END();

  public:

  void testXml();

};

#endif // __RNN_H__
