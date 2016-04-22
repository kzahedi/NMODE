#ifndef __NMODE_EXPORTER_H__
#define __NMODE_EXPORTER_H__

#include <nmode/Population.h>

#include <string>

using namespace std;

class Exporter
{
  public:


    static string toX3d(Individual *individual);
    static string toX3d(Module     *module);
    static string toX3d(Node       *node);
    static string toX3d(Edge       *edge);

  private:

    static string __x3dHeader();
    static string __x3dFooter();

    static string __cylinder(P3D start, P3D end, string color);

};


#endif // __POPULATION_EXPORTER_H__
