#ifndef __DATA_PARAMETER_H__
#define __DATA_PARAMETER_H__

#include "ParseElement.h"
#include "XsdParseNode.h"

#include <string>

using namespace std;

# define TAG_FITNESS_PARAMETER            (char*)"parameter"
# define TAG_FITNESS_PARAMETER_DEFINITION (char*)"fitness_parameter_definition"
# define TAG_VALUE                        (char*)"value"

class FitnessParameter : public XsdParseNode
{
  public:
    FitnessParameter(XsdParseNode *parent);
    virtual ~FitnessParameter() { };

    void add(ParseElement *element);

    string name();
    double realValue();
    int intValue();
    string value();
    bool boolValue();

    void createXsd();

    FitnessParameter *copy();

    void resetTo(const FitnessParameter *other);

  private:
    string _name;
    string _value;
};

#endif // __DATA_PARAMETER_H__
