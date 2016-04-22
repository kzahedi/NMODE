#ifndef __YARS_XSD_REGULAR_EXPRESSION_H__
#define __YARS_XSD_REGULAR_EXPRESSION_H__

#include <nmode/XsdNode.h>

#include <string>
#include <vector>

using namespace std;

class XsdRegularExpression : public XsdNode
{
  public:
    XsdRegularExpression(string name, string type, string regExp);

    string regExp();
    string name();
    string type();


  private:
    string _name;
    string _type;
    string _regExp;
};

#endif // __YARS_XSD_REGULAR_EXPRESSION_H__

