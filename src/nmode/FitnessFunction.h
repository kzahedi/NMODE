#ifndef __FITNESS_FUNCTION_H__
#define __FITNESS_FUNCTION_H__

#include "XsdParseNode.h"

# define TAG_FITNESS_FUNCTION            (char*)"fitnessfunction"
# define TAG_FITNESS_FUNCTION_DEFINITION (char*)"fitnessfunction_definition"

class FitnessFunction : public XsdParseNode
{
  public:
    FitnessFunction(XsdParseNode *parent);

    void add(ParseElement *element);

    static void createXsd(XsdSpecification *spec);

    int    lifeTime();
    double nodeCost();
    double edgeCost();

  private:
    int _lifeTime;
    double _nodeCost;
    double _edgeCost;
};


#endif // __FITNESS_FUNCTION_H__
