#ifndef ___DATA_NMODE_H__
#define ___DATA_NMODE_H__

#include "XsdParseNode.h"
#include "Version.h"

#include "CfgReproduction.h"
#include "Evolution.h"
#include "Evaluation.h"
#include "DataConfiguration.h"
#include "Simulator.h"
#include "Population.h"
#include "Fitness.h"

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

    Simulator*         simulator();
    Evolution*         evolution();
    Evaluation*        evaluation();
    DataConfiguration* configuration();
    Population*        population();
    CfgReproduction*   reproduction();

  private:
    void __getChild(ParseElement *element);

    Version            _version;
    Simulator*         _simulator;
    Evolution*         _evolution;
    DataConfiguration* _configuration;
    Population*        _population;
    Evaluation*        _evaluation;
    Fitness*           _fitness;
    CfgReproduction*   _reproduction;
    bool               _initialisationCompleted;

};

#endif // ___DATA_NMODE_H__
