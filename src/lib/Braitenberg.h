#include <nmode/Evaluate.h>

#include <nmode/RNN.h>
#include <nmode/Population.h>

#include <yars/cppClientCom/YarsClientCom.h>

# define FF_DISTANCE 3001

#include <sstream>

class Braitenberg : public Evaluate
{
  public:
    Braitenberg();

    void updateController();
    void updateFitnessFunction();
    bool abort();
    void newIndividual();
};
