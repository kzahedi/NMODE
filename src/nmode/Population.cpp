#include "Population.h"
#include "macros.h"
#include "mutex.h"
#include "Exporter.h"
#include "Data.h"

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
  _output.open(sst.str());
  _output << Data::instance()->xml();
  _output.close();

  sst.str("");
  sst << _logDirectory << "/" << "last_generation.xml";
  // cout << "Logging " << sst.str() << endl;
  _output.open(sst.str());
  _output << Data::instance()->xml();
  _output.close();

  sst.str("");
  sst << _logDirectory << "/" << "stats-" << _generation << ".csv";
  // cout << "Logging " << sst.str() << endl;
  _output.open(sst.str());

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
}

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

