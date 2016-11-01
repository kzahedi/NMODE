#ifndef __XSD_ENUMERATION_GRAPH_NODE_H__
#define __XSD_ENUMERATION_GRAPH_NODE_H__

#include <yars/configuration/xsd/graphviz/graph/XsdGraphNode.h>
#include <yars/configuration/xsd/specification/XsdEnumeration.h>

#include <string>
#include <sstream>

using namespace std;

class XsdEnumerationGraphNode : public XsdGraphNode
{
  public:
    XsdEnumerationGraphNode(XsdEnumeration *spec);
    string customLabel(string label);
    string content();
    string name();
    XsdEnumeration* spec();

  private:
    stringstream    _oss;
    XsdEnumeration *_spec;
    string          _specification;
    string          _type;
};

#endif // __XSD_ENUMERATION_GRAPH_NODE_H__
