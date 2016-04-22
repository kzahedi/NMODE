#ifndef __YARS_XSD_ELEMENT_H__
#define __YARS_XSD_ELEMENT_H__

#include <nmode/XsdNode.h>
#include <nmode/XsdAttribute.h>

#include <string>
#include <vector>

# define TAG_XSD_UNBOUNDED (char*)"unbounded"

using namespace std;

class XsdElement : public XsdNode
{
  public:
    XsdElement();
    XsdElement(string name, string type, int minOccurs);
    XsdElement(string name, string type, int minOccurs, int maxOccurs);
    XsdElement(string name, string type, string minOccurs = "", string maxOccurs = "");
    XsdElement(string name, string type, int minOccurs, string maxOccurs);
    void setName(string name);
    void setType(string type);
    void setMinOccurs(string minOccurs);
    void setMinOccurs(int minOccurs);
    void setMaxOccurs(string maxOccurs);
    void setMaxOccurs(int maxOccurs);

    string name();
    string type();

    string minOccurs();
    bool   minOccursGiven();
    string maxOccurs();
    bool   maxOccursGiven();

    void   add(XsdAttribute *attribute);
    std::vector<XsdAttribute*>::iterator a_begin();
    std::vector<XsdAttribute*>::iterator a_end();
    int a_size();

  private:
    string _name;
    string _type;
    string _minOccurs;
    string _maxOccurs;
    bool   _minOccursGiven;
    bool   _maxOccursGiven;
    std::vector<XsdAttribute*> _attributes;
};

#endif // __YARS_XSD_ELEMENT_H__


