#ifndef __NMODE_DATA_POPULATION_H__
#define __NMODE_DATA_POPULATION_H__

#include <nmode/XsdParseNode.h>
#include <nmode/Individual.h>
#include <nmode/Observable.h>
#include <nmode/Stats.h>

#include <pthread.h>
#include <iostream>
#include <fstream>

# define TAG_POPULATION            (char*)"population"
# define TAG_POPULATION_DEFINITION (char*)"population_definition"

#ifdef USE_PLPLOT
# include <plplot.h>
# include <plConfig.h>
# include <plevent.h>
#endif // USE_PLPLOT

class Population : public Observable, public XsdParseNode
{
  public:
    Population(XsdParseNode *parent = NULL);
    ~Population();

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
    void                  setGeneration(int);
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

    void                  removeCurrentLogDir();
    void                  setCurrentLogDir(string);
    void                  plotLast();
    
    void                  readStats(string);

    static Population*    instance();

  private:
    void            __getUniqueDirectoryName();
    void            __calculateSelectionProbabilities();
#ifdef USE_PLPLOT
    void __plotData();
    void __plotMaxFitness();
    void __plotAvgFitness();
    void __plotNrHiddenUnits();
    void __plotAvgHiddenUnits();
    void __plotNrEdges();
    void __plotAvgEdges();
    void __plotNrOfOffspring();
    void __plfbox( PLFLT x0, PLFLT y0 );
#endif // USE_PLPLOT
    void            __calculateStats();

    int             _generation;
    int             _individualId;
    int             _nextIndividual;
    int             _openEvaluations;
    string          _logDirectory;
    Individuals     _individuals;
    pthread_mutex_t _mutex;
    ofstream        _output;
    Statistics      _stats;

    static Population* _me;
};


#endif // __DATA_POPULATION_H__
