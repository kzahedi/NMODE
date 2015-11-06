#ifndef ___DATA_NMODE_H__
#define ___DATA_NMODE_H__

#include "XsdParseNode.h"
#include "Version.h"

#include "CfgReproduction.h"
#include "CfgMutation.h"
#include "CfgEvaluation.h"
#include "Configuration.h"
#include "Simulator.h"
#include "Population.h"

# define TAG_NMODE                        (char*)"nmode"
# define TAG_NMODE_DEFINITION             (char*)"enp_definition"
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

    Simulator*       simulator();
    CfgMutation*     mutation();
    CfgEvaluation*   evaluation();
    Configuration*   configuration();
    Population*      population();
    CfgReproduction* reproduction();

  private:
    void __getChild(ParseElement *element);
    void __applyConfigurationToModules();

    Version          _version;
    Simulator*       _simulator;
    CfgMutation*     _mutation;
    Configuration*   _configuration;
    Population*      _population;
    CfgEvaluation*   _evaluation;
    CfgReproduction* _reproduction;
    bool             _initialisationCompleted;

};

#endif // ___DATA_NMODE_H__
