#include "W3irdoPI.h"

#include <nmode/RnnFromIndividual.h>
#include <nmode/Data.h>

#include <sstream>

W3irdoPI::W3irdoPI()
  : Evaluate()
{
  networkInput.resize(2);
  _pi = new PIs();
}

void W3irdoPI::updateController()
{
  for(int i = 0; i < (int)networkInput.size(); i++) networkInput[i] = sensorValues[i];
  for(int i = 0;  i < 5;  i++) (*_l1c) << sensorValues[i];
  for(int i = 5;  i < 10; i++) (*_l2c) << sensorValues[i];
  for(int i = 10; i < 15; i++) (*_l3c) << sensorValues[i];
}

void W3irdoPI::updateFitnessFunction()
{
  _x       = sensorValues[31];
  _y       = sensorValues[32];
  _dist    = sqrt(_x * _x + _y * _y);
  fitness += _dist;
}

bool W3irdoPI::abort()
{
  return false;
}

void W3irdoPI::newIndividual()
{
  int b = 30;
  EVA->set("bins", b, 30);
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
    bins[i]       =  b;
  }
  _l1c->setDomains(domains);
  _l1c->setBinSizes(bins);
  _l2c->setDomains(domains);
  _l2c->setBinSizes(bins);
  _l3c->setDomains(domains);
  _l3c->setBinSizes(bins);
}

void W3irdoPI::evaluationCompleted()
{
  // cout << "discretising data" << endl;
  Container *d1 = _l1c->discretise();
  Container *d2 = _l2c->discretise();
  Container *d3 = _l3c->discretise();
  // cout << *_container << endl;
  cout << "1 min/max: " << _l1c->min() << " " << _l1c->max() << endl;
  cout << "2 min/max: " << _l2c->min() << " " << _l2c->max() << endl;
  cout << "3 min/max: " << _l3c->min() << " " << _l3c->max() << endl;
  double r1 = _pi->calculate(d1); delete d1;
  double r2 = _pi->calculate(d2); delete d2;
  double r3 = _pi->calculate(d3); delete d3;
  cout << "pi: " << r1 << " " << r2 << " " << r3 << endl;
  // fitness *= (1.0 + r1 + r2 + r3);
  fitness = r1 + r2 + r3;
}

// the class factories
extern "C" Evaluate* create()
{
  W3irdoPI *e = new W3irdoPI();
  return (Evaluate*)e;
}

extern "C" void destroy(Evaluate* controller) {}
