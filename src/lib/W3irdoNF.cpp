#include "W3irdoNF.h"

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

W3irdoNF::W3irdoNF()
  : Evaluate()
{
  networkInput.resize(31);
  _measureType         = -1;
  _combinationType     = -1;
  _intermediateFitness = 0.0;
}

void W3irdoNF::updateController()
{
  if(_lastSensorReading.size() == 0)
  {
    _lastSensorReading.resize(sensorValues.size());
    for(int i = 0; i < (int)sensorValues.size(); i++)
    {
      _lastSensorReading[i] = sensorValues[i];
    }
  }
  for(int i = 0; i < (int)networkInput.size(); i++)
  {
    networkInput[i] = sensorValues[i];
  }
  if(_itFactor > 0.0)
  {
    for(int i = 0; i < (int)_containers.size(); i++)
    {
      for(int j = 0; j < (int)_containerIndices[i].size(); j++)
      {
        (*_containers[i]) << sensorValues[_containerIndices[i][j]];
      }
    }
  }
}

void W3irdoNF::updateFitnessFunction()
{
  _x       = sensorValues[16];
  _y       = sensorValues[17];
  _z       = sensorValues[18];
  _mbContact = sensorValues[15];
  _dist    = sqrt(_x * _x + _y * _y);
  _intermediateFitness += _distFactor * _dist; 

  for(int i = 0; i < (int)_lastSensorReading.size(); i++)
  {
    if(sensorValues[i] * _lastSensorReading[i] < 0)
    {
      _intermediateFitness -= _oscillationFactor;
    }
  }
  fitness = __entropy(_intermediateFitness);
  // cout << _intermediateFitness << " -> " << fitness << endl;
}

bool W3irdoNF::abort()
{
  return false;
}

void W3irdoNF::newIndividual()
{
  stringstream sst;

  EVA->set("bins",               _bins,                  30);
  EVA->set("distance factor",    _distFactor,            1.0);
  EVA->set("entropy factor",     _itFactor,              1.0);
  EVA->set("oscillation factor", _oscillationFactor,     0.0);
  EVA->set("container offset",   _containerOffset,       1);
  EVA->set("combination type",   _combinationTypeString, "add");
  EVA->set("measure",            _measure,               "PI");

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

  sst.str("");
  sst << "container 1";
  int index = 1;
  _containerIndices.clear();
  while(EVA->exists(sst.str()))
  {
    _containerIndices.push_back(EVA->intList(sst.str()));
    sst.str("");
    sst << "container " << ++index;
  }

  for(int i = 0; i < (int)_containerIndices.size(); i++)
  {
    int      containerSize = (int)_containerIndices[i].size();
    double** domains       = new double*[containerSize];
    int*     bins          = new int[containerSize];
    for(int i = 0; i < containerSize; i++)
    {
      domains[i]    = new double[2];
      domains[i][0] = -1.0;
      domains[i][1] =  1.0;
      bins[i]       = _bins;
    }

    Container *newContainer = new Container(lifeTime, containerSize);

    newContainer->setDomains(domains);
    newContainer->setBinSizes(bins);

    _containers.push_back(newContainer);
  }
  _intermediateFitness = 0.0;
}

void W3irdoNF::evaluationCompleted()
{ }

double W3irdoNF::__entropy(double f)
{
  double r = 0;
  if(_itFactor > 0.0)
  {
    for(vector<Container*>::iterator c = _containers.begin();
        c != _containers.end(); c++)
    {
      Container *d = (*c)->discretise();
      double s = 0.0;
      switch(_measureType)
      {
        case useH:  s = H(d);  break;
        case usePI: s = PI(d); break;
        default:
            cerr << "Unknown measure type: " << _measure << endl;
            break;
      }
      r += _itFactor * s;
      // cout << s << " (" << r << ") ";
      delete d;
    }
    // cout << " -> " << r << endl;
    r = r / (double)_containers.size();
    // cout << " -> " << r << " (" << _itFactor << ", " << _containers.size() << ")" << endl;
    if(_combinationType == ADD)  f += r;
    if(_combinationType == MUL1) f *= 1.0 + r;
    if(_combinationType == MUL)  f *= r;
  }
  return f;
}

// the class factories
extern "C" Evaluate* create()
{
  W3irdoNF *e = new W3irdoNF();
  return (Evaluate*)e;
}

extern "C" void destroy(Evaluate*) {}
