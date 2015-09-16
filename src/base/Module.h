#ifndef __DATA_MODULE_H__
#define __DATA_MODULE_H__

#include "XsdParseNode.h"

#include "Node.h"
#include "Edge.h"

#include "Quaternion.h"
#include "ENPException.h"

# define TAG_MODULE            (char*)"module"
# define TAG_MODULE_DEFINITION (char*)"module_definition"

class Module : public XsdParseNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    Module(XsdParseNode *parent);

    /**
     * @brief Destructor.
     */
    virtual ~Module();

    void add(DataParseElement *element);

    static void createXsd(XsdSpecification *spec);

    Node*           node(int index);
    Nodes           nodes();
    Nodes::iterator n_begin();
    Nodes::iterator n_end();
    int                       n_size();

    Node*           sensorNode(int index);
    Nodes           sensorNodes();
    Nodes::iterator s_begin();
    Nodes::iterator s_end();
    int                       s_size();

    Node*           actuatorNode(int index);
    Nodes           actuatorNodes();
    Nodes::iterator a_begin();
    Nodes::iterator a_end();
    int                       a_size();

    Node*           hiddenNode(int index);
    Nodes           hiddenNodes();
    Nodes::iterator h_begin();
    Nodes::iterator h_end();
    int                       h_size();

    Edges           edges();
    Edges::iterator e_begin();
    Edges::iterator e_end();
    int                       e_size();
    Edge*           edge(int index);

    string                    name();
    string                    ref();

    P3D                       translation();
    Quaternion                rotation();

    void                      addNode(Node*);

    void                      update();
    // could be a copy but not yet linked
    bool                      isCopy();
    bool                      isLinked();

    void                      linkTo(Module*);

    bool operator == (const Module m);
    bool operator != (const Module m);

    bool removeNode(Node *n) throw (ENPException);
    bool removeEdge(Edge *e);

    Edge* addEdge(Node *src,
                            Node *dst,
                            double weight) throw (ENPException);

    bool modified();
    void setModified(bool m);
    int  getNewNodeId();

    void updateFromLink();

  private:
    // void            __linkConnectorNeurons();

    string     _name;
    string     _ref;

    Quaternion _rotation;
    P3D        _translation;

    bool      *_mirrorAxes;
    bool       _isCopy;
    bool       _isLinked;
    bool       _modified;
    int        _globalId;
    Edges      _copiedEdges;
    Nodes      _copiedNodes;
    Module    *_target;

    Nodes      _nodes;
    Nodes      _sensor;
    Nodes      _actuator;
    Nodes      _input;
    Nodes      _hidden;
    Edges      _edges;

};

typedef vector<Module*> Modules;

#endif // ___DATA_MODULE_H__


