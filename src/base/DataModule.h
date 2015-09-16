#ifndef __DATA_MODULE_H__
#define __DATA_MODULE_H__

#include "DataNode.h"

#include "DataModuleNode.h"
#include "DataModuleEdge.h"

#include "Quaternion.h"
#include "ENPException.h"

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

    DataModuleNode*           node(int index);
    DataModuleNodes           nodes();
    DataModuleNodes::iterator n_begin();
    DataModuleNodes::iterator n_end();
    int                       n_size();

    DataModuleNode*           sensorNode(int index);
    DataModuleNodes           sensorNodes();
    DataModuleNodes::iterator s_begin();
    DataModuleNodes::iterator s_end();
    int                       s_size();

    DataModuleNode*           actuatorNode(int index);
    DataModuleNodes           actuatorNodes();
    DataModuleNodes::iterator a_begin();
    DataModuleNodes::iterator a_end();
    int                       a_size();

    DataModuleNode*           hiddenNode(int index);
    DataModuleNodes           hiddenNodes();
    DataModuleNodes::iterator h_begin();
    DataModuleNodes::iterator h_end();
    int                       h_size();

    DataModuleEdges           edges();
    DataModuleEdges::iterator e_begin();
    DataModuleEdges::iterator e_end();
    int                       e_size();
    DataModuleEdge*           edge(int index);

    string                    name();
    string                    ref();

    P3D                       translation();
    Quaternion                rotation();

    void                      addNode(DataModuleNode*);

    void                      update();
    // could be a copy but not yet linked
    bool                      isCopy();
    bool                      isLinked();

    void                      linkTo(DataModule*);

    bool operator == (const DataModule m);
    bool operator != (const DataModule m);

    bool removeNode(DataModuleNode *n) throw (ENPException);
    bool removeEdge(DataModuleEdge *e);

    DataModuleEdge* addEdge(DataModuleNode *src,
                            DataModuleNode *dst,
                            double weight) throw (ENPException);

    bool modified();
    void setModified(bool m);
    int  getNewNodeId();

    void updateFromLink();

  private:
    // void            __linkConnectorNeurons();

    string          _name;
    string          _ref;

    Quaternion      _rotation;
    P3D             _translation;

    bool*           _mirrorAxes;
    bool            _isCopy;
    bool            _isLinked;
    bool            _modified;
    int             _globalId;
    DataModuleEdges _copiedEdges;
    DataModuleNodes _copiedNodes;
    DataModule     *_target;

    DataModuleNodes _nodes;
    DataModuleNodes _sensor;
    DataModuleNodes _actuator;
    DataModuleNodes _input;
    DataModuleNodes _hidden;
    DataModuleEdges _edges;

};

typedef vector<DataModule*> DataModules;

#endif // ___DATA_MODULE_H__


