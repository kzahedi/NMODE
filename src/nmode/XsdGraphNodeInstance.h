#ifndef __NMODE_XSD_GRAPH_NODE_INSTANCE_H__
#define __NMODE_XSD_GRAPH_NODE_INSTANCE_H__

#include <nmode/XsdGraphNode.h>

#include <string>
#include <vector>
using namespace std;

class XsdGraphNodeInstance : public std::vector<XsdGraphNodeInstance*>
{
  public:
    XsdGraphNodeInstance(string name, string label, XsdGraphNode *node);

    string uniqueName();
    string name();
    string label();
    int    port();
    void   setPort(int port);

  private:
    string        _uniqueName;
    string        _name;
    string        _label;
    int           _port;
    XsdGraphNode *_node;

    static int    _index;
};

#endif // __XSD_GRAPH_NODE_INSTANCE_H__
