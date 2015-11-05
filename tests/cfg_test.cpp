#include "cfg_test.h"

#include <nmode/Configuration.h>

#include <iostream>
#include <string>

using namespace std;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( cfgTest );


void cfgTest::testConfiguration()
{
  string name = "cfg-tests";
  // string help = "--help";
  string file = "bin/test.ini";
  char** parameters;
  parameters = new char*[2];
  parameters[0] = &name[0];
  parameters[1] = &file[0];

  Configuration *c = new Configuration(2, parameters);
  delete c;
}
