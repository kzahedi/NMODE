#include "Edge.h"

#include <iostream>
#include <glog/logging.h>

#define TAG_SOURCE                      (char*)"source"
#define TAG_DESTINATION                 (char*)"destination"
#define TAG_WEIGHT                      (char*)"weight"

using namespace std;

Edge::Edge(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _sourceNode      = NULL;
  _destinationNode = NULL;
}

Edge::~Edge()
{
  // nothing to do
}

void Edge::add(ParseElement *element)
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

void Edge::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_MODULE_EDGE_DEFINITION);
  root->add(NA(TAG_SOURCE,      TAG_XSD_STRING,  true));
  root->add(NA(TAG_DESTINATION, TAG_XSD_STRING,  true));
  root->add(NA(TAG_WEIGHT,      TAG_XSD_DECIMAL, true));
  spec->add(root);
}

string Edge::source()
{
  return _source;
}

string Edge::destination()
{
  return _destination;
}

double Edge::weight()
{
  return _weight;
}

bool Edge::operator==(const Edge o)
{
  return (_weight      == o._weight &&
          _source      == o._source &&
          _destination == o._destination);
}

bool Edge::operator!=(const Edge o)
{
  return (_weight      != o._weight ||
          _source      != o._source ||
          _destination != o._destination);
}

Node* Edge::sourceNode()
{
  return _sourceNode;
}

Node* Edge::destinationNode()
{
  return _destinationNode;
}

void Edge::setSourceNode(Node* src)
{
  _sourceNode = src;
}

void Edge::setDestinationNode(Node* dst)
{
  _destinationNode = dst;
}

void Edge::setWeight(double w)
{
  _weight = w;
}
