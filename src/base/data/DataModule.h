#ifndef __DATA_MODULE_H__
#define __DATA_MODULE_H__

#include "DataNode.h"

#include "DataModuleNode.h"
#include "DataModuleEdge.h"

# define TAG_MODULE            (char*)"module"
# define TAG_MODULE_DEFINITION (char*)"module_definition"

class DataModule : public DataNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    DataModule(DataNode *parent);

    /**
     * @brief Destructor.
     */
    virtual ~DataModule();

    void add(DataParseElement *element);

    static void createXsd(XsdSpecification *spec);

    DataModuleNodes           nodes();
    DataModuleNodes::iterator n_begin();
    DataModuleNodes::iterator n_end();
    int                       n_size();

    DataModuleEdges           edges();
    DataModuleEdges::iterator e_begin();
    DataModuleEdges::iterator e_end();
    int                       e_size();

    string name();

  private:
    string _name;

    DataModuleNodes _nodes;
    DataModuleEdges _edges;
};

typedef vector<DataModule*> DataModules;

#endif // ___DATA_MODULE_H__


