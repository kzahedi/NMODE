#ifndef ___DATA_ENP_H__
#define ___DATA_ENP_H__

#include "XsdParseNode.h"
#include "Version.h"

#include "Evolution.h"
#include "DataConfiguration.h"
#include "Simulator.h"
#include "Population.h"

# define TAG_ENP                        (char*)"enp"
# define TAG_ENP_DEFINITION             (char*)"enp_definition"
# define TAG_VERSION_REGULAR_EXPRESSION (char*)"[0-9]+.[0-9]+.[0-9]+"

class ENP : public XsdParseNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    ENP(XsdParseNode *parent);

    /**
     * @brief Destructor.
     */
    virtual ~ENP();

    Version version();
    void setVersion(Version version);

    void add(DataParseElement *element);

    static void createXsd(XsdSpecification *spec);

    Simulator*     simulator();
    Evolution*     evolution();
    DataConfiguration* configuration();
    Population*    population();

  private:
    void __getChild(DataParseElement *element);

    Version            _version;
    Simulator     *_simulator;
    Evolution     *_evolution;
    DataConfiguration *_configuration;
    Population    *_population;

};

#endif // ___DATA_ENP_H__