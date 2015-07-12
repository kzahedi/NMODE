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

    friend std::ostream& operator<<(std::ostream& str, const Population& p)
    {
      str <<"  <population generation=\"" << p._generation << "\">" << endl;

      for(Individuals::const_iterator i  = p._individuals.begin();
                                      i != p._individuals.end();
                                      i++)
      {
        str << **i;
      }
      str <<"  </population>" << endl;
      return str;
    };
  private:
    Individuals _individuals;
    int         _generation;
};


#endif // __POPULATION_H__
