#ifndef __DATA_MODULE_NODE_H__
#define __DATA_MODULE_NODE_H__

#include "DataNode.h"
#include "DataModuleEdge.h"

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

    bool operator==(const DataModuleNode o);
    bool operator!=(const DataModuleNode o);

    bool contains(DataModuleEdge *e);
    bool contains(DataModuleNode *n);

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

    DataModuleEdges::iterator e_begin();
    DataModuleEdges::iterator e_end();
    int                       e_size();
    DataModuleEdge*           edge(int index);

    void addEdge(DataModuleEdge *e);
    bool removeEdge(DataModuleEdge *e);
    void removeEdge(DataModuleNode *n);

    bool isSource();
    bool isDestination();

    friend std::ostream& operator<<(std::ostream& str, const DataModuleNode& n)
    {
      str << "        <node type=\"" << n._type << "\" label=\"" << n._label << "\">" << endl;
      str << "          <position x=\"" << n._position.x
                           << "\" y=\"" << n._position.y
                           << "\" z=\"" << n._position.z
                           << "\"/>" << endl;
      str << "          <transferfunction name=\"" << n._transferfunction << "\"/>" << endl;
      str << "          <bias value=\"" << n._bias << "\"/>" << endl;
      str << "        </node>" << endl;
      return str;
    };

  private:
    string          _type;
    string          _label;
    P3D             _position;
    string          _transferfunction;
    string          _nodeName;
    string          _moduleName;
    double          _bias;
    DataModuleEdges _in;
};

typedef vector<DataModuleNode*> DataModuleNodes;

#endif // ___DATA_MODULE_NODE_H__


