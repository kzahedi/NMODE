#ifndef __IO_TEST_H__
#define __IO_TEST_H__

#include <cppunit/extensions/HelperMacros.h>

class ioTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(ioTest);
  CPPUNIT_TEST(testIOModulesAndNeurons);
  CPPUNIT_TEST(testAgain1);
  CPPUNIT_TEST(testAgain2);
  CPPUNIT_TEST(testAgain3);
  CPPUNIT_TEST(testAgain4);
  CPPUNIT_TEST(testAgain5);
  CPPUNIT_TEST(testAgain6);
  CPPUNIT_TEST(testAgain7);
  CPPUNIT_TEST(testAgain8);
  CPPUNIT_TEST(testAgain9);
  CPPUNIT_TEST_SUITE_END();

  public:
  void tearDown();

  void testIOModulesAndNeurons();
  void testAgain1();
  void testAgain2();
  void testAgain3();
  void testAgain4();
  void testAgain5();
  void testAgain6();
  void testAgain7();
  void testAgain8();
  void testAgain9();
  
};

#endif // __RNN_H__
