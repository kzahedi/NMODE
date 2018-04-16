#include <nmode/NMODE.h>
#include <nmode/XmlChangeLog.h>

#include <nmode/StringTokeniser.h>
#include <nmode/NMODEErrorHandler.h>
#include <nmode/Individual.h>
#include <nmode/Module.h>
#include <nmode/macros.h>

#include <iostream>
#include <glog/logging.h>

using namespace std;

# define TAG_VERSION            (char*)"version"
# define TAG_VERSION_DEFINITION (char*)"version_definition"

NMODE::NMODE(XsdParseNode *parent)
  : XsdParseNode(parent)
{

#include "ChangeLog.h" // do not move from here

  _simulator     = NULL;
  _mutation      = NULL;
  _configuration = NULL;
  _population    = NULL;
  _evaluation    = NULL;
  _reproduction  = NULL;
  _visualisation = NULL;
  _changed       = false;

  _initialisationCompleted = false;
}

NMODE::~NMODE()
{
  // nothing to be done
}

void NMODE::add(ParseElement *element)
{
  if(current == NULL) current = this;
  if(element->opening(TAG_NMODE)) _changed = false;
  if(element->closing(TAG_NMODE)) _changed = _evaluation->changed();
  if(current == this)
  {
    __getChild(element);
  }
  else
  {
    current->add(element);
  }
}

Version NMODE::version()
{
  return _version;
}

void NMODE::setVersion(Version version)
{
  _version = version;
}

void NMODE::createXsd(XsdSpecification *spec)
{
  XsdSequence *_root = new XsdSequence(TAG_NMODE);
  _root->add(NA(TAG_VERSION,       TAG_VERSION_DEFINITION,       true));
  _root->add(NE(TAG_SIMULATOR,     TAG_SIMULATOR_DEFINITION,     1, 1));
  _root->add(NE(TAG_VISUALISATION, TAG_VISUALISATION_DEFINITION, 1, 1));
  _root->add(NE(TAG_EVALUATION,    TAG_EVALUATION_DEFINITION,    1, 1));
  _root->add(NE(TAG_REPRODUCTION,  TAG_REPRODUCTION_DEFINITION,  1, 1));
  _root->add(NE(TAG_MUTATION,      TAG_MUTATION_DEFINITION,      1, 1));
  _root->add(NE(TAG_CONFIGURATION, TAG_CONFIGURATION_DEFINITION, 1, 1));
  _root->add(NE(TAG_POPULATION,    TAG_POPULATION_DEFINITION,    0, 1));
  spec->setRoot(_root);

  XsdRegularExpression *versionDefinition =
    new XsdRegularExpression(TAG_VERSION_DEFINITION,
        TAG_XSD_STRING, TAG_VERSION_REGULAR_EXPRESSION);
  spec->add(versionDefinition);

  CfgMutation::createXsd(spec);
  CfgVisualisation::createXsd(spec);
  CfgEvaluation::createXsd(spec);
  Configuration::createXsd(spec);
  Population::createXsd(spec);
  CfgReproduction::createXsd(spec);
  Simulator::createXsd(spec);
}


