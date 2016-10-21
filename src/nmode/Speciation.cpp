#include <nmode/Speciation.h>

Speciation::Speciation(double threshold)
{
  _population = Population::instance();
  _threshold  = threshold;

  for(Individuals::iterator i = _population->i_begin(); i != _population->i_end(); i++)
  {
    __add(*i);
  }
}

void Speciation::__add(Individual* individual)
{
  bool assigned = false;

  for(int i = 0; i < (int)_species.size(); i++)
  {
    if(_species[i].size() > 0)
    {
      Individual* representation = _species[i][0];
      double t = __calculateDifference(_species[i][0], individual);
      if(t < _threshold)
      {
        _species[i].push_back(individual);
        assigned = true;
      }
    }
  }
  if(assigned == false)
  {
    Individuals newSpecies;
    newSpecies.push_back(individual);
    _species.push_back(newSpecies);
  }
}
