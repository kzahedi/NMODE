#ifndef __DATA_EVOLUTION_NODE_H__
#define __DATA_EVOLUTION_NODE_H__

#include "XsdParseNode.h"
#include "Version.h"

# define TAG_EVOLUTION_NODE            (char*)"node"
# define TAG_EVOLUTION_NODE_DEFINITION (char*)"node_evolution_definition"

class EvolutionNode : public XsdParseNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    EvolutionNode(XsdParseNode *parent);

    /**
     * @brief Destructor.
     */
    virtual ~EvolutionNode();

    void add(ParseElement *element);

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

#endif // ___DATA_EVOLUTION_NODE_H__


