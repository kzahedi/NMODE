#ifndef __MODULES_TEST_H__
#define __MODULES_TEST_H__

#include <cppunit/extensions/HelperMacros.h>

class modulesTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(modulesTest);
  CPPUNIT_TEST(testModules);
  CPPUNIT_TEST(testNodeEquality);
  CPPUNIT_TEST(testModuleEquality);
  CPPUNIT_TEST(testModuleInequality);
  CPPUNIT_TEST(testMutateModuleOperator);
  CPPUNIT_TEST(testModuleAddEdge);
  CPPUNIT_TEST(testModuleCopyConstructor);
  CPPUNIT_TEST(testModuleCopyOperator);
  CPPUNIT_TEST(testModuleApplyMirror);
  CPPUNIT_TEST(testModuleTranslation);
  CPPUNIT_TEST(testModuleRotation);
  CPPUNIT_TEST(testModuleTransition);
  CPPUNIT_TEST(testModuleCopy);
  CPPUNIT_TEST_SUITE_END();

  public:

  void setUp();
  void testModules();
  void testNodeEquality();
  void testModuleEquality();
  void testModuleInequality();
  void testMutateModuleOperator();
  void testModuleAddEdge();
  void testModuleCopyConstructor();
  void testModuleCopyOperator();
  void testModuleApplyMirror();
  void testModuleTranslation();
  void testModuleRotation();
  void testModuleTransition();
  void testModuleCopy();
};

#endif // __RNN_H__
