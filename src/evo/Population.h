#ifndef __POPULATION_H__
#define __POPULATION_H__

#include "Individual.h"

#include <string>
#include <ostream>

using namespace std;

class Population
{
  public:
    Population();
    ~Population();

    //Population(const Population);
    //Population operator=(const Population);

    void initialise();

    Individuals::iterator i_begin();
    Individuals::iterator i_end();
    int                   i_size();
    Individual*           individual(int index);
    int                   generation();

  private:
    Individuals _individuals;
    int         _generation;
};


#endif // __POPULATION_H__
