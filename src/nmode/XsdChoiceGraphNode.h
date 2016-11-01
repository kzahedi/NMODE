#ifndef __XSD_CHOICE_GRAPH_NODE_H__
#define __XSD_CHOICE_GRAPH_NODE_H__

#include <nmode/XsdGraphNode.h>
#include <nmode/XsdGraph.h>
#include <nmode/XsdChoice.h>

#include <string>
#include <sstream>

using namespace std;

class XsdChoiceGraphNode : public XsdGraphNode
{
  public:
    XsdChoiceGraphNode(XsdGraph* graph, XsdChoice* spec);
    string customLabel(string label);
    string name();
    string content();
    XsdChoice* spec();

  private:

    XsdGraphNode* __findNode(string name);
    stringstream  _oss;
    XsdChoice*    _spec;
    XsdGraph*     _graph;

};

#endif // __XSD_CHOICE_GRAPH_NODE_H__

