#ifndef __NMODE_XSD_ENUMERATION_GRAPH_NODE_H__
#define __NMODE_XSD_ENUMERATION_GRAPH_NODE_H__

#include <nmode/XsdGraphNode.h>
#include <nmode/XsdEnumeration.h>

#include <string>
#include <sstream>

using namespace std;

class XsdEnumerationGraphNode : public XsdGraphNode
{
  public:
    XsdEnumerationGraphNode(XsdEnumeration *spec);
    string customLabel(string label);
    string name();
    XsdEnumeration* spec();

  private:
    stringstream    _oss;
    XsdEnumeration *_spec;
    string          _specification;
    string          _type;
};

#endif // __XSD_ENUMERATION_GRAPH_NODE_H__
