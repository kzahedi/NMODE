#include "ENP.h"
#include "XmlChangeLog.h"

#include "StringTokeniser.h"
#include "ENPErrorHandler.h"
#include "Individual.h"

#include <iostream>
#include <glog/logging.h>

using namespace std;

# define TAG_VERSION            (char*)"version"
# define TAG_VERSION_DEFINITION (char*)"version_definition"

ENP::ENP(XsdParseNode *parent)
  : XsdParseNode(parent)
{

#include "ChangeLog.h" // do not move from here
  
  _evolution               = NULL;
  _configuration           = NULL;
  _simulator               = NULL;
  _population              = NULL;
  _initialisationCompleted = false;
}

ENP::~ENP()
{
  // nothing to be done
}

void ENP::add(ParseElement *element)
{
  if(current == NULL) current = this;
  if(current == this)
  {
    __getChild(element);
  }
  else
  {
    current->add(element);
  }

}

Version ENP::version()
{
  return _version;
}

void ENP::setVersion(Version version)
{
  _version = version;
}

void ENP::createXsd(XsdSpecification *spec)
{
  XsdSequence *_root = new XsdSequence(TAG_ENP);
  _root->add(NA(TAG_VERSION,       TAG_VERSION_DEFINITION,       true));
  _root->add(NE(TAG_SIMULATOR,     TAG_SIMULATOR_DEFINITION,     1, 1));
  _root->add(NE(TAG_EVALUATION,    TAG_EVALUATION_DEFINITION,    1, 1));
  _root->add(NE(TAG_REPRODUCTION,  TAG_REPRODUCTION_DEFINITION,  1, 1));
  _root->add(NE(TAG_EVOLUTION,     TAG_EVOLUTION_DEFINITION,     1, 1));
  _root->add(NE(TAG_CONFIGURATION, TAG_CONFIGURATION_DEFINITION, 1, 1));
  _root->add(NE(TAG_POPULATION,    TAG_POPULATION_DEFINITION   , 0, 1));
  spec->setRoot(_root);

  XsdRegularExpression *versionDefinition =
    new XsdRegularExpression(TAG_VERSION_DEFINITION,
        TAG_XSD_STRING, TAG_VERSION_REGULAR_EXPRESSION);
  spec->add(versionDefinition);

  Evolution::createXsd(spec);
  Evaluation::createXsd(spec);
  DataConfiguration::createXsd(spec);
  Population::createXsd(spec);
  CfgReproduction::createXsd(spec);
}


void ENP::__getChild(ParseElement *element)
{
  VLOG(100) << "parsing: " << element->name();
  if(element->opening(TAG_ENP))
  {
    string v;
    element->set(TAG_VERSION, v);
    std::vector<string> vs = StringTokeniser::tokenise(v, ".");
    _version.major = atoi(vs[0].c_str());
    _version.minor = atoi(vs[1].c_str());
    _version.patch = atoi(vs[2].c_str());
    if(_version > XmlChangeLog::version())
    {
      ENPErrorHandler *e = ENPErrorHandler::instance();
      (*e).precision(1);
      (*e).setf(ios::fixed,ios::floatfield);
      (*e) << "XML version mismatch. The given XML is of version ";
      (*e) << _version << " but this nmode binary only supports XML version ";
      (*e) << XmlChangeLog::version() << endl;
      (*e).unsetf(ios::floatfield);
      ENPErrorHandler::push();
      exit(-1);
    }
    if(_version < XmlChangeLog::version() && _version < XmlChangeLog::last_crucial_change())
    {
      ENPErrorHandler *e = ENPErrorHandler::instance();
      (*e).precision(1);
      (*e).setf(ios::fixed,ios::floatfield);
      (*e) << "XML version mismatch" << endl;
      (*e) << "Showing differences from your XML’s version ";
      (*e) << _version << " to the current version ";
      (*e) << XmlChangeLog::version() << ":" << endl;
      (*e) << XmlChangeLog::changes(_version);
      (*e).unsetf(ios::floatfield);
      ENPErrorHandler::push();
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
      cout.unsetf(ios::floatfield);
    }
    return;
  }

  if(element->opening(TAG_EVOLUTION))
  {
    _evolution = new Evolution(this);
    current = _evolution;
    current->add(element);
  }

  if(element->opening(TAG_CONFIGURATION))
  {
    _configuration = new DataConfiguration(this);
    current = _configuration;
    current->add(element);
  }

  if(element->opening(TAG_SIMULATOR))
  {
    _simulator = new Simulator(this);
    current = _simulator;
    current->add(element);
  }

  if(element->opening(TAG_EVALUATION))
  {
    _evaluation = new Evaluation(this);
    current = _evaluation;
    current->add(element);
  }

  if(element->opening(TAG_POPULATION) && _initialisationCompleted == false)
  {
    _population = new Population(this);
    current = _population;
    current->add(element);
    _initialisationCompleted = true;
  }

  if(element->opening(TAG_REPRODUCTION))
  {
    _reproduction = new CfgReproduction(this);
    current = _reproduction;
    current->add(element);
  }

}

Evolution* ENP::evolution()
{
  return _evolution;
}

DataConfiguration* ENP::configuration()
{
  return _configuration;
}

Simulator* ENP::simulator()
{
  return _simulator;
}

Population* ENP::population()
{
  return _population;
}

void ENP::initialiseFirstPopulationFromConfiguration()
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
    throw ENPException("Population: Trying to initialise a non empty population.");
  }
}


Evaluation* ENP::evaluation()
{
  return _evaluation;
}


CfgReproduction* ENP::reproduction()
{
  return _reproduction;
}
