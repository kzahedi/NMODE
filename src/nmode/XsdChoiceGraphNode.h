#ifndef __NMODE_XSD_CHOICE_GRAPH_NODE_H__
#define __NMODE_XSD_CHOICE_GRAPH_NODE_H__

#include <nmode/XsdGraphNode.h>
#include <nmode/XsdChoice.h>

#include <string>
#include <sstream>

using namespace std;

class XsdChoiceGraphNode : public XsdGraphNode
{
  public:
    XsdChoiceGraphNode(XsdChoice *spec);
    string customLabel(string label);
    string name();
    XsdChoice* spec();

  private:
    stringstream _oss;
    XsdChoice *_spec;

};

#endif // __XSD_CHOICE_GRAPH_NODE_H__

