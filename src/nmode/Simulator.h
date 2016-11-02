#ifndef __NMODE_DATA_SIMULATOR_H__
#define __NMODE_DATA_SIMULATOR_H__

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
    string path();
    int    nr();

  private:

    string _workingDirectory;
    string _xml;
    string _options;
    string _path;
    int    _nr;

};

#endif // ___DATA_SIMULATOR_H__
