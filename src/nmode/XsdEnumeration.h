#ifndef __YARS_XSD_ENUMERATION_H__
#define __YARS_XSD_ENUMERATION_H__

#include <nmode/XsdNode.h>

#include <string>
#include <vector>

using namespace std;

class XsdEnumeration : public XsdNode
{
  public:
    XsdEnumeration(string name, string type);
    void add(string name);
    void base(string base);

    std::vector<string>::iterator v_begin();
    std::vector<string>::iterator v_end();

    string name();
    string type();

  private:
    string _name;
    string _type;

    std::vector<string> _value;

};

#endif // __YARS_XSD_ENUMERATION_H__


