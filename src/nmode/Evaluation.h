#ifndef __EVALUATION_H__
#define __EVALUATION_H__

#include "XsdParseNode.h"

# define TAG_EVALUATION            (char*)"evaluation"
# define TAG_EVALUATION_DEFINITION (char*)"evaluation_definition"

class Evaluation : public XsdParseNode
{
  public:
    Evaluation(XsdParseNode *parent);

    void add(ParseElement *element);

    static void createXsd(XsdSpecification *spec);

    int    lifeTime();
    int    generations();
    double nodeCost();
    double edgeCost();

  private:
    int    _lifeTime;
    int    _generations;
    double _nodeCost;
    double _edgeCost;
};


#endif // __EVALUATION_H__
