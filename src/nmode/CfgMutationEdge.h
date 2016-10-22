#ifndef __NMODE_DATA_EVOLUTION_EDGE_H__
#define __NMODE_DATA_EVOLUTION_EDGE_H__

#include <nmode/XsdParseNode.h>
#include <nmode/Version.h>

# define TAG_MUTATION_EDGE            (char*)"edge"
# define TAG_MUTATION_EDGE_DEFINITION (char*)"edge_evolution_definition"

# define EDGE_ADD_MODE_UNIFORM  10001
# define EDGE_ADD_MODE_DISTANCE 10002

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

    int    mode();

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
      str << "  Add mode:         " << e._mode              << endl;
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
    double _mode;

};

#endif // ___DATA_EVOLUTION_EDGE_H__
