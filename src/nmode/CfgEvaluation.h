#ifndef __NMODE_EVALUATION_H__
#define __NMODE_EVALUATION_H__

#include <nmode/XsdParseNode.h>
#include <nmode/EvaluationParameter.h>
#include <nmode/EvaluationParameterMap.hpp>

#include <string>

using namespace std;

# define TAG_EVALUATION            (char*)"evaluation"
# define TAG_EVALUATION_DEFINITION (char*)"evaluation_definition"

class CfgEvaluation : public XsdParseNode, public EvaluationParameterMap
{
  public:
    CfgEvaluation(XsdParseNode *parent);
    ~CfgEvaluation();

    void add(ParseElement *element);

    static void createXsd(XsdSpecification *spec);

    int    lifeTime();
    int    generations();
    double nodeCost();
    double edgeCost();
    string module();

    void setLifeTime(int);

  private:
    int                  _lifeTime;
    int                  _generations;
    double               _nodeCost;
    double               _edgeCost;
    string               _module;
    EvaluationParameters _parameters;
};


#endif // __EVALUATION_H__
