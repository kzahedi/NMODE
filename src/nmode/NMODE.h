#ifndef __NMODE_DATA_NODE_H__
#define __NMODE_DATA_NODE_H__

#include <nmode/XsdParseNode.h>
#include <nmode/Version.h>

#include <nmode/CfgReproduction.h>
#include <nmode/CfgVisualisation.h>
#include <nmode/CfgMutation.h>
#include <nmode/CfgEvaluation.h>
#include <nmode/Configuration.h>
#include <nmode/Simulator.h>
#include <nmode/Population.h>

# define TAG_NMODE                      (char*)"nmode"
# define TAG_NODE_DEFINITION            (char*)"enp_definition"
# define TAG_VERSION_REGULAR_EXPRESSION (char*)"[0-9]+.[0-9]+.[0-9]+"

class NMODE : public XsdParseNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    NMODE(XsdParseNode *parent);

    /**
     * @brief Destructor.
     */
    virtual ~NMODE();

    Version version();
    void setVersion(Version version);

    void add(ParseElement *element);
    void initialiseFirstPopulationFromConfiguration();

    static void createXsd(XsdSpecification *spec);

    Simulator*        simulator();
    CfgMutation*      mutation();
    CfgEvaluation*    evaluation();
    Configuration*    configuration();
    Population*       population();
    CfgReproduction*  reproduction();
    CfgVisualisation* visualisation();

    // for test cases only
    void setSimulator(Simulator*);
    void setCfgMutation(CfgMutation*);
    void setCfgEvaluation(CfgEvaluation*);
    void setConfiguration(Configuration*);
    void setPopulation(Population*);
    void setCfgReproduction(CfgReproduction*);
    void setCfgVisualisation(CfgVisualisation*);
    void overrideReadingOfPopulation();
    bool changed();

  private:
    void __getChild(ParseElement *element);
    void __applyConfigurationToModules();

    Version           _version;
    Simulator*        _simulator;
    CfgMutation*      _mutation;
    Configuration*    _configuration;
    Population*       _population;
    CfgEvaluation*    _evaluation;
    CfgReproduction*  _reproduction;
    CfgVisualisation* _visualisation;
    bool              _initialisationCompleted;
    bool              _changed;

};

#endif // ___DATA_NODE_H__
