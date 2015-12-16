#include "W3irdo.h"

#include <entropy++/sparse/H.h>
#include <entropy++/sparse/PI.h>

#include <nmode/RnnFromIndividual.h>
#include <nmode/Data.h>

#include <sstream>

#define MIN3(a,c,b) ((a<b)?((c<a)?c:a):(c<b)?c:b)

# define ADD   1001
# define MUL   1002
# define MUL1  1003

# define usePI 2001
# define useMI 2002
# define useH  2003

using namespace entropy::sparse;

W3irdo::W3irdo()
  : Evaluate()
{
  networkInput.resize(31);
  _measureType     = -1;
  _combinationType = -1;
}

void W3irdo::updateController()
{
  for(int i = 0; i < (int)networkInput.size(); i++)
  {
    networkInput[i] = sensorValues[i];
  }
  for(int i = 0;  i < 15; i++)
  {
    (*_containers[i / _containerSize]) << sensorValues[2*i];
  }
}

void W3irdo::updateFitnessFunction()
{
  _x       = sensorValues[31];
  _y       = sensorValues[32];
  _dist    = sqrt(_x * _x + _y * _y);
  fitness += _distFactor * _dist;
}

bool W3irdo::abort()
{
  return false;
}

void W3irdo::newIndividual()
{
  EVA->set("bins",             _bins,                  30);
  EVA->set("distance factor",  _distFactor,            1.0);
  EVA->set("entropy factor",   _itFactor,              1.0);
  EVA->set("container size",   _containerSize,         1);
  EVA->set("combination type", _combinationTypeString, "add");
  EVA->set("measure",          _measure,               "PI");

  if(_combinationTypeString == "add")  _combinationType = ADD;
  if(_combinationTypeString == "mul")  _combinationType = MUL;
  if(_combinationTypeString == "mul1") _combinationType = MUL1;

  if(_measure == "PI") _measureType = usePI;
  if(_measure == "MI") _measureType = useMI;
  if(_measure == "H")  _measureType = useH;


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
}

void W3irdo::evaluationCompleted()
{
  stringstream sst;
  double r = 0;
  int    i = 0;
  sst << "Factor: " << _itFactor << " Results:";
  for(vector<Container*>::iterator c = _containers.begin(); c != _containers.end(); c++)
  {
    i++;
    Container *d = (*c)->discretise();
    double s  = 0.0;
    switch(_measureType)
    {
      case useH:
       s = H(d) / log2(_bins);
       break;
      case usePI:
       s = PI(d) / log2(_bins);
       break;
      default:
       cerr << "Unknown measure type: " << _measure << endl;
    }
    sst << " " << s;
    r += _itFactor * s;
    delete d;
  }
  if(_combinationType == ADD)
  {
    fitness += r / (double)_containers.size();
    cout << " Fitness: " << fitness << " " << (r / (double)_containers.size()) << " " << sst.str() << endl;
  }
  if(_combinationType == MUL1)
  {
    fitness *= 1.0 + r / (double)_containers.size();
    cout << " Fitness: " << fitness << " " << (1.0 + r / (double)_containers.size()) << " " << sst.str() << endl;
  }
  if(_combinationType == MUL)
  {
    fitness *= r / (double)_containers.size();
    cout << " Fitness: " << fitness << " " << (r / (double)_containers.size()) << " " << sst.str() << endl;
  }
}

// the class factories
extern "C" Evaluate* create()
{
  W3irdo *e = new W3irdo();
  return (Evaluate*)e;
}

extern "C" void destroy(Evaluate*) {}
