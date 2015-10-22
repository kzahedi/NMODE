#include "enp/EvaluateTemplate.h"

#include "enp/RNN.h"
#include "enp/Population.h"

#include <yars/cppClientCom/YarsClientCom.h>

# define FF_DISTANCE 3001

#include <sstream>

class Evaluate : public EvaluateTemplate
{
  public:
    Evaluate();

    void updateController();
    void updateFitnessFunction();
    bool abort();

  private:
    double _x;
    double _y;
    double _lastX;
    double _lastY;
    double _dist;
};
