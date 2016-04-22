#ifndef __NMODE_STATS_H__
#define __NMODE_STATS_H__

#include <nmode/Individual.h>
#include <vector>

using namespace std;

class Stats
{

  public:
    Stats(const Individuals&);
    double bestFitness()       {return _bestFitness;};
    double avgFitness()        {return _avgFitness;};
    double sdFitness()         {return _sdFitness;};
    double minSdFitness()      {return _minSdFitness;};
    double maxSdFitness()      {return _maxSdFitness;};

    double bestNrHiddenUnits() {return _bestNrHiddenUnits;};
    double avgNrHiddenUnits()  {return _avgNrHiddenUnits;};
    double sdHiddenUnits()     {return _sdHiddenUnits;};
    double minSdHiddenUnits()  {return _minSdHiddenUnits;};
    double maxSdHiddenUnits()  {return _maxSdHiddenUnits;};

    double bestNrEdges()       {return _bestNrEdges;};
    double avgNrEdges()        {return _avgNrEdges;};
    double sdEdges()           {return _sdEdges;};
    double minSdEdges()        {return _minSdEdges;};
    double maxSdEdges()        {return _maxSdEdges;};

  private:
    void    __bestFitness(const Individuals&);
    void    __avgFitness(const Individuals&);
    void    __sdFitness(const Individuals&);

    void    __bestHidden(const Individuals&);
    void    __avgHidden(const Individuals&);
    void    __sdHidden(const Individuals&);

    void    __bestEdges(const Individuals&);
    void    __avgEdges(const Individuals&);
    void    __sdEdges(const Individuals&);

    double _bestFitness;
    double _avgFitness;
    double _sdFitness;
    double _minSdFitness;
    double _maxSdFitness;

    double _bestNrHiddenUnits;
    double _avgNrHiddenUnits;
    double _sdHiddenUnits;
    double _minSdHiddenUnits;
    double _maxSdHiddenUnits;

    double _bestNrEdges;
    double _avgNrEdges;
    double _sdEdges;
    double _minSdEdges;
    double _maxSdEdges;
};

typedef vector<Stats*> Statistics;

#endif //__STATS_H__
