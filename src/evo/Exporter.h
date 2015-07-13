#ifndef __POPULATION_EXPORTER_H__
#define __POPULATION_EXPORTER_H__

#include "Population.h"

#include <string>

using namespace std;

class Exporter
{
  public:

    static string toXml(Population *population);
    static string toXml(Individual *individual);
    static string toXml(Module *module);

    // static string toPov(Population *population, bool useHeader = true);
    static string toPov(Individual *individual, bool useHeader = false);
    static string toPov(Module *module,         bool useHeader = false);
    static string toPov(Node *node,             bool useHeader = false);
    // static string toPov(Edge *edge,             bool useHeader = false);

  private:

    static string __povHeader();


};


#endif // __POPULATION_EXPORTER_H__
