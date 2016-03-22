#ifndef ___DATA_EVOLUTION_EDGE_H__
#define ___DATA_EVOLUTION_EDGE_H__

#include "XsdParseNode.h"
#include "Version.h"

# define TAG_MUTATION_EDGE            (char*)"edge"
# define TAG_MUTATION_EDGE_DEFINITION (char*)"edge_evolution_definition"

class CfgMutationEdge : public XsdParseNode
{
  public:

    CfgMutationEdge(XsdParseNode *parent);
    ~CfgMutationEdge();

    void add(ParseElement *element);

    static void createXsd(XsdSpecification *spec);

    double modifyProbability();
    double modifyMaxValue();
    double modifyDelta();

    double addProbability();
    double addMaxValue();

    double selfProbability();
    double selfMaxValue();

    double delProbability();

    CfgMutationEdge* copy();

    friend std::ostream& operator<<(std::ostream& str, const CfgMutationEdge& e)
    {
      str << "Edge mutation parameters: " << endl;
      str << "  Mod probability   " << e._modifyProbability << endl;
      str << "  Mod max value:    " << e._modifyMaxValue    << endl;
      str << "  Mod delta:        " << e._modifyDelta       << endl;
      str << "  Add prob:         " << e._addProbability    << endl;
      str << "  Add self-coupling " << e._addSelfcoupling   << endl;
      str << "  Add max value:    " << e._addProbability    << endl;
      str << "  Del prob:         " << e._delProbability    << endl;
      return str;
    };

  private:

    double _modifyProbability;
    double _modifyMaxValue;
    double _modifyDelta;

    double _addProbability;
    double _addMaxValue;

    double _addSelfcoupling;
    double _maxSelfcoupling;

    double _delProbability;

};

#endif // ___DATA_EVOLUTION_EDGE_H__
