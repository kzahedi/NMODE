#ifndef __XSD_ELEMENT_GRAPH_NODE_H__
#define __XSD_ELEMENT_GRAPH_NODE_H__

#include <nmode/XsdGraphNode.h>
#include <nmode/XsdGraph.h>

#include <nmode/XsdElement.h>

#include <string>
#include <sstream>

using namespace std;

class XsdElementGraphNode : public XsdGraphNode
{
  public:
    XsdElementGraphNode(XsdGraph* graph, XsdElement* spec);
    string customLabel(string label);
    string name();
    string content();
    XsdElement* spec();

  private:
    XsdGraphNode* __findNode(string name);

    stringstream  _oss;
    XsdElement*   _spec;
    XsdGraph*     _graph;
};

#endif // __XSD_ELEMENT_GRAPH_NODE_H__


