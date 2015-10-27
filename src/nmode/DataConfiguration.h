#ifndef ___DATA_CONFIGURATION_H__
#define ___DATA_CONFIGURATION_H__

#include "XsdParseNode.h"

#include "Module.h"
#include "Individual.h"

# define TAG_CONFIGURATION            (char*)"configuration"
# define TAG_CONFIGURATION_DEFINITION (char*)"configuration_definition"

class DataConfiguration : public XsdParseNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    DataConfiguration(XsdParseNode *parent);
    ~DataConfiguration();

    void add(ParseElement *element);

    Modules::iterator m_begin();
    Modules::iterator m_end();
    int               m_size();
    Modules           modules();

    static void createXsd(XsdSpecification *spec);

  private:
    Individual *_individual;
};

#endif // ___DATA_CONFIGURATION_H__
