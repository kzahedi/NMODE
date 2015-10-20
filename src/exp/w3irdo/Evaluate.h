#include "evo/EvaluateTemplate.h"

#include "base/RNN.h"
#include "base/Population.h"

#include <yars/cppClientCom/YarsClientCom.h>

# define FF_DISTANCE 3001

#include <sstream>

class Evaluate : public EvaluateTemplate
{
  public:
    Evaluate();

    void updateController();
    void updateFitnessFunction();

  private:
    double _x;
    double _y;
    double _lastX;
    double _lastY;
};