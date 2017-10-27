#include <nmode/Evaluate.h>

#include <nmode/RNN.h>
#include <nmode/Population.h>

#include <yars/cppClientCom/YarsClientCom.h>

#include <sstream>

class Hexaboard : public Evaluate
{
  public:
    Hexaboard();

    void updateController();
    void updateFitnessFunction();
    bool abort();
    void newIndividual();
    void evaluationCompleted();

  private:
    double _x;
    double _y;
    double _z;
    double _alpha;
    double _beta;
    double _gamma;
    double _mbContact;
    double _dist;
    bool   _abort;
    double _intermediateFitness;
};
