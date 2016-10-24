#ifndef __NMODE_CFG_REPRODUCTION_H__
#define __NMODE_CFG_REPRODUCTION_H__

#include <nmode/XsdParseNode.h>

# define TAG_REPRODUCTION            (char*)"reproduction"
# define TAG_REPRODUCTION_DEFINITION (char*)"reproduction_cfg_definition"

class CfgReproduction : public XsdParseNode
{
  public:
    CfgReproduction(XsdParseNode *parent);

    void add(ParseElement *element);

    static void createXsd(XsdSpecification *spec);

    int    populationSize();
    double selectionPressure();
    double elitePressure();
    double crossoverProbability();

  private:
    int    _populationSize;
    double _selectionPressure;
    double _elitePressure;
    double _crossoverProbability;
};


#endif // __CFG_REPRODUCTION_H__
