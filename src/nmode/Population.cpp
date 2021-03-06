#include <nmode/Population.h>
#include <nmode/macros.h>
#include <nmode/mutex.h>
#include <nmode/Exporter.h>
#include <nmode/Data.h>
#include <nmode/Convert.h>
#include <nmode/StringTokeniser.h>
#include <nmode/Timer.h>

#include <math.h>
#include <stdlib.h>

#include <glog/logging.h>
#include <unistd.h>
#include <regex>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/format.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/regex.hpp>

using namespace boost::gregorian;
namespace fs = boost::filesystem;

#define TAG_GENERATION (char*)"generation"

#ifdef USE_PLPLOT
# include <plplot.h>
# include <plConfig.h>
# include <plevent.h>

static PLFLT pos[]   = { 0.0, 0.25, 0.5, 0.75, 1.0 };
static PLFLT red[]   = { 0.0, 0.25, 0.5, 1.0, 1.0 };
static PLFLT green[] = { 1.0, 0.5, 0.5, 0.5, 1.0 };
static PLFLT blue[]  = { 1.0, 1.0, 0.5, 0.25, 0.0 };
#endif // USE_PLPLOT

Population* Population::_me = NULL;

Population::Population(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  reset();
  _me         = this;
  _generation = 0;
  _ext        = Data::instance()->specification()->evaluation()->logFileType();
  _keepLogs   = Data::instance()->specification()->evaluation()->keepLogs();
  __getUniqueDirectoryName();
  ENP_INIT;
}


Population::~Population()
{
}

