#ifndef __NMODE_DATA_CONFIGURATION_H__
#define __NMODE_DATA_CONFIGURATION_H__

#include <nmode/XsdParseNode.h>

#include <nmode/Module.h>
#include <nmode/Individual.h>

# define TAG_CONFIGURATION            (char*)"configuration"
# define TAG_CONFIGURATION_DEFINITION (char*)"configuration_definition"

class Configuration : public XsdParseNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    Configuration(XsdParseNode *parent);
    ~Configuration();

    void add(ParseElement *element);

    Modules::iterator m_begin();
    Modules::iterator m_end();
    int               m_size();
    Modules           modules();
    Module*           module(int index);

    static void createXsd(XsdSpecification *spec);

  private:
    Individual *_individual;
};

#endif // ___DATA_CONFIGURATION_H__
