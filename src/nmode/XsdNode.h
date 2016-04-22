#ifndef __XSD_NODE_H__
#define __XSD_NODE_H__

# define XSD_NODE_TYPE_SEQUENCE    0
# define XSD_NODE_TYPE_ELEMENT     1
# define XSD_NODE_TYPE_CHOICE      2
# define XSD_NODE_TYPE_REG_EXP     3
# define XSD_NODE_TYPE_INTERVAL    4
# define XSD_NODE_TYPE_ATTRIBUTE   5
# define XSD_NODE_TYPE_ENUMERATION 6

#include <string>

using namespace std;

class XsdNode
{
  public:
    XsdNode(int nodeType);
    ~XsdNode();

    int    nodeType();
    void   setComment(string comment);
    string comment();
    virtual string name() = 0;

  private:
    int    _nodeType;
    string _comment;
};

#endif // __XSD_NODE_H__


