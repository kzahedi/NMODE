#ifndef __DATA_POPULATION_H__
#define __DATA_POPULATION_H__

#include "DataNode.h"
#include "DataIndividual.h"

# define TAG_POPULATION            (char*)"population"
# define TAG_POPULATION_DEFINITION (char*)"population_definition"

class DataPopulation : public DataNode
{
  public:
    DataPopulation(DataNode *parent);
    // ~DataPopulation();

    //DataPopulation(const DataPopulation);
    //DataPopulation operator=(const DataPopulation);

    void add(DataParseElement *element);
    static void createXsd(XsdSpecification *spec);

    
    DataIndividuals::iterator i_begin();
    DataIndividuals::iterator i_end();
    int                       i_size();
    DataIndividuals           individuals();
    DataIndividual            individual(int index);
    int                       generation();

  private:

    int             _generation;
    DataIndividuals _individuals;
};

#endif // __DATA_POPULATION_H__


