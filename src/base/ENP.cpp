#include "ENP.h"
#include "XmlChangeLog.h"

#include "base/StringTokeniser.h"
#include "base/ENPErrorHandler.h"

#include <iostream>
#include <glog/logging.h>

using namespace std;

# define TAG_VERSION            (char*)"version"
# define TAG_VERSION_DEFINITION (char*)"version_definition"

ENP::ENP(XsdParseNode *parent)
  : XsdParseNode(parent)
{

#include "ChangeLog.h" // do not move from here
  
  _evolution     = NULL;
  _configuration = NULL;
  _simulator     = NULL;
  _population    = NULL;

}

ENP::~ENP()
{
  // nothing to be done
}


void ENP::add(DataParseElement *element)
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
  _root->add(NE(TAG_EVOLUTION,     TAG_EVOLUTION_DEFINITION,     1, 1));
  _root->add(NE(TAG_CONFIGURATION, TAG_CONFIGURATION_DEFINITION, 1, 1));
  _root->add(NE(TAG_POPULATION,    TAG_POPULATION_DEFINITION   , 0, 1));
  spec->setRoot(_root);

  XsdRegularExpression *versionDefinition =
    new XsdRegularExpression(TAG_VERSION_DEFINITION,
        TAG_XSD_STRING, TAG_VERSION_REGULAR_EXPRESSION);
  spec->add(versionDefinition);

  Evolution::createXsd(spec);
  DataConfiguration::createXsd(spec);
  Population::createXsd(spec);
}


void ENP::__getChild(DataParseElement *element)
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
      (*e) << _version << " but this enp binary only supports XML version ";
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

  if(element->opening(TAG_POPULATION))
  {
    _population = new Population(this);
    current = _population;
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
