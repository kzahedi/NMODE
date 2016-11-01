#ifndef __YARS_XSD_GRAPH_NODE_H__
#define __YARS_XSD_GRAPH_NODE_H__

#include <yars/configuration/xsd/specification/XsdSpecification.h>

#include <string>
#include <vector>

#define ATTRIBUTE_BGCOLOR     "#fee1b7"
#define ELEMENT_BGCOLOR       "#adc9f0"
#define CHOICE_BGCOLOR        "#adf0ad"
#define SPECIFICATION_BGCOLOR "#fefeb7"

#define REGEXP_BGCOLOR        "#f3afd7"
#define INTERVAL_BGCOLOR      "#d9adf0"
#define ENUM_BGCOLOR          "#b8adf0"

#define OPTIONAL_COLOR        "#00A000"
#define REQUIRED_COLOR        "#ff0000"

using namespace std;

class XsdGraphNode
{
  public:
    XsdGraphNode();
    virtual ~XsdGraphNode() { };

    virtual string   customLabel(string label) = 0;
    virtual string   name()                    = 0;
    virtual string   content()                 = 0;
    virtual XsdNode* spec()                    = 0;

    string uniqueNodeName();
    void   setUniqueNodeName(string n);
    bool   hasDefinition(string type);

  private:
    string            _uniqueName;
};

#endif // __YARS_XSD_GRAPH_NODE_H__
