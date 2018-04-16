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

    void overrideCpus(int cpus);

    string workingDirectory();
    string xml();
    string options();
    string path();
    string env();
    int    nr();

  private:

    string _workingDirectory;
    string _xml;
    string _options;
    string _path;
    string _env;
    int    _nr;
    int    _overrideCpus;

};

#endif // ___DATA_SIMULATOR_H__
