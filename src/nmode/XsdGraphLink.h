#ifndef __NMODE_XSD_GRAPH_LINK_H__
#define __NMODE_XSD_GRAPH_LINK_H__

class XsdGraphNode;

#include <nmode/XsdGraphNode.h>

class XsdGraphLink
{
  public:
    XsdGraphLink();
    string label();
    void   setLabel(string label);

    XsdGraphNode* source();
    XsdGraphNode* destination();
    string        destinationName();
    void          setDestinationName(string dName);
    void          setSource(XsdGraphNode *source);
    void          setDestination(XsdGraphNode *destination);

  private:
    XsdGraphNode *_source;
    XsdGraphNode *_destination;
    string        _label;
    string        _destinationName;
};

#endif // __XSD_GRAPH_LINK_H__
