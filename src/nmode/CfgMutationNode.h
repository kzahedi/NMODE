#ifndef __DATA_EVOLUTION_NODE_H__
#define __DATA_EVOLUTION_NODE_H__

#include "XsdParseNode.h"
#include "Version.h"

# define TAG_MUTATION_NODE            (char*)"node"
# define TAG_MUTATION_NODE_DEFINITION (char*)"node_evolution_definition"

class CfgMutationNode : public XsdParseNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    CfgMutationNode(XsdParseNode *parent);

    /**
     * @brief Destructor.
     */
    ~CfgMutationNode();

    void add(ParseElement *element);

    static void createXsd(XsdSpecification *spec);

    double modifyProbability();
    double modifyMaxValue();
    double modifyDelta();
    double addProbability();
    double addMaxValue();
    double delProbability();

  private:

    double _modifyProbability;
    double _modifyMaxValue;
    double _modifyDelta;
    double _addProbability;
    double _addMaxValue;
    double _delProbability;


};

#endif // ___DATA_EVOLUTION_NODE_H__


