#include <nmode/Random.h>

#include <stdlib.h>

#include <iostream>

using namespace std;

void Random::initialise()
{
  time_t t;
  time(&t);
  srand48(t);

  cout << "random initialised:";
  for(int i = 0; i < 10; i++)
  {
    cout << " " << rand(0, 100);
  }
  // cout << endl;
  // cout << "random initialised:";
  // for(int i = 0; i < 10; i++)
  // {
    // cout << " " << unit();
  // }
  // cout << endl;

}

double Random::unit()
{
  return drand48();
}

void Random::initialise(int seed)
{
  srand(seed);
}

int Random::randi(int min, int max)
{
  return min + int(drand48() * (double)(max-min) + 0.5);
}


double Random::rand(double min, double max)
{
  double d = drand48();
  return min + d * (double)(max - min);
  // return min + drand48() * (double)(max - min);
}
