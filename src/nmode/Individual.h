#ifndef __NMODE_DATA_INDIVIDUAL_H__
#define __NMODE_DATA_INDIVIDUAL_H__

#include <nmode/XsdParseNode.h>
#include <nmode/Module.h>

# define TAG_INDIVIDUAL            (char*)"individual"
# define TAG_INDIVIDUAL_DEFINITION (char*)"individual_definition"

class Individual : public XsdParseNode
{
  public:
    Individual(XsdParseNode *parent = NULL);
    ~Individual();

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
    void              setAge(int);
    int               age();

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
    void              linkConnectorNodes() throw(NMODEException);

    int               nr();
    void              setNr(int);

    Individual*       copy(bool reset=false);
    bool              equal(Individual*);

    void              setFitnessComponents(vector<double> &fc) {_fitnessComponents = fc;};
    vector<double>    getFitnessComponents() {return _fitnessComponents;};
    void              setFitnessComponentNames(vector<string> &fcn) {_fitnessComponentNames = fcn;};
    vector<string>    getFitnessComponentNames() {return _fitnessComponentNames;};

    void              setSelected(bool);
    bool              isSelected();

    void              setEvaluated(bool);
    bool              isEvaluated();


  private:
    Node*   __getNonHiddenNode(string module, string label);
    Node*   __getNonHiddenNodeFromModule(Module *m, string nodeLabel);

    int            _id;
    int            _nr;
    int            _age;
    double         _fitness;
    Modules        _modules;
    double         _rawFitness;
    double         _edgeCost;
    double         _nodeCost;
    int            _nrOfSynapses;
    int            _nrOfNeurons;
    vector<double> _fitnessComponents;
    vector<string> _fitnessComponentNames;
    bool           _selected;
    bool           _evaluated;
};

typedef vector<Individual*> Individuals;

#endif // __DATA_INDIVIDUAL_H__


