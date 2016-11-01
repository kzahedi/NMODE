#ifndef __XSD_ELEMENT_GRAPH_NODE_H__
#define __XSD_ELEMENT_GRAPH_NODE_H__

#include <yars/configuration/xsd/graphviz/graph/XsdGraphNode.h>
#include <yars/configuration/xsd/graphviz/graph/XsdGraph.h>

#include <yars/configuration/xsd/specification/XsdElement.h>

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


