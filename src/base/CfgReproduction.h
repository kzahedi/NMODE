#ifndef __CFG_REPRODUCTION_H__
#define __CFG_REPRODUCTION_H__

#include "XsdParseNode.h"

# define TAG_REPRODUCTION            (char*)"reproduction"
# define TAG_REPRODUCTION_DEFINITION (char*)"reproduction_cfg_definition"

class CfgReproduction : public XsdParseNode
{
  public:
    CfgReproduction(XsdParseNode *parent);

    void add(ParseElement *element);

    static void createXsd(XsdSpecification *spec);

    int populationSize();
    double selectionPressure();

  private:
    int    _populationSize;
    double _selectionPressure;
};


#endif // __CFG_REPRODUCTION_H__
