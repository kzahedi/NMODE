#ifndef __YARS_XSD_CHOCIE_H__
#define __YARS_XSD_CHOCIE_H__

#include <nmode/XsdNode.h>
#include <nmode/XsdElement.h>
#include <nmode/XsdAttribute.h>

#include <string>
#include <vector>

class XsdSequence;

using namespace std;

class XsdChoice : public XsdNode
{

  public:
    XsdChoice(string name);
    XsdChoice(string name, int minOccurs, int maxOccurs);
    XsdChoice(string name, string minOccurs, string maxOccurs);

    string name();
    void setName(string name);
    void add(XsdElement *element);
    void add(XsdAttribute *attribute);
    void add(XsdSequence *sequence);
    void add(std::vector<XsdElement*> elements);

    std::vector<XsdElement*>::iterator e_begin();
    std::vector<XsdElement*>::iterator e_end();
    int e_size();

    std::vector<XsdAttribute*>::iterator a_begin();
    std::vector<XsdAttribute*>::iterator a_end();
    int a_size();

    std::vector<XsdSequence*>::iterator s_begin();
    std::vector<XsdSequence*>::iterator s_end();
    int s_size();


    bool   maxOccursGiven();
    bool   minOccursGiven();
    string maxOccurs();
    string minOccurs();

    void setMaxOccurs(string maxOccurs);
    void setMinOccurs(string minOccurs);

  private:
    string _minOccurs;
    string _maxOccurs;
    string _name;
    bool   _minOccursGiven;
    bool   _maxOccursGiven;
    std::vector<XsdElement*>     _elements;
    std::vector<XsdAttribute*>   _attributes;
    std::vector<XsdSequence*>    _sequences;

};

#endif // __YARS_XSD_CHOCIE_H__



