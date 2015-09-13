#include "DataModuleEdge.h"

#include <iostream>
#include <glog/logging.h>

#define TAG_SOURCE                      (char*)"source"
#define TAG_DESTINATION                 (char*)"destination"
#define TAG_WEIGHT                      (char*)"weight"

using namespace std;

DataModuleEdge::DataModuleEdge(DataNode *parent)
  : DataNode(parent)
{
  _sourceNode      = NULL;
  _destinationNode = NULL;
}

DataModuleEdge::~DataModuleEdge()
{
}

void DataModuleEdge::add(DataParseElement *element)
{
  VLOG(100) << "parsing " << element->name();
  if(element->closing(TAG_MODULE_EDGE))
  {
    current = parent;
    return;
  }

  if(element->opening(TAG_MODULE_EDGE))
  {
    element->set(TAG_SOURCE,      _source);
    element->set(TAG_DESTINATION, _destination);
    element->set(TAG_WEIGHT,      _weight);
    VLOG(100) << "set edge values to " << _source << " -> " << _destination << " with " << _weight;
  }

}

void DataModuleEdge::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_MODULE_EDGE_DEFINITION);
  root->add(NA(TAG_SOURCE,      TAG_XSD_STRING,  true));
  root->add(NA(TAG_DESTINATION, TAG_XSD_STRING,  true));
  root->add(NA(TAG_WEIGHT,      TAG_XSD_DECIMAL, true));
  spec->add(root);
}

string DataModuleEdge::source()
{
  return _source;
}

string DataModuleEdge::destination()
{
  return _destination;
}

double DataModuleEdge::weight()
{
  return _weight;
}

bool DataModuleEdge::operator==(const DataModuleEdge o)
{
  return (_weight      == o._weight &&
          _source      == o._source &&
          _destination == o._destination);
}

bool DataModuleEdge::operator!=(const DataModuleEdge o)
{
  return (_weight      != o._weight ||
          _source      != o._source ||
          _destination != o._destination);
}

DataModuleNode* DataModuleEdge::sourceNode()
{
  return _sourceNode;
}

DataModuleNode* DataModuleEdge::destinationNode()
{
  return _destinationNode;
}

