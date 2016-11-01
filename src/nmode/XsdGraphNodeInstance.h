#ifndef __XSD_GRAPH_NODE_INSTANCE_H__
#define __XSD_GRAPH_NODE_INSTANCE_H__

#include "XsdGraphNode.h"

#include <string>
#include <vector>
using namespace std;

class XsdGraphNodeInstance : public std::vector<XsdGraphNodeInstance*>
{
  public:
    XsdGraphNodeInstance(string name, string label, XsdGraphNode *node, string restrictions);

    string uniqueName();
    string name();
    string label();
    string restrictions();
    int    port();
    void   setPort(int port);

  private:
    string        _uniqueName;
    string        _name;
    string        _label;
    string        _restrictions;
    int           _port;
    XsdGraphNode* _node;
    static int    _index;
};

#endif // __XSD_GRAPH_NODE_INSTANCE_H__
