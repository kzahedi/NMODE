#include "base/Configuration.h"

#include <iostream>

int main(int argc, char** argv)
{
  Configuration *configuration = new Configuration(argc, argv);
  cout << configuration->cfg() << endl;
  return 0;
}
