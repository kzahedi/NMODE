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
    string label();        // if label contains a '/' its a reference
    double bias();

    P3D    position();
    void   setPosition(P3D);

    string transferfunction();
    void   setTransferfunction(string);

    string moduleName();
    void   setModuleName(string);

    string nodeName();
    void   setNodeName(string);

  private:
    string _type;
    string _label;
    P3D    _position;
    string _transferfunction;
    string _nodeName;
    string _moduleName;
    double _bias;
};

typedef vector<DataModuleNode*> DataModuleNodes;

#endif // ___DATA_MODULE_NODE_H__


