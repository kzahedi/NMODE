#ifndef __YARS_XSD_ATTRIBUTE_H__
#define __YARS_XSD_ATTRIBUTE_H__

#include <nmode/XsdNode.h>

#include <string>

using namespace std;

class XsdAttribute : public XsdNode
{
  public:
    XsdAttribute();
    XsdAttribute(string name, string type, bool required);

    void   setName(string name);
    string name();

    void   setType(string type);
    string type();

    void   setRequired(bool required);
    bool   required();

  private:
    string _name;
    string _type;
    bool   _required;
};

#endif // __YARS_XSD_ATTRIBUTE_H__


