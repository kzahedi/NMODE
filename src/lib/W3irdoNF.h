#include <nmode/Evaluate.h>

#include <nmode/RNN.h>
#include <nmode/Population.h>

#include <yars/cppClientCom/YarsClientCom.h>

#include <entropy++/Container.h>

#include <sstream>

class W3irdoNF : public Evaluate
{
  public:
    W3irdoNF();

    void updateController();
    void updateFitnessFunction();
    bool abort();
    void newIndividual();
    void evaluationCompleted();

  private:
    double               _x;
    double               _y;
    double               _z;
    double               _mbContact;
    double               _dist;
    double               _distFactor;
    double               _itFactor;
    double               _oscillationFactor;
    int                  _bins;
    int                  _containerOffset;
    int                  _combinationType;
    string               _combinationTypeString;
    string               _measure;
    int                  _measureType;
    vector<Container*>   _containers;
    vector<vector<int> > _containerIndices;
    vector<double>       _lastSensorReading;
};
