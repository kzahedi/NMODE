#ifndef __NMODE_DATA_EVOLUTION_NODE_H__
#define __NMODE_DATA_EVOLUTION_NODE_H__

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
    CfgMutationNode(XsdParseNode *parent = NULL);

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
    bool   changed() {return _changed;};

    CfgMutationNode* copy();

    friend std::ostream& operator<<(std::ostream& str, const CfgMutationNode& n)
    {
      str << "Node mutation parameters: " << endl;
      str << "  Mod probability " << n._modifyProbability << endl;
      str << "  Mod max value:  " << n._modifyMaxValue    << endl;
      str << "  Mod delta:      " << n._modifyDelta       << endl;
      str << "  Add prob:       " << n._addProbability    << endl;
      str << "  Add max value:  " << n._addProbability    << endl;
      str << "  Del prob:       " << n._delProbability    << endl;
      return str;
    };

  private:

    double _modifyProbability;
    double _modifyMaxValue;
    double _modifyDelta;
    double _addProbability;
    double _addMaxValue;
    double _delProbability;
    bool   _changed;


};

#endif // ___DATA_EVOLUTION_NODE_H__


