#include <iostream>
#include <glog/logging.h>

#define TAG_SOURCE                      (char*)"source"
#define TAG_DESTINATION                 (char*)"destination"
#define TAG_WEIGHT                      (char*)"weight"

using namespace std;

DataPopulationModuleEdge::DataPopulationModuleEdge(DataNode *parent)
  : DataNode(parent)
{ }

void DataPopulationModuleEdge::add(DataParseElement *element)
{
  if(element->closing(TAG_EDGE))
  {
    current = parent;
    return;
  }

  if(element->opening(TAG_EDGE))
  {
    element->set(TAG_SOURCE,      _source);
    element->set(TAG_DESTINATION, _destination);
    element->set(TAG_WEIGHT,      _weight);
    VLOG(100) << "set edge values to " << _source << " -> " << _destination << " with " << _weight;
  }

}

void DataPopulationModuleEdge::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_EDGE_DEFINITION);
  root->add(NA(TAG_SOURCE,      TAG_XSD_STRING,  true));
  root->add(NA(TAG_DESTINATION, TAG_XSD_STRING,  true));
  root->add(NA(TAG_WEIGHT,      TAG_XSD_DECIMAL, true));
  spec->add(root);
}

string DataPopulationModuleEdge::source()
{
  return _source;
}

string DataPopulationModuleEdge::destination()
{
  return _destination;
}

double DataPopulationModuleEdge::weight()
{
  return _weight;
}

