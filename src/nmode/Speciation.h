#ifndef __SPECIATION_H__
#define __SPECIATION_H__

#include <nmode/Population.h>
#include <nmode/Individual.h>

#include <vector>

using namespace std;

class Speciation
{
  public:
    Speciation(double threshold);
    // ~Speciation();

    //Speciation(const Speciation);
    //Speciation operator=(const Speciation);


  private:
    void __add(Individual*);

    Population*         _population;
    vector<Individuals> _species;
    double              _threshold;
};


#endif // __SPECIATION_H__
