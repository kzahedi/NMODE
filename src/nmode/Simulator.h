#ifndef __DATA_SIMULATOR_H__
#define __DATA_SIMULATOR_H__

#include "XsdParseNode.h"

# define TAG_SIMULATOR            (char*)"simulator"
# define TAG_SIMULATOR_DEFINITION (char*)"simulator_definition"

class Simulator : public XsdParseNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    Simulator(XsdParseNode *parent);

    /**
     * @brief Destructor.
     */
    virtual ~Simulator();

    void add(ParseElement *element);

    static void createXsd(XsdSpecification *spec);

    string workingDirectory();
    string xml();
    string options();
    int    nr();

  private:

    string _workingDirectory;
    string _xml;
    string _options;
    int    _nr;

};

#endif // ___DATA_SIMULATOR_H__
