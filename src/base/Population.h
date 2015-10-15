#ifndef __DATA_POPULATION_H__
#define __DATA_POPULATION_H__

#include "XsdParseNode.h"
#include "Individual.h"

# define TAG_POPULATION            (char*)"population"
# define TAG_POPULATION_DEFINITION (char*)"population_definition"

class Population : public XsdParseNode
{
  public:
    Population(XsdParseNode *parent = NULL);
    // ~Population();

    //Population(const Population);
    //Population operator=(const Population);

    void add(ParseElement *element);
    static void createXsd(XsdSpecification *spec);

    
    Individuals::iterator i_begin();
    Individuals::iterator i_end();
    int                   i_size();
    Individuals           individuals();
    Individual*           individual(int index);
    int                   generation();
    void                  addIndividual(Individual*);
    void                  sortByFitness();
    void                  incGeneration();
    void                  calculateSelectionProbabilities();
    void                  resize(int);

    static Population*    instance();

  private:

    int         _generation;
    int         _individualId;
    Individuals _individuals;

    static Population* _me;
};


#endif // __DATA_POPULATION_H__
