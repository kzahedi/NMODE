#ifndef __EDGE_H__
#define __EDGE_H__

#define EDGE_TYPE_SENSOR   1001
#define EDGE_TYPE_ACTUATOR 1002
#define EDGE_TYPE_HIDDEN   1003

#include "base/P3D.h"

#include <vector>

using namespace std;

class Node;

class Edge
{
  public:
    Edge();
    ~Edge();

    //Edge(const Edge);
    //Edge operator=(const Edge);
    bool operator==(const Edge o);
    bool operator!=(const Edge o);

    void setSource(Node *src);
    void setDestination(Node *dest);
    void setWeight(double weight);

    Node*  source();
    Node*  destination();
    double weight();

  private:

    Node  *_src;
    Node  *_dest;
    double _weight;
};

typedef vector<Edge*> Edges;

#endif // __EDGE_H__

