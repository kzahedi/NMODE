#ifndef __DATA_MODULE_H__
#define __DATA_MODULE_H__

#include "DataNode.h"

#include "DataModuleNode.h"
#include "DataModuleEdge.h"

#include "base/Quaternion.h"

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

    string                    name();
    string                    ref();

    P3D                       translation();
    Quaternion                rotation();

  private:
    string          _name;
    string          _ref;

    DataModuleNodes _nodes;
    DataModuleEdges _edges;

    Quaternion      _rotation;
    P3D             _translation;

    bool*           _mirror;
};

typedef vector<DataModule*> DataModules;

#endif // ___DATA_MODULE_H__


