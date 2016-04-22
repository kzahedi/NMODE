#ifndef __NMODE_XSD_ELEMENT_GRAPH_NODE_H__
#define __NMODE_XSD_ELEMENT_GRAPH_NODE_H__

#include <nmode/XsdGraphNode.h>
#include <nmode/XsdElement.h>

#include <string>
#include <sstream>

using namespace std;

class XsdElementGraphNode : public XsdGraphNode
{
  public:
    XsdElementGraphNode(XsdElement *spec);
    string customLabel(string label);
    string name();
    XsdElement* spec();

  private:
    stringstream _oss;
    XsdElement *_spec;

};

#endif // __XSD_ELEMENT_GRAPH_NODE_H__


