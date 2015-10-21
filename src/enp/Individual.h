#ifndef __DATA_INDIVIDUAL_H__
#define __DATA_INDIVIDUAL_H__

#include "XsdParseNode.h"
#include "Module.h"

# define TAG_INDIVIDUAL            (char*)"individual"
# define TAG_INDIVIDUAL_DEFINITION (char*)"individual_definition"

class Individual : public XsdParseNode
{
  public:
    Individual(XsdParseNode *parent = NULL);
    // ~Individual();

    //Individual(const Individual);
    //Individual operator=(const Individual);

    void add(ParseElement *element);
    static void createXsd(XsdSpecification *spec);

    void              setFitness(double);
    double            fitness();

    double            rawFitness();
    void              setRawFitness(double);

    double            nodeCost();
    void              setNodeCost(double);

    double            edgeCost();
    void              setEdgeCost(double);

    void              setId(int);
    int               id();

    void              incAge();
    void              resetAge();
    int               age();

    int               nrOfOffspring();
    void              setNrOfOffspring(int);

    int               nrOfSynapses();
    void              setNrOfSynapses(int);

    int               nrOfNeurons();
    void              setNrOfNeurons(int);

    Modules::iterator m_begin();
    Modules::iterator m_end();
    int               m_size();
    Modules           modules();
    Module*           module(int);
    Module*           moduleByName(string);
    void              addModule(Module*);
    Individual*       getRealisation();
    void              linkConnectorNodes() throw(ENPException);

    double            probability();
    void              setProbability(double);

    Individual*       copy(bool reset=false);

  private:
    Node*   __getNonHiddenNode(string module, string label);
    Node*   __getNonHiddenNodeFromModule(Module *m, string nodeLabel);

    int     _id;
    int     _age;
    double  _fitness;
    Modules _modules;
    double  _probability;
    double  _rawFitness;
    double  _edgeCost;
    double  _nodeCost;
    int     _nrOfOffspring;
    int     _nrOfSynapses;
    int     _nrOfNeurons;
};

typedef vector<Individual*> Individuals;

#endif // __DATA_INDIVIDUAL_H__


