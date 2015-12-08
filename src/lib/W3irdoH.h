#include <nmode/Evaluate.h>

#include <nmode/RNN.h>
#include <nmode/Population.h>

#include <yars/cppClientCom/YarsClientCom.h>

#include <entropy++/Container.h>
#include <entropy++/Hs.h>

#include <sstream>

class W3irdoH : public Evaluate
{
  public:
    W3irdoH();

    void updateController();
    void updateFitnessFunction();
    bool abort();
    void newIndividual();
    void evaluationCompleted();

  private:
    double             _x;
    double             _y;
    double             _dist;
    double             _distFactor;
    double             _hFactor;
    int                _bins;
    int                _containerSize;
    int                _combinationType;
    string             _combinationTypeString;
    vector<Container*> _containers;
    Hs*                _h;
};
