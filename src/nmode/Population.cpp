#include "Population.h"
#include "macros.h"
#include "mutex.h"
#include "Exporter.h"
#include "Data.h"
#include "Convert.h"

#include <math.h>

#include <glog/logging.h>
#include <unistd.h>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/format.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

using namespace boost::gregorian;
namespace fs = boost::filesystem;

#define TAG_GENERATION (char*)"generation"

#ifdef USE_PLPLOT
# include <plplot.h>
# include <plConfig.h>
# include <plevent.h>
#endif // USE_PLPLOT

Population* Population::_me = NULL;

Population::Population(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _generation      = 0;
  _nextIndividual  = 0;
  _individualId    = 0;
  _openEvaluations = 0;
  _me              = this;
  __getUniqueDirectoryName();
  ENP_INIT;
}


Population::~Population()
{
}

void Population::add(ParseElement *element)
{
  VLOG(100) << "parsing " << element->name();
  if(element->closing(TAG_POPULATION))
  {
    current = parent;
  }

  if(element->opening(TAG_POPULATION))
  {
    element->set(TAG_GENERATION, _generation);
    VLOG(100) << "set generation to " << _generation;
  }

  if(element->opening(TAG_INDIVIDUAL))
  {
    VLOG(100) << "found " << TAG_INDIVIDUAL;
    Individual *i = new Individual(this);
    _individuals.push_back(i);
    current = i;
    current->add(element);
  }
}

void Population::createXsd(XsdSpecification *spec)
{
  XsdSequence *_root = new XsdSequence(TAG_POPULATION_DEFINITION);
  _root->add(NA(TAG_GENERATION, TAG_POSITIVE_INTEGER,      false));
  _root->add(NE(TAG_INDIVIDUAL, TAG_INDIVIDUAL_DEFINITION, 1, TAG_XSD_UNBOUNDED));
  spec->add(_root);

  Module::createXsd(spec);
}

Individuals::iterator Population::i_begin()
{
  return _individuals.begin();
}

Individuals::iterator Population::i_end()
{
  return _individuals.end();
}

int Population::i_size()
{
  return _individuals.size();
}

Individuals Population::individuals()
{
  return _individuals;
}

Individual* Population::individual(int index)
{
  return _individuals[index];
}

int Population::generation()
{
  return _generation;
}

void Population::addIndividual(Individual *i)
{
  i->setId(_individualId);
  _individualId++;
  _individuals.push_back(i);
}

bool fnSortByFitness(Individual *a, Individual *b) {return (a->fitness() > b->fitness());}

void Population::sortByFitness()
{
  sort(_individuals.begin(), _individuals.end(), fnSortByFitness);
}

void Population::incGeneration()
{
  _generation++;
  if(EVA->generations() > 0 && _generation > EVA->generations())
  {
    notifyObservers(_m_quit);
    exit(0);
  }
}


void Population::__calculateSelectionProbabilities()
{
  double sum = 0.0;
  double min = _individuals[0]->fitness();
  double rp  = REP->reproductionPressure();
  double max = 0.0;
  vector<double> fitness(_individuals.size());

  FORI(0, _individuals.size(), i) fitness[i] = _individuals[i]->fitness();
  FORI(0, fitness.size(), i)      if(min > fitness[i]) min = fitness[i];
  FORI(0, fitness.size(), i)      fitness[i] -= min;
  FORI(0, fitness.size(), i)      if(fitness[i] > max) max = fitness[i];
  if(max > 0.0)
  {
    FORI(0, fitness.size(), i)    fitness[i] = fitness[i] / max;
    FORI(0, fitness.size(), i)    fitness[i] = pow(fitness[i], rp);
    FORI(0, fitness.size(), i)    sum += fitness[i];
    FORI(0, fitness.size(), i)    _individuals[i]->setReproductionFactor(fitness[i] / sum);
  }
  else
  {
    double f = 1.0/((double)_individuals.size());
    FORI(0, fitness.size(),    i) _individuals[i]->setReproductionFactor(f);
  }
}

Population* Population::instance()
{
  return _me;
}

void Population::resize(int size)
{
  for(int i = size; i < (int)_individuals.size(); i++)
  {
    delete _individuals[i];
  }

  _individuals.resize(size);
}

