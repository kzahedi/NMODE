#include "DataSimulator.h"

#include <iostream>

#define TAG_WD  (char*)"wd"
#define TAG_XML (char*)"xml"
#define TAG_NR  (char*)"nr"


using namespace std;

DataSimulator::DataSimulator(DataNode *parent)
  : DataNode(parent)
{ }

DataSimulator::~DataSimulator()
{
}


void DataSimulator::add(DataParseElement *element)
{
  if(element->closing(TAG_SIMULATOR))
  {
    current = parent;
    return;
  }

  if(element->opening(TAG_SIMULATOR))
  {
    element->set(TAG_WD,  _workingDirectory);
    element->set(TAG_XML, _xml);
    element->set(TAG_NR,  _nr);
    return;
  }
}

void DataSimulator::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_SIMULATOR_DEFINITION);
  root->add(NA(TAG_WD,  TAG_XSD_STRING,                true));
  root->add(NA(TAG_XML, TAG_XSD_STRING,                true));
  root->add(NA(TAG_NR,  TAG_POSITIVE_NON_ZERO_DECIMAL, true));
  spec->add(root);
}

string DataSimulator::workingDirectory()
{
  return _workingDirectory;
}

string DataSimulator::xml()
{
  return _xml;
}

int DataSimulator::nr()
{
  return _nr;
}

