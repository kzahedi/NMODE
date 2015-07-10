#ifndef __POPULATION_H__
#define __POPULATION_H__

#include "Individual.h"

class Population
{
  public:
    Population();
    ~Population();

    //Population(const Population);
    //Population operator=(const Population);

    void initialise();
    Individual* individual(int index);


  private:
    Individuals _individuals;
};


#endif // __POPULATION_H__