void Population::reset()
{
  _nextIndividual  = 0;
  _individualId    = 0;
  _openEvaluations = 0;
  _start           = 0;
  _end             = 0;
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

void Population::i_resize(int s)
{
  return _individuals.resize(s);
}

void Population::i_remove(Individual* i)
{
  FORC(Individuals, c, _individuals)
  {
    if((*c)->id() == i->id())
    {
      _individuals.erase(c);
      return;
    }
  }
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


Population* Population::instance()
{
  if(_me == NULL) _me = new Population();
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


  if(Data::instance()->changed() == false)
  {
    while(_individuals[_nextIndividual]->isEvaluated()) _nextIndividual++;
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
  if(_start > 0)
  {
    _end = Timer::getTime();
    double elapsed_secs = double(_end - _start) / 1000.0;
    cout << "Elapsed time: " << elapsed_secs << "s" << endl;
  }
  _start = Timer::getTime();

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
  // fs::create_directory(_logDirectory);
}

void Population::serialise()
{

  sortByFitness();

  if(boost::filesystem::exists(fs::path(_logDirectory)) == false)
  {
    fs::create_directory(_logDirectory);
  }

  Stats *s = new Stats(_individuals);
  _stats.push_back(s);
  cout << "Generation " << _generation << " completed." << endl;
  stringstream sst;
  sst << _logDirectory << "/" << "generation-" << _generation << ".xml";
  // cout << "Logging " << sst.str() << endl;
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
      << (*i)->nrOfNeurons()   << "," << (*i)->nrOfSynapses()
      << endl;
  }
  _output.close();

  if(_individuals[0]->getFitnessComponents().size() > 0)
  {
    sst.str("");
    sst << _logDirectory << "/" << "fitness-components-" << _generation << ".csv";
    // cout << "Logging " << sst.str() << endl;
    _output.open(sst.str(), std::ofstream::trunc);
    vector<string> fcn = _individuals[0]->getFitnessComponentNames();
    if(fcn.size() > 0)
    {
      _output << "# ";
      for(int i = 0; i < fcn.size() - 1; i++)
      {
        _output << fcn[i] << ", ";
      }
      _output << fcn[fcn.size()-1] << endl;
    }
    FORC(Individuals, i, _individuals)
    {
      vector<double> fc = (*i)->getFitnessComponents();
      for(int i = 0; i < fc.size() - 1; i++)
      {
        _output << fc[i] << ", ";
      }
      _output << fc[fc.size()-1] << endl;
    }
    _output.close();
  }


#ifdef USE_PLPLOT
  __plotData();
#endif // USE_PLPLOT
}

#ifdef USE_PLPLOT
void Population::__plotData()
{
  if(_stats.size() < 2) return;
  stringstream sst;

  if(_keepLogs)
  {
    sst << _logDirectory << "/" << "stats-" << _generation << "." << _ext;
    plsetopt("dev",_ext.c_str());
    plsetopt("geometry","1800x1200");
    plsfnam (sst.str().c_str());
    plstar( 2, 3 );
    __plotMaxFitness();
    __plotAvgFitness();
    __plotNrHiddenUnits();
    __plotAvgHiddenUnits();
    __plotNrEdges();
    __plotAvgEdges();
    plend();
  }

  sst.str("");
  sst << _logDirectory << "/" << "stats." << _ext;
  plsetopt("dev",_ext.c_str());
  plsetopt("geometry","1800x1200");
  plsfnam (sst.str().c_str());
  plstar( 2, 3 );
  __plotMaxFitness();
  __plotAvgFitness();
  __plotNrHiddenUnits();
  __plotAvgHiddenUnits();
  __plotNrEdges();
  __plotAvgEdges();
  plend();

  if(_keepLogs)
  {
    plsetopt("dev",_ext.c_str());
    plsetopt("geometry","1800x400");
    sst.str("");
    sst << _logDirectory << "/" << "fitness-" << _generation << "." << _ext;
    plsfnam (sst.str().c_str());
    plstar( 2, 1 );
    __plotNrOfOffspring();
    __plotFitness();
    plend();
  }

  sst.str("");
  sst << _logDirectory << "/" << "fitness." << _ext;
  plsetopt("dev",_ext.c_str());
  plsetopt("geometry","1800x400");
  plsfnam (sst.str().c_str());
  plstar( 2, 1 );
  __plotNrOfOffspring();
  __plotFitness();
  plend();
}

void Population::__plfbox( PLFLT x0, PLFLT y0 )
{
    PLFLT x[4], y[4];

    x[0] = x0;
    y[0] = 0.;
    x[1] = x0;
    y[1] = y0;
    x[2] = x0 + 1.;
    y[2] = y0;
    x[3] = x0 + 1.;
    y[3] = 0.;
    plfill( 4, x, y );
    plcol0( 1 );
    pllsty( 1 );
    plline( 4, x, y );
}

void Population::__plotFitness()
{
  double max = _individuals[0]->fitness();
  double min = _individuals[0]->fitness();
  for(int i = 1; i < (int)_individuals.size(); i++)
  {
    double m = _individuals[i]->fitness();
    if(m > max) max = m;
    if(m < min) min = m;
  }
  if(max < 0.0) max = 0.0;
  if(min > 0.0) min = 0.0;

  plcol0(4);
  plscmap1l( 1, 5, pos, red, green, blue, NULL );
  plenv( 0, _individuals.size(), 1.1 * min, 1.1 * max, 0, -1 );
  pllab("", "", "Fitness");

  float delta = 1.0/(float)(_individuals.size());
  int index = 0;
  char string[100];
  for(int i = 0; i < (int)_individuals.size(); i++)
  {
    plcol1( ((float)i) / ((float)_individuals.size()));
    plpsty( 0 );
    __plfbox( i, _individuals[i]->fitness());
    sprintf( string, "%.2f", _individuals[i]->fitness());
    plmtex( "b", 1.0, ( ( i + 1 ) * delta - .5 * delta ), 0.5, string );
  }
}

void Population::__plotNrOfOffspring()
{
  int max = 0;
  for(int i = 0; i < (int)_individuals.size(); i++)
  {
    int m = _individuals[i]->nrOfOffspring();
    if(m > max) max = m;
  }

  plcol0(4);
  plscmap1l(1, 5, pos, red, green, blue, NULL);
  // plbox("b", 10000.0, 0, "b", (float)_individuals.size(), 10000.0);
  plenv(0, _individuals.size(), 0, ((float)max) * 1.1, 0, -1);
  pllab("", "", "Nr. of offspring");

  float delta = 1.0/(float)(_individuals.size());
  int index = 0;
  char string[100];
  // plssym(12.0, 1.0);
  for(int i = 0; i < (int)_individuals.size(); i++)
  {
    //plcol0(i + 1);
    plcol1( ((float)i) / ((float)_individuals.size()));
    plpsty(0);
    __plfbox(i, _individuals[i]->nrOfOffspring());
    sprintf(string, "%d", _individuals[i]->nrOfOffspring());
    // plptex((i + .5), 1.5, 1.0, 0.0, .5, string);
    // sprintf(string, "%d", i+1);
    plmtex("b", 1.0, ((i + 1) * delta - .5 * delta), 0.5, string);
  }
  // plssym(12.0, 1.0);
}


void Population::__plotNrEdges()
{
  plcol0(4);
  PLFLT y[_stats.size()];
  PLFLT x[_stats.size()];

  PLFLT xmin = 0;
  PLFLT xmax = _stats.size()-1;
  PLFLT ymin = 0;
  PLFLT ymax = 1;

  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i]->bestNrEdges();
    if(y[i] > ymax) ymax = y[i];
    if(y[i] < ymin) ymin = y[i];
  }

  plenv( xmin, xmax, ymin, ymax, 0, 0 );

  pllab( "generation", "#edges", "Best individual's #edges" );

  // Plot the data that was prepared above.
  plline( (int)_stats.size(), x, y );
}

