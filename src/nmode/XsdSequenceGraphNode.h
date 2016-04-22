#ifndef __NMODE_XSD_SEQUENCE_GRAPH_NODE_H__
#define __NMODE_XSD_SEQUENCE_GRAPH_NODE_H__

#include <nmode/XsdGraphNode.h>
#include <nmode/XsdSequence.h>

#include <string>
#include <sstream>

using namespace std;

class XsdSequenceGraphNode : public XsdGraphNode
{
  public:
    XsdSequenceGraphNode(XsdSequence *spec);
    string customLabel(string label);
    string name();
    XsdSequence* spec();

  private:
    stringstream _oss;
    XsdSequence *_spec;
};

#endif // __XSD_SEQUENCE_GRAPH_NODE_H__
