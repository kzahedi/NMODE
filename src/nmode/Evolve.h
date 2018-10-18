#ifndef __NMODE_EVOLVE_H__
#define __NMODE_EVOLVE_H__

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

class Evolve : public Observer
{
public:
  Evolve(bool printConfiguration = false);

  void init(string xml, bool read = true, string log = "");
  void initFromDir(string dir);

  void notify(ObservableMessage *message);

private:
  // Reproduction*        _reproduction;
  Population *_population;
  Data *_data;
  Population *_pop;
  Reproduction *_reproduction;
  vector<Evaluate *> _evaluators;
  vector<boost::thread *> _threads;
  bool _printConfiguration;
};

#endif // __EVOLVE_H__
