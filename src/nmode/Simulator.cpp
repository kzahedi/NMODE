#include <nmode/Simulator.h>

#include <iostream>

#define TAG_WD        (char*)"wd"
#define TAG_XML       (char*)"experiment"
#define TAG_NR        (char*)"nr"
#define TAG_PATH      (char*)"path"
#define TAG_ENV       (char*)"environment"
#define TAG_OPTIONS   (char*)"options"
#define TAG_YARS      (char*)"YARS"
#define TAG_OPENAI    (char*)"OpenAI"
#define TAG_SIM_ENUM  (char*)"environment_enum"


using namespace std;

Simulator::Simulator(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _workingDirectory = ".";
  _xml              = "";
  _path             = "";
  _options          = "";
  _nr               = 1;
  _env              = TAG_YARS;
  _overrideCpus     = -1;
}

Simulator::~Simulator()
{
}

void Simulator::add(ParseElement *element)
{
  if(element->closing(TAG_SIMULATOR))
  {
    current = parent;
    return;
  }

  if(element->opening(TAG_SIMULATOR))
  {
    element->set(TAG_WD,      _workingDirectory);
    element->set(TAG_XML,     _xml);
    element->set(TAG_PATH,    _path);
    element->set(TAG_OPTIONS, _options);
    element->set(TAG_NR,      _nr);
    element->set(TAG_ENV,     _env);
    return;
  }
}

void Simulator::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_SIMULATOR_DEFINITION);
  root->add(NA(TAG_WD,      TAG_XSD_STRING,                false));
  root->add(NA(TAG_XML,     TAG_XSD_STRING,                true));
  root->add(NA(TAG_OPTIONS, TAG_XSD_STRING,                false));
  root->add(NA(TAG_PATH,    TAG_XSD_STRING,                false));
  root->add(NA(TAG_ENV,     TAG_SIM_ENUM,                  false));
  root->add(NA(TAG_NR,      TAG_POSITIVE_NON_ZERO_INTEGER, false));
  spec->add(root);

  XsdEnumeration *envEnum = new XsdEnumeration(TAG_SIM_ENUM,
                                               TAG_XSD_STRING);
  envEnum->add(TAG_YARS);
  envEnum->add(TAG_OPENAI);
  spec->add(envEnum);

}

string Simulator::workingDirectory()
{
  return _workingDirectory;
}

string Simulator::xml()
{
  return _xml;
}

int Simulator::nr()
{
  if(_overrideCpus > 0) return _overrideCpus;
  return _nr;
}

string Simulator::options()
{
  return _options;
}

string Simulator::path()
{
  return _path;
}

string Simulator::env()
{
  return _env;
}

void Simulator::overrideCpus(int cpus)
{
  _overrideCpus = cpus;
}
