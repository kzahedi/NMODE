#ifndef __IO_TEST_H__
#define __IO_TEST_H__

#include <cppunit/extensions/HelperMacros.h>

class ioTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(ioTest);
  CPPUNIT_TEST(testIOModulesAndNeurons);
  CPPUNIT_TEST_SUITE_END();

  public:

  void testIOModulesAndNeurons();

};

#endif // __RNN_H__
