#ifndef __DATA_SIMULATOR_H__
#define __DATA_SIMULATOR_H__

#include "DataNode.h"

# define TAG_SIMULATOR            (char*)"simulator"
# define TAG_SIMULATOR_DEFINITION (char*)"simulator_definition"

class DataSimulator : public DataNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    DataSimulator(DataNode *parent);

    /**
     * @brief Destructor.
     */
    virtual ~DataSimulator();

    void add(DataParseElement *element);

    static void createXsd(XsdSpecification *spec);

    string workingDirectory();
    string xml();
    int    nr();

  private:

    string _workingDirectory;
    string _xml;
    int    _nr;

};

#endif // ___DATA_SIMULATOR_H__


