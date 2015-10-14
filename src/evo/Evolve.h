#ifndef __EVOLVE_H__
#define __EVOLVE_H__

#include "base/PopulationContainer.h"
#include "base/Observer.h"
#include "base/Data.h"
#include "Reproduction.h"
#include "Evaluate.h"

#include <string>
#include <vector>
#include <boost/thread.hpp>

using namespace std;
using namespace boost;

class Evolve : public Observer
{
  public:
    Evolve();

    void init(string xml);

    void notify(ObservableMessage *message);

  private:

    // Reproduction*        _reproduction;
    PopulationContainer*   _pc;
    Data*                  _data;
    Population*            _pop;
    vector<Evaluate*>      _evaluators;
    vector<boost::thread*> _threads;
};

#endif // __EVOLVE_H__
