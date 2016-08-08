#include <nmode/Evaluate.h>

#include <nmode/RNN.h>
#include <nmode/Population.h>

#include <yars/cppClientCom/YarsClientCom.h>

#include <entropy++/Container.h>

#include <sstream>

class W3irdo : public Evaluate
{
  public:
    W3irdo();

    void updateController();
    void updateFitnessFunction();
    bool abort();
    void newIndividual();
    void evaluationCompleted();

  private:
    double               _x;
    double               _y;
    double               _dist;
    double               _distFactor;
    double               _itFactor;
    int                  _bins;
    int                  _containerOffset;
    int                  _combinationType;
    string               _combinationTypeString;
    string               _measure;
    int                  _measureType;
    vector<DContainer*>  _containers;
    vector<vector<int> > _containerIndices;
};
