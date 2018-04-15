#ifndef __NMODE_CFG_MUTATION_H__
#define __NMODE_CFG_MUTATION_H__

#include <nmode/XsdParseNode.h>

#include <nmode/CfgMutationNode.h>
#include <nmode/CfgMutationEdge.h>

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

    void setNode(CfgMutationNode*);
    void setEdge(CfgMutationEdge*);

    CfgMutation* copy();

    bool changed(){return _changed;};

  private:
    CfgMutationNode *_node;
    CfgMutationEdge *_edge;
    bool             _changed;

};

#endif // ___CFG_MUTATION_H__
