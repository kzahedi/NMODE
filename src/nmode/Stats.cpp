#include <nmode/Stats.h>

Stats::Stats(const Individuals& individuals)
{
  __bestFitness(individuals);
  __avgFitness(individuals);
  __sdFitness(individuals);

  __bestHidden(individuals);
  __avgHidden(individuals);
  __sdHidden(individuals);

  __bestEdges(individuals);
  __avgEdges(individuals);
  __sdEdges(individuals);
}


void Stats::__bestFitness(const Individuals& individuals)
{
  _bestFitness = individuals[0]->fitness();
}

void Stats::__avgFitness(const Individuals& individuals)
{
  _avgFitness = 0.0;
  for(int i = 0; i < (int)individuals.size(); i++)
    _avgFitness += individuals[i]->fitness();
  _avgFitness /= (double)individuals.size();
}

void Stats::__sdFitness(const Individuals& individuals)
{
  double s = 0;
  for(int i = 0; i < (int)individuals.size(); i++)
  {
    double d = _avgFitness - individuals[i]->fitness();
    s += d * d;
  }
  s = sqrt(s);

  _sdFitness    = s;
  _minSdFitness = _avgFitness - s;
  _maxSdFitness = _avgFitness + s;
}

////////////////////////////////////////////////////////////////////////////////
// Hidden
////////////////////////////////////////////////////////////////////////////////

void Stats::__bestHidden(const Individuals& individuals)
{
  _bestNrHiddenUnits = 0;
  for(Modules::iterator m = individuals[0]->m_begin(); m != individuals[0]->m_end(); m++)
  {
    _bestNrHiddenUnits = (*m)->h_size();
  }
}

void Stats::__avgHidden(const Individuals& individuals)
{
  _avgNrHiddenUnits = 0.0;
  for(Individuals::const_iterator i = individuals.begin(); i != individuals.end(); i++)
  {
    for(Modules::iterator m = (*i)->m_begin(); m != (*i)->m_end(); m++)
    {
      _avgNrHiddenUnits += (*m)->h_size();
    }
  }
  _avgNrHiddenUnits /= (double)(individuals.size());
}

void Stats::__sdHidden(const Individuals& individuals)
{
  _sdHiddenUnits = 0.0;
  for(Individuals::const_iterator i = individuals.begin(); i != individuals.end(); i++)
  {
    double avg = 0.0;
    for(Modules::iterator m = (*i)->m_begin(); m != (*i)->m_end(); m++)
    {
      avg = (*m)->h_size();
    }
    avg /= (double)(*i)->m_size();
    double d = avg - _avgNrHiddenUnits;
    _sdHiddenUnits += d * d;
  }
  _sdHiddenUnits = sqrt(_sdHiddenUnits);
  _minSdHiddenUnits = _avgNrHiddenUnits - _sdHiddenUnits;
  _maxSdHiddenUnits = _avgNrHiddenUnits + _sdHiddenUnits;
}

////////////////////////////////////////////////////////////////////////////////
// Hidden
////////////////////////////////////////////////////////////////////////////////

void Stats::__bestEdges(const Individuals& individuals)
{
  _bestNrEdges = 0;
  for(Modules::iterator m = individuals[0]->m_begin(); m != individuals[0]->m_end(); m++)
  {
    _bestNrEdges += (*m)->e_size();
  }
}

void Stats::__avgEdges(const Individuals& individuals)
{
  _avgNrEdges = 0.0;
  for(Individuals::const_iterator i = individuals.begin(); i != individuals.end(); i++)
  {
    for(Modules::iterator m = (*i)->m_begin(); m != (*i)->m_end(); m++)
    {
      _avgNrEdges += (*m)->e_size();
    }
  }
  _avgNrEdges /= (double)(individuals.size());
}

void Stats::__sdEdges(const Individuals& individuals)
{
  _sdEdges = 0.0;
  for(Individuals::const_iterator i = individuals.begin(); i != individuals.end(); i++)
  {
    double avg = 0.0;
    for(Modules::iterator m = (*i)->m_begin(); m != (*i)->m_end(); m++)
    {
      avg = (*m)->h_size();
    }
    double d = avg - _avgNrEdges;
    _sdEdges += d * d;
  }
  _sdEdges = sqrt(_sdEdges);
  _minSdEdges = _avgNrEdges - _sdEdges;
  _maxSdEdges = _avgNrEdges + _sdEdges;
}

