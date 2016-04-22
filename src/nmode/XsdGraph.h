#ifndef __NMODE_YARS_XSD_GRAPH_H__
#define __NMODE_YARS_XSD_GRAPH_H__

#include <nmode/XsdGraphNode.h>
#include <nmode/XsdGraphNodeInstance.h>
#include <nmode/XsdGraphLink.h>

#include <ostream>
#include <sstream>

using namespace std;

class XsdGraph
{
  public:
    XsdGraph();
    ~XsdGraph();

    XsdGraphNodeInstance* get(string parent, string name);

    std::vector<XsdGraphNodeInstance*>::iterator i_begin();
    std::vector<XsdGraphNodeInstance*>::iterator i_end();

  private:
    void __createGraph();
    void __add(XsdSequence          *seq);
    void __add(XsdChoice            *choice);
    void __add(XsdEnumeration       *enumeration);
    void __add(XsdInterval          *interval);
    void __add(XsdRegularExpression *regexp);

    void __add(XsdGraphNodeInstance *parent, XsdNode              *node);
    void __add(XsdGraphNodeInstance *parent, XsdElement           *element);
    void __add(XsdGraphNodeInstance *parent, XsdAttribute         *attribute);
    void __add(XsdGraphNodeInstance *parent, XsdSequence          *node);
    void __add(XsdGraphNodeInstance *parent, XsdChoice            *node);
    void __add(XsdGraphNodeInstance *parent, XsdRegularExpression *node);
    void __add(XsdGraphNodeInstance *parent, XsdInterval          *node);
    void __add(XsdGraphNodeInstance *parent, XsdEnumeration       *node);

    XsdGraphNode* __findNode(string          name);

    XsdGraphNodeInstance *_root;
    XsdSpecification     *_spec;

    std::vector<XsdGraphNode*>         _nodes;
    std::vector<XsdGraphNodeInstance*> _instances;
};

#endif // __YARS_XSD_GRAPH_H__
