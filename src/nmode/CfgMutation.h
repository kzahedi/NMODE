#ifndef ___CFG_MUTATION_H__
#define ___CFG_MUTATION_H__

#include "XsdParseNode.h"

#include "CfgMutationNode.h"
#include "CfgMutationEdge.h"

# define TAG_MUTATION                        (char*)"mutation"
# define TAG_MUTATION_DEFINITION             (char*)"mutation_definition"

class CfgMutation : public XsdParseNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    CfgMutation(XsdParseNode *parent);

    /**
     * @brief Destructor.
     */
    virtual ~CfgMutation();

    void add(ParseElement *element);

    static void createXsd(XsdSpecification *spec);

    CfgMutationNode* node();
    CfgMutationEdge* edge();

  private:
    CfgMutationNode *_node;
    CfgMutationEdge *_edge;

};

#endif // ___CFG_MUTATION_H__
