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

    int    id();
    int    offspring();
    double fitness();

    void setFitness(double);
    void setId(int id);

    Modules::iterator m_begin();
    Modules::iterator m_end();
    int               m_size();
    Modules           modules();
    Module*           module(int);
    Module*           moduleByName(string);
    void              addModule(Module*);
    Individual*       getRealisation();
    void              linkConnectorNodes() throw(ENPException);

  private:
    Node*   __getNonHiddenNode(string module, string label);
    Node*   __getNonHiddenNodeFromModule(Module *m, string nodeLabel);

    int     _id;
    int     _offspring;
    double  _fitness;
    Modules _modules;
};

typedef vector<Individual*> Individuals;

#endif // __DATA_INDIVIDUAL_H__


