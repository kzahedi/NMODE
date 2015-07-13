#ifndef __INDIVIDUAL_H__
#define __INDIVIDUAL_H__

#include "base/data/DataIndividual.h"
#include "Module.h"

#include <vector>
#include <string>
#include <ostream>

using namespace std;

class Individual
{
  public:
    Individual();
    ~Individual();

    //Individual(const Individual);
    //Individual operator=(const Individual);

    void    setFitness(double fitness);
    void    setId(int id);

    double  fitness();
    int     id();

    void    initialise(DataIndividual *data);
    void    add(DataModule *module);

    Module* module(int index);
    Modules::iterator m_begin();
    Modules::iterator m_end();
    int               m_size();

  private:
    double  _fitness;
    int     _id;
    Modules _modules;
};

typedef vector<Individual*> Individuals;

#endif // __INDIVIDUAL_H__