Individual* Population::getNextIndividual()
{
  ENP_LOCK;

  if(_nextIndividual >= (int)_individuals.size())
  {
    while(_openEvaluations > 0) usleep(500); // wait for the others to complete
    notifyObservers(_m_next_generation);
  }

  Individual *i = _individuals[_nextIndividual];
  _nextIndividual++;
  _openEvaluations++;

  ENP_UNLOCK;
  return i;
}

void Population::evaluationCompleted()
{
  _openEvaluations--;
}

void Population::reproductionCompleted()
{
  _nextIndividual = 0;
  int index = 1;
  FORC(Individuals, i, _individuals) (*i)->setNr(index++);
}

void Population::__getUniqueDirectoryName()
{
  stringstream sst;
  char buf[1024];
  getcwd(buf,1024);
  sst << buf << "/log";
  _logDirectory = sst.str();
  int index = 1;
  string dateString;
  string dirTmp;
  date d(day_clock::local_day());
  dateString = to_iso_extended_string(d);
  stringstream oss;
  oss << _logDirectory << "-" << dateString;
  dirTmp = oss.str();
  _logDirectory = oss.str();
  while(fs::exists(_logDirectory))
  {
    stringstream newOss;
    newOss << dirTmp << "-" << index;
    index++;
    _logDirectory = newOss.str();
  }
  fs::create_directory(_logDirectory);
}

void Population::serialise()
{
  cout << "Generation " << _generation << " completed." << endl;
  stringstream sst;
  sst << _logDirectory << "/" << "generation-" << _generation << ".xml";
  cout << "Logging " << sst.str() << endl;
  VLOG(10) << "opening " << sst.str();
  _output.open(sst.str(), std::ofstream::trunc);
  VLOG(10) << "writing data";
  _output << Data::instance()->xml();
  VLOG(10) << "done writing data";
  _output.close();
  VLOG(10) << "closing " << sst.str();

  sst.str("");
  sst << _logDirectory << "/" << "last_generation.xml";
  // cout << "Logging " << sst.str() << endl;
  VLOG(10) << "opening " << sst.str();
  _output.open(sst.str(), std::ofstream::trunc);
  VLOG(10) << "writing data";
  _output << Data::instance()->xml();
  VLOG(10) << "done writing data";
  _output.close();
  VLOG(10) << "closing " << sst.str();

  sst.str("");
  sst << _logDirectory << "/" << "stats-" << _generation << ".csv";
  // cout << "Logging " << sst.str() << endl;
  _output.open(sst.str(), std::ofstream::trunc);

  _output << "# ID, Fitness, Age, Raw Fitness, "
    << "Node Cost, Edge Cost, Nr. of Neurones, "
    << "Nr. of Syanspes, Nr. of offspring, "
    << "Probability" << endl;

  FORC(Individuals, i, _individuals)
  {
    _output
      << (*i)->id()            << "," << (*i)->fitness()      << "," << (*i)->age()      << ","
      << (*i)->rawFitness()    << "," << (*i)->nodeCost()     << "," << (*i)->edgeCost() << ","
      << (*i)->nrOfNeurons()   << "," << (*i)->nrOfSynapses() << ","
      << (*i)->nrOfOffspring() << "," << (*i)->reproductionFactor()
      << endl;
  }
  _output.close();

#ifdef USE_PLPLOT
  __plotData();
#endif // USE_PLPLOT
}