void Population::__plotAvgEdges()
{
  plcol0(4);
  PLFLT y[_stats.size()];
  PLFLT x[_stats.size()];

  PLFLT xmin = 0;
  PLFLT xmax = _stats.size()-1;
  PLFLT ymin = _stats[0]->minSdEdges();
  PLFLT ymax = 1;

  for(int i = 0; i < (int)_stats.size(); i++)
  {
    if(_stats[i]->maxSdEdges() > ymax) ymax = _stats[i]->maxSdEdges();
    if(_stats[i]->minSdEdges() < ymin) ymin = _stats[i]->minSdEdges();
  }

  plenv( xmin, xmax, ymin, ymax, 0, 0 );
  pllab( "generation", "#edges", "Avg. individual's #edges" );

  plcol0(4);
  // plwid(2);
  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i]->avgNrEdges();
  }
  plline( (int)_stats.size(), x, y );

  // plwid(1);
  plcol0(3);
  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i]->minSdEdges();
  }
  plline( (int)_stats.size(), x, y );

  plcol0(3);
  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i]->maxSdEdges();
  }
  plline( (int)_stats.size(), x, y );
}

void Population::__plotNrHiddenUnits()
{
  plcol0(4);
  PLFLT y[_stats.size()];
  PLFLT x[_stats.size()];

  PLFLT xmin = 0;
  PLFLT xmax = _stats.size()-1;
  PLFLT ymin = 0;
  PLFLT ymax = 1;

  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i]->bestNrHiddenUnits();
    if(y[i] > ymax) ymax = y[i];
    if(y[i] < ymin) ymin = y[i];
  }

  plenv( xmin, xmax, ymin, ymax, 0, 0 );

  pllab( "generation", "#hidden units", "Best individual's #hidden" );

  // Plot the data that was prepared above.
  plline( (int)_stats.size(), x, y );
}

void Population::__plotAvgHiddenUnits()
{
  plcol0(4);
  PLFLT y[_stats.size()];
  PLFLT x[_stats.size()];

  PLFLT xmin = 0;
  PLFLT xmax = _stats.size()-1;
  PLFLT ymin = _stats[0]->minSdHiddenUnits();
  PLFLT ymax = 1;

  for(int i = 0; i < (int)_stats.size(); i++)
  {
    if(_stats[i]->maxSdHiddenUnits() > ymax) ymax = _stats[i]->maxSdHiddenUnits();
    if(_stats[i]->minSdHiddenUnits() < ymin) ymin = _stats[i]->minSdHiddenUnits();
  }

  plenv( xmin, xmax, ymin, ymax, 0, 0 );
  pllab( "generation", "#hidden units", "Avg. individual's #hidden units" );

  plcol0(4);
  // plwid(2);
  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i]->avgNrHiddenUnits();
  }
  plline( (int)_stats.size(), x, y );

  // plwid(1);
  plcol0(4);
  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i]->minSdHiddenUnits();
  }
  plline( (int)_stats.size(), x, y );

  plcol0(4);
  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i]->maxSdHiddenUnits();
  }
  plline( (int)_stats.size(), x, y );
}

void Population::__plotAvgFitness()
{
  plcol0(4);
  PLFLT y[_stats.size()];
  PLFLT x[_stats.size()];

  PLFLT xmin = 0;
  PLFLT xmax = _stats.size()-1;
  PLFLT ymin = _stats[0]->minSdFitness();
  PLFLT ymax = _stats[0]->maxSdFitness();

  for(int i = 0; i < (int)_stats.size(); i++)
  {
    if(_stats[i]->maxSdFitness() > ymax) ymax = _stats[i]->maxSdFitness();
    if(_stats[i]->minSdFitness() < ymin) ymin = _stats[i]->minSdFitness();
  }

  plenv( xmin, xmax, ymin, ymax, 0, 0 );
  pllab( "generation", "fitness", "Avg. individual's fitness" );

  plcol0(4);
  // plwid(2);
  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i]->avgFitness();
  }
  plline( (int)_stats.size(), x, y );

  // plwid(1);
  plcol0(3);
  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i]->minSdFitness();
  }
  plline( (int)_stats.size(), x, y );

  plcol0(3);
  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i]->maxSdFitness();
  }
  plline( (int)_stats.size(), x, y );
}

