#ifndef __DATA_MODULE_NODE_H__
#define __DATA_MODULE_NODE_H__

#include "DataNode.h"

#include "base/P3D.h"

# define TAG_MODULE_NODE            (char*)"node"
# define TAG_MODULE_NODE_DEFINITION (char*)"module_node_definition"

class DataModuleNode : public DataNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    DataModuleNode(DataNode *parent);

    /**
     * @brief Destructor.
     */
    virtual ~DataModuleNode();

    void add(DataParseElement *element);

    static void createXsd(XsdSpecification *spec);

    string type();
    string label();
    P3D    position();
    string transferfunction();
    double bias();

  private:
    string _type;
    string _label;
    P3D    _position;
    string _transferfunction;
    double _bias;
};

typedef vector<DataModuleNode*> DataModuleNodes;

#endif // ___DATA_MODULE_NODE_H__