void NMODE::__getChild(ParseElement *element)
{
  VLOG(100) << "parsing: " << element->name();
  if(element->opening(TAG_NMODE))
  {
    string v;
    element->set(TAG_VERSION, v);
    std::vector<string> vs = StringTokeniser::tokenise(v, ".");
    _version.major = atoi(vs[0].c_str());
    _version.minor = atoi(vs[1].c_str());
    _version.patch = atoi(vs[2].c_str());
    if(_version > XmlChangeLog::version())
    {
      NMODEErrorHandler *e = NMODEErrorHandler::instance();
      (*e).precision(1);
      (*e).setf(ios::fixed,ios::floatfield);
      (*e) << "XML version mismatch. The given XML is of version ";
      (*e) << _version << " but this nmode binary only supports XML version ";
      (*e) << XmlChangeLog::version() << endl;
      (*e).unsetf(ios::fixed);
      (*e).unsetf(ios::floatfield);
      NMODEErrorHandler::push();
      exit(-1);
    }
    if(_version < XmlChangeLog::version() && _version < XmlChangeLog::last_crucial_change())
    {
      NMODEErrorHandler *e = NMODEErrorHandler::instance();
      (*e).precision(1);
      (*e).setf(ios::fixed,ios::floatfield);
      (*e) << "XML version mismatch" << endl;
      (*e) << "Showing differences from your XML’s version ";
      (*e) << _version << " to the current version ";
      (*e) << XmlChangeLog::version() << ":" << endl;
      (*e) << XmlChangeLog::changes(_version);
      (*e).unsetf(ios::fixed);
      (*e).unsetf(ios::floatfield);
      NMODEErrorHandler::push();
      exit(-1);
    }
    else if(_version < XmlChangeLog::version())
    {
      cout.precision(1);
      cout.setf(ios::fixed,ios::floatfield);
      cout << "Non-critical XML version mismatch" << endl;
      cout << "Showing differences from your XML’s version ";
      cout << _version << " to the current version ";
      cout << XmlChangeLog::version() << ":" << endl;
      cout << XmlChangeLog::changes(_version);
      cout.unsetf(ios::fixed);
      cout.unsetf(ios::floatfield);
      cout.precision(8);
    }
    return;
  }

  if(element->opening(TAG_MUTATION))
  {
    if(_mutation != NULL) delete _mutation;
    _mutation = new CfgMutation(this);
    current = _mutation;
    current->add(element);
  }

  if(element->opening(TAG_CONFIGURATION))
  {
    if(_configuration != NULL) delete _configuration;
    _configuration = new Configuration(this);
    current = _configuration;
    current->add(element);
  }

  if(element->opening(TAG_SIMULATOR))
  {
    if(_simulator != NULL) delete _simulator;
    _simulator = new Simulator(this);
    current = _simulator;
    current->add(element);
  }

  if(element->opening(TAG_VISUALISATION))
  {
    if(_visualisation != NULL) delete _visualisation;
    _visualisation = new CfgVisualisation(this);
    current = _visualisation;
    current->add(element);
  }

  if(element->opening(TAG_EVALUATION))
  {
    if(_evaluation == NULL) _evaluation = new CfgEvaluation(this);
    current = _evaluation;
    current->add(element);
  }

  if(element->opening(TAG_POPULATION) && _initialisationCompleted == false)
  {
    _population = Population::instance();
    _population->cleanup();
    // _population = new Population(this);
    current = _population;
    current->add(element);
    _initialisationCompleted = true;
  }

  if(element->opening(TAG_REPRODUCTION))
  {
    if(_reproduction != NULL) delete _reproduction;
    _reproduction = new CfgReproduction(this);
    current = _reproduction;
    current->add(element);
  }

  if(element->closing(TAG_NMODE))
  {
    __applyConfigurationToModules();
  }
}

void NMODE::__applyConfigurationToModules()
{
  if(_population == NULL) return;
  FORF(Modules, m, _configuration, m_begin(), m_end())
  {
    FORF(Individuals, i, _population, i_begin(), i_end())
    {
      FORF(Modules, n, (*i), m_begin(), m_end())
      {
        if((*m)->name() == (*n)->name())
        {
          if((*m)->mutation() == NULL)
          {
            (*n)->removeMutation();
          }
          else
          {
            (*n)->setMutation((*m)->mutation()->copy());
          }
        }
      }
    }
  }
}

CfgMutation* NMODE::mutation()
{
  return _mutation;
}

Configuration* NMODE::configuration()
{
  return _configuration;
}

Simulator* NMODE::simulator()
{
  return _simulator;
}

Population* NMODE::population()
{
  return _population;
}

void NMODE::initialiseFirstPopulationFromConfiguration()
{
  if(_population == NULL)
  {
    VLOG(100) << "initialising from specification";
    _population = new Population();
    Individual *ind = new Individual();
    _population->addIndividual(ind);
    for(Modules::iterator m =  _configuration->m_begin(); m != _configuration->m_end(); m++)
    {
      ind->addModule(*m);
    }
  }
  else
  {
    throw NMODEException("Population: Trying to initialise a non empty population.");
  }
}


CfgEvaluation* NMODE::evaluation()
{
  return _evaluation;
}

CfgReproduction* NMODE::reproduction()
{
  return _reproduction;
}

CfgVisualisation* NMODE::visualisation()
{
  return _visualisation;
}

void NMODE::setSimulator(Simulator* s)
{
  _simulator = s;
}
void NMODE::setCfgMutation(CfgMutation* m)
{
  _mutation = m;
}

void NMODE::setCfgEvaluation(CfgEvaluation* e)
{
  _evaluation = e;
}

void NMODE::setConfiguration(Configuration* c)
{
  _configuration = c;
}

void NMODE::setPopulation(Population* p)
{
  _population = p;
}

void NMODE::setCfgReproduction(CfgReproduction* r)
{
  _reproduction = r;
}

void NMODE::setCfgVisualisation(CfgVisualisation* v)
{
  _visualisation = v;
}

void NMODE::overrideReadingOfPopulation()
{
  _initialisationCompleted = false;
}

bool NMODE::changed()
{
  return _changed;
}
