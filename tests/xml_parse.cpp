#include "data/Data.h"

#include <iostream>
#include <string>

using namespace std;


int main(int, char**)
{
  string file = "bin/test.xml";
  Data *d = Data::instance();
  d->read(file);
  return 0;
}
