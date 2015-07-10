#include "Edge.h"

Edge::Edge()
{
}

Edge::~Edge()
{ }

void Edge::setSource(Node *src)
{
  _src = src;
}

void Edge::setDestination(Node *dest)
{
  _dest = dest;
}

void Edge::setWeight(double weight)
{
  _weight = weight;
}

Node* Edge::source()
{
  return _src;
}

Node* Edge::destination()
{
  return _dest;
}

double Edge::weight()
{
  return _weight;
}

bool Edge::operator==(const Edge o)
{
  return (_weight == o._weight &&
          _src    == o._src    &&
          _dest   == o._dest);
}

bool Edge::operator!=(const Edge o)
{
  return (_weight != o._weight ||
          _src    != o._src    ||
          _dest   != o._dest);
}

