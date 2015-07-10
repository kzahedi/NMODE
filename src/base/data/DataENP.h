#ifndef ___DATA_ENP_H__
#define ___DATA_ENP_H__

#include "DataNode.h"
#include "Version.h"

#include "DataEvolution.h"
#include "DataConfiguration.h"
#include "DataSimulator.h"
#include "DataPopulation.h"

# define TAG_ENP                        (char*)"enp"
# define TAG_ENP_DEFINITION             (char*)"enp_definition"
# define TAG_VERSION_REGULAR_EXPRESSION (char*)"[0-9]+.[0-9]+.[0-9]+"

class DataENP : public DataNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    DataENP(DataNode *parent);

    /**
     * @brief Destructor.
     */
    virtual ~DataENP();

    Version version();
    void setVersion(Version version);

    void add(DataParseElement *element);

    static void createXsd(XsdSpecification *spec);

    DataSimulator*     simulator();
    DataEvolution*     evolution();
    DataConfiguration* configuration();
    DataPopulation*    population();

  private:
    void __getChild(DataParseElement *element);

    Version            _version;
    DataSimulator     *_simulator;
    DataEvolution     *_evolution;
    DataConfiguration *_configuration;
    DataPopulation    *_population;

};

#endif // ___DATA_ENP_H__
