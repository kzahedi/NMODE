#ifndef ___DATA_EVOLUTION_EDGE_H__
#define ___DATA_EVOLUTION_EDGE_H__

#include "XsdParseNode.h"
#include "Version.h"

# define TAG_EVOLUTION_EDGE            (char*)"edge"
# define TAG_EVOLUTION_EDGE_DEFINITION (char*)"edge_evolution_definition"

class EvolutionEdge : public XsdParseNode
{
  public:

    EvolutionEdge(XsdParseNode *parent);

    ~EvolutionEdge();

    void add(DataParseElement *element);

    static void createXsd(XsdSpecification *spec);

    double modifyProbability();
    double modifyMaxValue();
    double modifyDelta();

    double addProbability();
    double addMaxValue();

    double delProbability();

    double cost();

  private:

    double _modifyProbability;
    double _modifyMaxValue;
    double _modifyDelta;

    double _addProbability;
    double _addMaxValue;

    double _delProbability;

    double _cost;


};

#endif // ___DATA_EVOLUTION_EDGE_H__
