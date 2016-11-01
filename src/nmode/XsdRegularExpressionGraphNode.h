#ifndef __XSD_REGULAR_EXPRESSION_GRAPH_NODE_H__
#define __XSD_REGULAR_EXPRESSION_GRAPH_NODE_H__

#include <yars/configuration/xsd/graphviz/graph/XsdGraphNode.h>
#include <yars/configuration/xsd/specification/XsdRegularExpression.h>

#include <string>
#include <sstream>

using namespace std;

class XsdRegularExpressionGraphNode : public XsdGraphNode
{
  public:
    XsdRegularExpressionGraphNode(XsdRegularExpression *spec);
    string customLabel(string label);
    string name();
    string content();
    XsdRegularExpression* spec();

  private:
    stringstream          _oss;
    XsdRegularExpression *_spec;
    string                _specification;
    string                _type;
};

#endif // __XSD_REGULAR_EXPRESSION_GRAPH_NODE_H__
