#ifndef __DATA_EVOLUTION_NODE_H__
#define __DATA_EVOLUTION_NODE_H__

#include "DataNode.h"
#include "Version.h"

# define TAG_EVOLUTION_NODE            (char*)"node"
# define TAG_EVOLUTION_NODE_DEFINITION (char*)"node_evolution_definition"

class DataEvolutionNode : public DataNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    DataEvolutionNode(DataNode *parent);

    /**
     * @brief Destructor.
     */
    virtual ~DataEvolutionNode();

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

#endif // ___DATA_EVOLUTION_NODE_H__


