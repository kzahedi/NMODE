#ifndef __YARS_XSD_SEQUENCE_H__
#define __YARS_XSD_SEQUENCE_H__

#include <nmode/XsdNode.h>
#include <nmode/XsdElement.h>
#include <nmode/XsdAttribute.h>
#include <nmode/XsdChoice.h>
#include <nmode/XsdRegularExpression.h>
#include <nmode/XsdInterval.h>

#include <string>
#include <vector>

using namespace std;

class XsdSequence : public XsdNode
{

  public:
    XsdSequence();
    XsdSequence(string name);

    void setName(char *name);
    void setName(string name);
    void add(XsdElement *element);
    void add(XsdAttribute *attribute);
    void add(XsdChoice *choice);
    void add(XsdRegularExpression *regExp);
    void add(XsdInterval *interval);
    void add(std::vector<XsdElement*> elements);

    string name();

    std::vector<XsdElement*>::iterator           e_begin();
    std::vector<XsdElement*>::iterator           e_end();
    int                                     e_size();

    std::vector<XsdAttribute*>::iterator         a_begin();
    std::vector<XsdAttribute*>::iterator         a_end();
    int                                     a_size();

    std::vector<XsdChoice*>::iterator            c_begin();
    std::vector<XsdChoice*>::iterator            c_end();
    int                                     c_size();

    std::vector<XsdRegularExpression*>::iterator r_begin();
    std::vector<XsdRegularExpression*>::iterator r_end();
    int                                     r_size();

    std::vector<XsdInterval*>::iterator          i_begin();
    std::vector<XsdInterval*>::iterator          i_end();
    int                                     i_size();

    std::vector<XsdNode*>::iterator              n_begin();
    std::vector<XsdNode*>::iterator              n_end();
    int                                     n_size();

  private:
    string                             _name;
    std::vector<XsdElement*>           _elements;
    std::vector<XsdAttribute*>         _attributes;
    std::vector<XsdChoice*>            _choices;
    std::vector<XsdRegularExpression*> _regExps;
    std::vector<XsdInterval*>          _intervals;
    std::vector<XsdNode*>              _children;

};

#endif // __YARS_XSD_SEQUENCE_H__


