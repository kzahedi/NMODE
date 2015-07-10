#ifndef ___DATA_CONFIGURATION_H__
#define ___DATA_CONFIGURATION_H__

#include "DataNode.h"

#include "DataModule.h"

# define TAG_CONFIGURATION            (char*)"configuration"
# define TAG_CONFIGURATION_DEFINITION (char*)"configuration_definition"

class DataConfiguration : public DataNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    DataConfiguration(DataNode *parent);

    /**
     * @brief Destructor.
     */
    virtual ~DataConfiguration();

    void add(DataParseElement *element);

    DataModules::iterator m_begin();
    DataModules::iterator m_end();
    int                   m_size();
    DataModules           modules();

    static void createXsd(XsdSpecification *spec);

  private:
    DataModules _modules;
};

#endif // ___DATA_CONFIGURATION_H__
