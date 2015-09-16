#ifndef __DATA_POPULATION_H__
#define __DATA_POPULATION_H__

#include "XsdParseNode.h"
#include "Individual.h"

# define TAG_POPULATION            (char*)"population"
# define TAG_POPULATION_DEFINITION (char*)"population_definition"

class Population : public XsdParseNode
{
  public:
    Population(XsdParseNode *parent);
    // ~Population();

    //Population(const Population);
    //Population operator=(const Population);

    void add(DataParseElement *element);
    static void createXsd(XsdSpecification *spec);

    
    Individuals::iterator i_begin();
    Individuals::iterator i_end();
    int                       i_size();
    Individuals           individuals();
    Individual            individual(int index);
    int                       generation();

  private:

    int             _generation;
    Individuals _individuals;
};

#endif // __DATA_POPULATION_H__


