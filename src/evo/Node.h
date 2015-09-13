#ifndef __NODE_H__
#define __NODE_H__

#include <vector>
#include <string>
#include <ostream>

#include "base/P3D.h"
#include "base/ENPException.h"


#define NODE_TYPE_SENSOR    1001
#define NODE_TYPE_ACTUATOR  1002
#define NODE_TYPE_HIDDEN    1003
#define NODE_TYPE_INPUT     1004
#define NODE_TYPE_OUTPUT    1005
#define NODE_TYPE_CONNECTOR 1006

using namespace std;

class Node
{
  public:
    Node();
    ~Node();

    //Node(const Node);
    //Node operator=(const Node);


    void   setBias(double v);
    double bias();

    bool isSource();
    bool isDestination();



  private:

    P3D    _position;
    int    _type;
    double _bias;
    string _stype;
    string _label;
    string _transferfunction;
};

typedef vector<Node*> Nodes;

#endif // __NODE_H__

