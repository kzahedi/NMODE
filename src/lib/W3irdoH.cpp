#include "W3irdoH.h"

#include <nmode/RnnFromIndividual.h>
#include <nmode/Data.h>

#include <sstream>

#define MIN3(a,c,b) ((a<b)?((c<a)?c:a):(c<b)?c:b)

W3irdoH::W3irdoH()
  : Evaluate()
{
  networkInput.resize(33);
  _h = new Hs();
}

void W3irdoH::updateController()
{
  for(int i = 0; i < (int)networkInput.size(); i++) networkInput[i] = sensorValues[i];
  for(int i = 0;  i < 5;  i++) (*_l1c) << sensorValues[i];
  for(int i = 5;  i < 10; i++) (*_l2c) << sensorValues[i];
  for(int i = 10; i < 15; i++) (*_l3c) << sensorValues[i];
}

void W3irdoH::updateFitnessFunction()
{
  _x       = sensorValues[31];
  _y       = sensorValues[32];
  _dist    = sqrt(_x * _x + _y * _y);
  fitness += _dist;
}

bool W3irdoH::abort()
{
  return false;
}

void W3irdoH::newIndividual()
{
  EVA->set("bins", _bins, 30);
  if(_l1c != NULL) delete _l1c;
  if(_l2c != NULL) delete _l2c;
  if(_l3c != NULL) delete _l3c;
  _l1c = new Container(lifeTime, 5);
  _l2c = new Container(lifeTime, 5);
  _l3c = new Container(lifeTime, 5);
  double** domains = new double*[5];
  int*     bins    = new int[5];
  for(int i = 0; i < 5; i++)
  {
    domains[i]    = new double[2];
    domains[i][0] = -1.0;
    domains[i][1] =  1.0;
    bins[i]       = _bins;
  }
  _l1c->setDomains(domains);
  _l1c->setBinSizes(bins);
  _l2c->setDomains(domains);
  _l2c->setBinSizes(bins);
  _l3c->setDomains(domains);
  _l3c->setBinSizes(bins);
}

void W3irdoH::evaluationCompleted()
{
  Container *d1 = _l1c->discretise();
  Container *d2 = _l2c->discretise();
  Container *d3 = _l3c->discretise();
  double    r1  = _h->calculate(d1) / log2(_bins);
  double    r2  = _h->calculate(d2) / log2(_bins);
  double    r3  = _h->calculate(d3) / log2(_bins);
  double    r   = r1 + r2 + r3; // MIN3(r1, r2, r3);
  cout << "fitness from " << fitness;
  // fitness      *= 1.0 + r;
  fitness      *= r;
  // fitness      = r1 + r2 + r3;
  cout << " to " << fitness << " (" << r << ")" << endl;

  delete d1;
  delete d2;
  delete d3;
  // cout << "entropies: " << r1 << " " << r2 << " " << r3 << " -> " << r << endl;
}

// the class factories
extern "C" Evaluate* create()
{
  W3irdoH *e = new W3irdoH();
  return (Evaluate*)e;
}

extern "C" void destroy(Evaluate* controller) {}
