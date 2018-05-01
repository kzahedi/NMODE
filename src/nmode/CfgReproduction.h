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
    int    loggingSize();
    double crossoverProbability();
    double tournamentPercentage();

  private:
    int    _populationSize;
    int    _loggingSize;
    double _crossoverProbability;
    double _tournament;
};


#endif // __CFG_REPRODUCTION_H__
