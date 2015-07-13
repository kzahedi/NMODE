#ifndef __POPULATION_EXPORTER_H__
#define __POPULATION_EXPORTER_H__

#include "Population.h"

#include <string>

using namespace std;

class PopulationExporter
{
  public:

    static string toXml(Population *pop);
    // static string toPov(Population *pop);

  private:
    static string __individualToXml(Individual *individual);
    static string __moduleToXml(Module *module);

    // static string __individualToPov(Individual *individual);
    // static string __moduleToPov(Module *module);

};


#endif // __POPULATION_EXPORTER_H__
