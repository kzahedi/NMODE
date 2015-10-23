#ifndef __FITNESS_FUNCTION_PARAMETER_H__
#define __FITNESS_FUNCTION_PARAMETER_H__

#include "XsdParseNode.h"

#include <string>

using namespace std;

# define PARAMETER                        "parameter"
# define YARS_STRING_PARAMETER            (char*)PARAMETER
# define YARS_STRING_PARAMETER_DEFINITION (char*)PARAMETER DIVIDER DEFINITION
# define VALUE                            "value"
# define YARS_STRING_VALUE                (char*)VALUE

class FitnessFunctionParameter : public XsdParseNode
{
  public:
    FitnessFunctionParameter(XsdParseNode *parent);
    virtual ~FitnessFunctionParameter() { };

    void add(DataParseElement *element);

    string name();
    yReal realValue();
    int intValue();
    string value();
    bool boolValue();

    void createXsd();

    FitnessFunctionParameter *copy();

    void resetTo(const FitnessFunctionParameter *other);

  private:
    string _name;
    string _value;
};

#endif // __FITNESS_FUNCTION_PARAMETER_H__
