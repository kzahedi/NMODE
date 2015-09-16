#ifndef ___DATA_EVOLUTION_H__
#define ___DATA_EVOLUTION_H__

#include "XsdParseNode.h"

#include "EvolutionNode.h"
#include "EvolutionEdge.h"

# define TAG_EVOLUTION                        (char*)"evolution"
# define TAG_EVOLUTION_DEFINITION             (char*)"evolution_definition"

class Evolution : public XsdParseNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    Evolution(XsdParseNode *parent);

    /**
     * @brief Destructor.
     */
    virtual ~Evolution();

    void add(DataParseElement *element);

    static void createXsd(XsdSpecification *spec);

    EvolutionNode* node();
    EvolutionEdge* edge();

  private:
    EvolutionNode *_node;
    EvolutionEdge *_edge;

};

#endif // ___DATA_EVOLUTION_H__
