#include <nmode/Simulator.h>

#include <iostream>

#define TAG_WD      (char*)"wd"
#define TAG_XML     (char*)"xml"
#define TAG_NR      (char*)"nr"
#define TAG_OPTIONS (char*)"options"


using namespace std;

Simulator::Simulator(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _workingDirectory = "no wd";
  _xml              = "no xml";
  _options          = "";
  _nr               = 4;
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
    element->set(TAG_OPTIONS, _options);
    element->set(TAG_NR,      _nr);
    return;
  }
}

void Simulator::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_SIMULATOR_DEFINITION);
  root->add(NA(TAG_WD,      TAG_XSD_STRING,                true));
  root->add(NA(TAG_XML,     TAG_XSD_STRING,                true));
  root->add(NA(TAG_OPTIONS, TAG_XSD_STRING,                false));
  root->add(NA(TAG_NR,      TAG_POSITIVE_NON_ZERO_DECIMAL, true));
  spec->add(root);
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
  return _nr;
}

string Simulator::options()
{
  return _options;
}

