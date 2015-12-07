#include <nmode/Evaluate.h>

#include <nmode/RNN.h>
#include <nmode/Population.h>

#include <yars/cppClientCom/YarsClientCom.h>

#include <entropy++/Container.h>
#include <entropy++/PIs.h>

#include <sstream>

class W3irdoPI : public Evaluate
{
  public:
    W3irdoPI();

    void updateController();
    void updateFitnessFunction();
    bool abort();
    void newIndividual();
    void evaluationCompleted();

  private:
    double     _x;
    double     _y;
    double     _dist;
    Container* _l1c;
    Container* _l2c;
    Container* _l3c;
    PIs*       _pi;
};
