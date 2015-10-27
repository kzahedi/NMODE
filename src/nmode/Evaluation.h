#ifndef __EVALUATION_H__
#define __EVALUATION_H__

#include <nmode/XsdParseNode.h>
#include <nmode/EvaluationParameter.h>
#include <nmode/EvaluationParameterMap.hpp>

#include <string>

using namespace std;

# define TAG_EVALUATION            (char*)"evaluation"
# define TAG_EVALUATION_DEFINITION (char*)"evaluation_definition"

class Evaluation : public XsdParseNode, public EvaluationParameterMap
{
  public:
    Evaluation(XsdParseNode *parent);

    void add(ParseElement *element);

    static void createXsd(XsdSpecification *spec);

    int    lifeTime();
    int    generations();
    double nodeCost();
    double edgeCost();
    string module();

  private:
    int                  _lifeTime;
    int                  _generations;
    double               _nodeCost;
    double               _edgeCost;
    string               _module;
    EvaluationParameters _parameters;
};


#endif // __EVALUATION_H__