#ifdef USE_PLPLOT
void Population::__plotData()
{
  Stats stat;

  stat.fitness = _individuals[0]->fitness();

  double m = 0;
  for(int i = 0; i < (int)_individuals.size(); i++) m += _individuals[i]->fitness();
  m /= (double)_individuals.size();

  stat.avgFitness = m;

  double s = 0;
  for(int i = 0; i < (int)_individuals.size(); i++)
  {
    double d = m - _individuals[i]->fitness();
    s += d * d;
  }
  s = sqrt(s);

  stat.sdFitness    = s;
  stat.minSdFitness = m - s;
  stat.maxSdFitness = m + s;

  stat.bestNrHiddenUnits = 0;
  for(Modules::iterator m = _individuals[0]->m_begin(); m != _individuals[0]->m_end(); m++)
  {
    stat.bestNrHiddenUnits += (*m)->h_size();
  }

  stat.avgNrHiddenUnits = 0;
  double i = 0;
  for(Modules::iterator m = _individuals[0]->m_begin(); m != _individuals[0]->m_end(); m++)
  {
    stat.avgNrHiddenUnits += (*m)->h_size();
    i = i + 1.0;
  }
  stat.avgNrHiddenUnits /= i;
  
  stat.sdHiddenUnits = 0;
  for(Modules::iterator m = _individuals[0]->m_begin(); m != _individuals[0]->m_end(); m++)
  {
    double d = stat.avgNrHiddenUnits - (*m)->h_size();
    stat.sdHiddenUnits = d * d;
  }
  stat.sdHiddenUnits = sqrt(stat.sdHiddenUnits);

  stat.minSdHiddenUnits = stat.avgNrHiddenUnits - stat.sdHiddenUnits;
  stat.maxSdHiddenUnits = stat.avgNrHiddenUnits + stat.sdHiddenUnits;

  stat.avgNrEdges = 0;
  i = 0;
  for(Modules::iterator m = _individuals[0]->m_begin(); m != _individuals[0]->m_end(); m++)
  {
    stat.avgNrEdges += (*m)->e_size();
    i = i + 1.0;
  }
  stat.avgNrEdges /= i;
  
  stat.sdEdges = 0;
  for(Modules::iterator m = _individuals[0]->m_begin(); m != _individuals[0]->m_end(); m++)
  {
    double d = stat.avgNrEdges - (*m)->e_size();
    stat.sdEdges = d * d;
  }
  stat.sdEdges = sqrt(stat.sdEdges);

  stat.minSdEdges = stat.avgNrEdges - stat.sdEdges;
  stat.maxSdEdges = stat.avgNrEdges + stat.sdEdges;


  _stats.push_back(stat);

  if(_stats.size() < 2) return;
  plsetopt("dev","pdf");
  plsetopt("geometry","1200x900");
  plsfnam ("stats.pdf");
  plstar( 2, 3 );
  __plotMaxFitness();
  __plotAvgFitness();
  __plotNrHiddenUnits();
  __plotAvgHiddenUnits();
  __plotNrEdges();
  __plotAvgEdges();
  plend();
}

void Population::__plotNrEdges()
{
  PLFLT y[_stats.size()];
  PLFLT x[_stats.size()];

  PLFLT xmin = 0;
  PLFLT xmax = _stats.size()-1;
  PLFLT ymin = 0;
  PLFLT ymax = 1;

  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i].bestNrEdges;
    if(y[i] > ymax) ymax = y[i];
    if(y[i] < ymin) ymin = y[i];
  }

  plenv( xmin, xmax, ymin, ymax, 0, 0 );

  pllab( "generation", "#edges", "Best individual's #edges" );

  // Plot the data that was prepared above.
  plcol0(5);
  plline( (int)_stats.size(), x, y );
  plcol0(1);
}

void Population::__plotAvgEdges()
{
  PLFLT y[_stats.size()];
  PLFLT x[_stats.size()];

  PLFLT xmin = 0;
  PLFLT xmax = _stats.size()-1;
  PLFLT ymin = _stats[0].minSdEdges;
  PLFLT ymax = 1;

  for(int i = 0; i < (int)_stats.size(); i++)
  {
    if(_stats[i].maxSdEdges > ymax) ymax = _stats[i].maxSdEdges;
    if(_stats[i].minSdEdges < ymin) ymin = _stats[i].minSdEdges;
  }

  plenv( xmin, xmax, ymin, ymax, 0, 0 );
  pllab( "generation", "#edges", "Avg. individual's #edges" );

  plcol0(3);
  // plwid(2);
  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i].avgNrEdges;
  }
  plline( (int)_stats.size(), x, y );

  // plwid(1);
  plcol0(4);
  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i].minSdEdges;
  }
  plline( (int)_stats.size(), x, y );

  plcol0(4);
  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i].maxSdEdges;
  }
  plline( (int)_stats.size(), x, y );
  plcol0(1);
}

void Population::__plotNrHiddenUnits()
{
  PLFLT y[_stats.size()];
  PLFLT x[_stats.size()];

  PLFLT xmin = 0;
  PLFLT xmax = _stats.size()-1;
  PLFLT ymin = 0;
  PLFLT ymax = 1;

  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i].bestNrHiddenUnits;
    if(y[i] > ymax) ymax = y[i];
    if(y[i] < ymin) ymin = y[i];
  }

  plenv( xmin, xmax, ymin, ymax, 0, 0 );

  pllab( "generation", "#hidden units", "Best individual's #hidden" );

  // Plot the data that was prepared above.
  plcol0(5);
  plline( (int)_stats.size(), x, y );
  plcol0(1);
}

