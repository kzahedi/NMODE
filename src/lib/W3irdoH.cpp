#include "W3irdoH.h"

#include <nmode/RnnFromIndividual.h>
#include <nmode/Data.h>

#include <sstream>

#define MIN3(a,c,b) ((a<b)?((c<a)?c:a):(c<b)?c:b)

# define ADD 1001
# define MUL 1002

W3irdoH::W3irdoH()
  : Evaluate()
{
  networkInput.resize(33);
  _h = new Hs();
}

void W3irdoH::updateController()
{
  for(int i = 0; i < (int)networkInput.size(); i++) networkInput[i] = sensorValues[i];
  for(int i = 0;  i < 15; i++)
  {
    // cout << "container index = " << i / _containerSize << endl;
    (*_containers[i / _containerSize]) << sensorValues[i];
  }
}

void W3irdoH::updateFitnessFunction()
{
  _x       = sensorValues[31];
  _y       = sensorValues[32];
  _dist    = sqrt(_x * _x + _y * _y);
  fitness += _distFactor * _dist;
}

bool W3irdoH::abort()
{
  return false;
}

void W3irdoH::newIndividual()
{
  EVA->set("bins",             _bins,                  30);
  EVA->set("distance factor",  _distFactor,            1.0);
  EVA->set("entropy factor",   _hFactor,               1.0);
  EVA->set("container size",   _containerSize,         1);
  EVA->set("combination type", _combinationTypeString, "add");
  if(_combinationTypeString == "add")
  {
    _combinationType = ADD;
  }
  else
  {
    _combinationType = MUL;
  }
  for(int i = 0; i < (int)_containers.size(); i++)
  {
    if(_containers[i] != NULL) delete _containers[i];
  }
  _containers.clear();
  for(int i = 0; i < 15 / _containerSize; i++)
  {
    _containers.push_back(new Container(lifeTime, _containerSize));
  }
  double** domains = new double*[_containerSize];
  int*     bins    = new int[_containerSize];
  for(int i = 0; i < _containerSize; i++)
  {
    domains[i]    = new double[2];
    domains[i][0] = -1.0;
    domains[i][1] =  1.0;
    bins[i]       = _bins;
  }
  for(vector<Container*>::iterator c = _containers.begin(); c != _containers.end(); c++)
  {
    (*c)->setDomains(domains);
    (*c)->setBinSizes(bins);
  }
  cout << "Bins: " << _bins << " DF: " << _distFactor << " EF: " << _hFactor << " CS: " << _containerSize << endl;
}

void W3irdoH::evaluationCompleted()
{
  stringstream sst;
  double r = 0;
  int    i = 0;
  sst << "Factor: " << _hFactor << " Results:";
  for(vector<Container*>::iterator c = _containers.begin(); c != _containers.end(); c++)
  {
    i++;
    Container *d = (*c)->discretise();
    double s  = _h->calculate(d) / log2(_bins);
    sst << " " << s;
    r += _hFactor * s;
    delete d;
  }
  sst << endl;
  if(_combinationType == ADD)
  {
    fitness += r;
  }
  else
  {
    fitness *= r;
  }
  fitness /= (double)lifeTime;
  sst << "Fitness: " << fitness;
  cout << sst.str() << endl;
}

// the class factories
extern "C" Evaluate* create()
{
  W3irdoH *e = new W3irdoH();
  return (Evaluate*)e;
}

extern "C" void destroy(Evaluate*) {}