void Population::__plotMaxFitness()
{
  plcol0(4);
  PLFLT y[_stats.size()];
  PLFLT x[_stats.size()];

  PLFLT xmin = 0;
  PLFLT xmax = _stats.size()-1;
  PLFLT ymin = _stats[0]->bestFitness();
  PLFLT ymax = _stats[0]->bestFitness();

  for(int i = 0; i < (int)_stats.size(); i++)
  {
    x[i] = i;
    y[i] = (PLFLT)_stats[i]->bestFitness();
    if(y[i] > ymax) ymax = y[i];
    if(y[i] < ymin) ymin = y[i];
  }

  plenv( xmin, xmax, ymin, ymax, 0, 0 );

  pllab( "generation", "fitness", "Best individual's fitness" );

  // Plot the data that was prepared above.
  plline( (int)_stats.size(), x, y );
}
#endif // USE_PLPLOT

void Population::incAge()
{
  FORC(Individuals, i, _individuals) (*i)->incAge();
}

void Population::cleanup()
{
  FORC(Individuals, i, _individuals) delete (*i);
  _individuals.clear();
  reset();
  _generation = 0;
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
  // cout << "converting " << _logDirectory << endl;
  Convert::convertIndividual(_individuals[0]);
  // system("open out.html");
}


void Population::readStats(string d)
{
  _stats.clear();
  fs::path dir(d);
  boost::regex rgx("stats-(\\d+)\\.csv");
  vector<fs::path> files;

  if(!fs::exists(dir) || !fs::is_directory(dir)) return;

  fs::recursive_directory_iterator it(dir);
  fs::recursive_directory_iterator endit;

  while(it != endit)
  {
    if(fs::is_regular_file(*it))
    {
      string s = it->path().filename().string();
      if(boost::regex_match(s, rgx))
      {
        files.push_back(it->path().filename());
      }
    }
    ++it;
  }


  vector<int> indices;

  for(vector<fs::path>::iterator i = files.begin(); i != files.end(); i++)
  {
    string t = (*i).string();
    string s = boost::regex_replace(t,
                                    boost::regex("stats-([0-9]+).csv"),
                                    string("\\1")
                                   );
    indices.push_back(atoi(s.c_str()));
  }

  std::sort (indices.begin(), indices.end());

  _stats.clear();
  stringstream sst;
  int index = 1;
  for(vector<int>::iterator i = indices.begin(); i != indices.end(); i++)
  {
    sst.str("");
    sst << dir.string() << "/stats-" << (index++) << ".csv";
    std::ifstream input(sst.str());
    std::string line;
    getline(input, line); // first line is comments
    vector<double> fitness;
    // vector<double> age;
    // vector<double> rawfitness;
    // vector<double> nodecost;
    // vector<double> edgecost;
    vector<double> nrneurons;
    vector<double> nrsynapses;
    // vector<double> offspring;
    for(;getline( input, line );)
    {
      vector<string> toks = StringTokeniser::tokenise(line, ",");
      fitness.push_back(atof(toks[1].c_str()));
      // age.push_back(atof(toks[2].c_str()));
      // rawfitness.push_back(atof(toks[3].c_str()));
      // nodecost.push_back(atof(toks[4].c_str()));
      // edgecost.push_back(atof(toks[5].c_str()));
      nrneurons.push_back(atof(toks[6].c_str()));
      nrsynapses.push_back(atof(toks[7].c_str()));
      // cout << toks[1] << " " << toks[6] << " " << toks[7] << endl;
      // nroffspring.push_back(atof(toks[8].c_str()));
    }
    input.close();

    double bestFitness       = fitness[0];
    double bestNrHiddenUnits = nrneurons[0];
    double bestNrEdges       = nrsynapses[0];

    double avgFitness        = __mean(fitness);
    double avgNrHiddenUnits  = __mean(nrneurons);
    double avgNrEdges        = __mean(nrsynapses);

    double sdFitness         = __std(fitness);
    double sdHiddenUnits     = __std(nrneurons);
    double sdEdges           = __std(nrsynapses);

    Stats *s = new Stats(bestFitness, avgFitness, sdFitness,
                         bestNrHiddenUnits, avgNrHiddenUnits, sdHiddenUnits,
                         bestNrEdges, avgNrEdges, sdEdges);
    _stats.push_back(s);
  }

}

void Population::setInactive(int module, int node, bool value)
{
  for(Individuals::iterator i = _individuals.begin(); i != _individuals.end(); i++)
  {
    (*i)->module(module)->node(node)->setInactive(value);
  }
}

void Population::removeFirstIndividual()
{
  _individuals.erase(_individuals.begin());
}

double Population::__mean(vector<double> &v)
{
  double s = 0;
  for(vector<double>::iterator i = v.begin(); i != v.end(); i++)
  {
    s += *i;
  }
  return (s / ((float) v.size()));
}

double Population::__std(vector<double> &v)
{
  double m = __mean(v);
  double s = 0;
  for(vector<double>::iterator i = v.begin(); i != v.end(); i++)
  {
    s += (*i - m) * (*i - m);
  }
  return (s / ((float) v.size()));
}

