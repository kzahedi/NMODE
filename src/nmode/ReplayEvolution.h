#ifndef __NMODE_REPLAY_EVOLUION_H__
#define __NMODE_REPLAY_EVOLUION_H__

#include <nmode/Observer.h>
#include <nmode/Data.h>
#include <nmode/Reproduction.h>
#include <nmode/Evaluate.h>

#include <string>
#include <vector>
#include <boost/thread.hpp>
#include <dlfcn.h>

using namespace std;
using namespace boost;

class ReplayEvolution : public Observer
{
  public:
    ReplayEvolution();

    void replayBestIndividual(string xml);
    void replayEvolution(string dir);

    void notify(ObservableMessage *message);

    void setRestart(bool r);

  private:

    // Reproduction*        _reproduction;
    Population*            _population;
    Data*                  _data;
    Population*            _pop;
    Reproduction*          _reproduction;
    vector<Evaluate*>      _evaluators;
    vector<boost::thread*> _threads;
    Evaluate*              _e;
};

#endif // __REPLAY_EVOLUION_H__
