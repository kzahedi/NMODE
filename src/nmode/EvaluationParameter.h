#ifndef __EVALUATION_PARAMETER_H__
#define __EVALUATION_PARAMETER_H__

#include "ParseElement.h"
#include "XsdParseNode.h"

#include <string>
#include <vector>

using namespace std;

# define TAG_EVALUATION_PARAMETER            (char*)"parameter"
# define TAG_EVALUATION_PARAMETER_DEFINITION (char*)"evaluation_parameter_definition"

class EvaluationParameter : public XsdParseNode
{
  public:
    EvaluationParameter(XsdParseNode *parent);
    virtual ~EvaluationParameter() { };

    void add(ParseElement *element);

    string name();
    double realValue();
    int intValue();
    string value();
    bool boolValue();

    void createXsd(XsdSpecification *spec);

    EvaluationParameter *copy();

    void resetTo(const EvaluationParameter *other);

  private:
    string _name;
    string _value;
};

typedef vector<EvaluationParameter*> EvaluationParameters;

#endif // __EVALUATION_PARAMETER_H__