void Population::__plotAvgHiddenUnits()
{
  PLFLT y[_stats.size()];
  PLFLT x[_stats.size()];

  PLFLT xmin = 0;
  PLFLT xmax = _stats.size()-1;
  PLFLT ymin = _stats[0].minSdHiddenUnits;
  PLFLT ymax = 1;

  for(int i = 0; i < (int)_stats.size(); i++)
  {
    if(_stats[i].maxSdHiddenUnits > ymax) ymax = _stats[i].maxSdHiddenUnits;
    if(_stats[i].minSdHiddenUnits < ymin) ymin = _stats[i].minSdHiddenUnits;
  }

  plenv( xmin, xmax, ymin, ymax, 0, 0 );
  pllab( "generation", "#hidden units", "Avg. individual's #hidden units" );

  plcol0(3);
  // plwid(2);
  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i].avgNrHiddenUnits;
  }
  plline( (int)_stats.size(), x, y );

  // plwid(1);
  plcol0(4);
  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i].minSdHiddenUnits;
  }
  plline( (int)_stats.size(), x, y );

  plcol0(4);
  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i].maxSdHiddenUnits;
  }
  plline( (int)_stats.size(), x, y );
  plcol0(1);
}

void Population::__plotAvgFitness()
{
  PLFLT y[_stats.size()];
  PLFLT x[_stats.size()];

  PLFLT xmin = 0;
  PLFLT xmax = _stats.size()-1;
  PLFLT ymin = _stats[0].minSdFitness;
  PLFLT ymax = _stats[0].maxSdFitness;

  for(int i = 0; i < (int)_stats.size(); i++)
  {
    if(_stats[i].maxSdFitness > ymax) ymax = _stats[i].maxSdFitness;
    if(_stats[i].minSdFitness < ymin) ymin = _stats[i].minSdFitness;
  }

  plenv( xmin, xmax, ymin, ymax, 0, 0 );
  pllab( "generation", "fitness", "Avg. individual's fitness" );

  plcol0(3);
  // plwid(2);
  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i].avgFitness;
  }
  plline( (int)_stats.size(), x, y );

  // plwid(1);
  plcol0(4);
  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i].minSdFitness;
  }
  plline( (int)_stats.size(), x, y );

  plcol0(4);
  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i].maxSdFitness;
  }
  plline( (int)_stats.size(), x, y );
  plcol0(1);
}

void Population::__plotMaxFitness()
{
  PLFLT y[_stats.size()];
  PLFLT x[_stats.size()];

  PLFLT xmin = 0;
  PLFLT xmax = _stats.size()-1;
  PLFLT ymin = _stats[0].fitness;
  PLFLT ymax = _stats[1].fitness;

  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i].fitness;
    if(y[i] > ymax) ymax = y[i];
    if(y[i] < ymin) ymin = y[i];
  }

  plenv( xmin, xmax, ymin, ymax, 0, 0 );

  pllab( "generation", "fitness", "Best individual's fitness" );

  // Plot the data that was prepared above.
  plcol0(1);
  plline( (int)_stats.size(), x, y );
  plcol0(1);
}
#endif // USE_PLPLOT

void Population::incAge()
{
  FORC(Individuals, i, _individuals) (*i)->incAge();
}

void Population::calculateNrOfOffspring()
{
  __calculateSelectionProbabilities();
  int populationSize = REP->populationSize() - _individuals.size();
  if(populationSize <= 0)
  {
    cout << "No offspring will be generated!" << endl;
    return;
  }
  FORC(Individuals, i, _individuals)
  {
    int offspring = (int)((*i)->reproductionFactor() * populationSize + 0.5);
    (*i)->setNrOfOffspring(offspring);
  }
}

void Population::cleanup()
{
  FORC(Individuals, i, _individuals) delete (*i);
  _individuals.clear();
}

void Population::removeCurrentLogDir()
{
  fs::remove_all(_logDirectory);
}

void Population::setCurrentLogDir(string dir)
{
  _logDirectory = dir;
}

void Population::setGeneration(int g)
{
  _generation = g;
}

void Population::plotLast()
{
  cout << "converting " << _logDirectory << endl;
  Convert::convertIndividual(_individuals[0]);
  // system("open out.html");
}
