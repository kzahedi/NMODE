#ifndef ___DATA_EVOLUTION_H__
#define ___DATA_EVOLUTION_H__

#include "DataNode.h"

#include "DataEvolutionNode.h"
#include "DataEvolutionEdge.h"

# define TAG_EVOLUTION                        (char*)"evolution"
# define TAG_EVOLUTION_DEFINITION             (char*)"evolution_definition"

class DataEvolution : public DataNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    DataEvolution(DataNode *parent);

    /**
     * @brief Destructor.
     */
    virtual ~DataEvolution();

    void add(DataParseElement *element);

    static void createXsd(XsdSpecification *spec);

    DataEvolutionNode* node();
    DataEvolutionEdge* edge();

  private:
    DataEvolutionNode *_node;
    DataEvolutionEdge *_edge;

};

#endif // ___DATA_EVOLUTION_H__
