#ifndef __XSD_INTERVAL_GRAPH_NODE_H__
#define __XSD_INTERVAL_GRAPH_NODE_H__

#include <nmode/XsdGraphNode.h>
#include <nmode/XsdInterval.h>

#include <string>
#include <sstream>

using namespace std;

class XsdIntervalGraphNode : public XsdGraphNode
{
  public:
    XsdIntervalGraphNode(XsdInterval *spec);
    string customLabel(string label);
    string name();
    string content();
    XsdInterval* spec();

  private:
    stringstream  _oss;
    XsdInterval  *_spec;
    string        _specification;
    string        _type;
};

#endif // __XSD_INTERVAL_GRAPH_NODE_H__
