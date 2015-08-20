#ifndef __DATA_INDIVIDUAL_H__
#define __DATA_INDIVIDUAL_H__

#include "DataNode.h"
#include "DataModule.h"

# define TAG_INDIVIDUAL            (char*)"individual"
# define TAG_INDIVIDUAL_DEFINITION (char*)"individual_definition"

class DataIndividual : public DataNode
{
  public:
    DataIndividual(DataNode *parent);
    // ~DataIndividual();

    //DataIndividual(const DataIndividual);
    //DataIndividual operator=(const DataIndividual);

    void add(DataParseElement *element);
    static void createXsd(XsdSpecification *spec);

    int    id();
    int    offspring();
    double fitness();

    DataModules::iterator m_begin();
    DataModules::iterator m_end();
    int                   m_size();
    DataModules           modules();

  private:
    void        __linkConnectorNodes();

    int         _id;
    int         _offspring;
    double      _fitness;
    DataModules _modules;
};

typedef vector<DataIndividual*> DataIndividuals;

#endif // __DATA_INDIVIDUAL_H__


