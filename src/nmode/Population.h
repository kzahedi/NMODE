#ifndef __DATA_POPULATION_H__
#define __DATA_POPULATION_H__

#include "XsdParseNode.h"
#include "Individual.h"
#include "Observable.h"

#include <pthread.h>
#include <iostream>
#include <fstream>

# define TAG_POPULATION            (char*)"population"
# define TAG_POPULATION_DEFINITION (char*)"population_definition"

class Population : public Observable, public XsdParseNode
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
    void                  resize(int);
    void                  evaluationCompleted();
    void                  reproductionCompleted();
    void                  serialise();
    void                  incAge();
    void                  calculateNrOfOffspring();
    void                  cleanup();

    static Population*    instance();

  private:
    void            __getUniqueDirectoryName();
    void            __calculateSelectionProbabilities();

    int             _generation;
    int             _individualId;
    int             _nextIndividual;
    int             _openEvaluations;
    string          _logDirectory;
    Individuals     _individuals;
    pthread_mutex_t _mutex;
    ofstream        _output;

    static Population* _me;
};


#endif // __DATA_POPULATION_H__
