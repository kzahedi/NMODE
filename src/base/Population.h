#ifndef __DATA_POPULATION_H__
#define __DATA_POPULATION_H__

#include "XsdParseNode.h"
#include "Individual.h"
#include "Observable.h"

#include <pthread.h>

# define TAG_POPULATION            (char*)"population"
# define TAG_POPULATION_DEFINITION (char*)"population_definition"

class Population : public XsdParseNode, public Observable
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
    Individual*           getNextIndividual();
    int                   generation();
    void                  addIndividual(Individual*);
    void                  sortByFitness();
    void                  incGeneration();
    void                  calculateSelectionProbabilities();
    void                  resize(int);
    void                  evaluationCompleted();
    void                  reproductionCompleted();

    static Population*    instance();

  private:

    int             _generation;
    int             _individualId;
    int             _nextIndividual;
    int             _openEvaluations;
    Individuals     _individuals;
    pthread_mutex_t _mutex;

    static Population* _me;
};


#endif // __DATA_POPULATION_H__
