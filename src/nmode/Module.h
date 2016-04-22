#ifndef __NMODE_MODULE_H__
#define __NMODE_MODULE_H__

#include <nmode/XsdParseNode.h>

#include <nmode/Node.h>
#include <nmode/Edge.h>
#include <nmode/CfgMutation.h>

#include <nmode/Quaternion.h>
#include <nmode/NMODEException.h>

# define TAG_MODULE            (char*)"module"
# define TAG_MODULE_DEFINITION (char*)"module_definition"

class MirrorAxes
{
  public:
    MirrorAxes()
    {
      x = false;
      y = false;
      z = false;
    }

    MirrorAxes(const MirrorAxes& ma)
    {
      x = ma.x;
      y = ma.y;
      z = ma.z;
    }

    MirrorAxes& operator=(const MirrorAxes &b)
    {
      x = b.x;
      y = b.y;
      z = b.z;
      return *this;
    }

    bool x;
    bool y;
    bool z;
};


class Module : public XsdParseNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    Module(XsdParseNode *parent = NULL);
    ~Module();


    Module(const Module &m);
    // Module& operator=(const Module &m);

    Module* copy();

    void add(ParseElement *element);
    void setName(string name);

    static void createXsd(XsdSpecification *spec);

    Node*           node(int index);
    Nodes           nodes();
    Nodes::iterator n_begin();
    Nodes::iterator n_end();
    int             n_size();

    Node*           sensorNode(int index);
    Nodes           sensorNodes();
    Nodes::iterator s_begin();
    Nodes::iterator s_end();
    int             s_size();

    Node*           actuatorNode(int index);
    Nodes           actuatorNodes();
    Nodes::iterator a_begin();
    Nodes::iterator a_end();
    int             a_size();
    Node*           nodeByName(string);

    Node*           moduleInputNode(int index);
    Nodes           moduleInputNodes();
    Nodes::iterator i_begin();
    Nodes::iterator i_end();
    int             i_size();

    Node*           moduleOutputNode(int index);
    Nodes           moduleOutputNodes();
    Nodes::iterator o_begin();
    Nodes::iterator o_end();
    int             o_size();

    Node*           hiddenNode(int index);
    Nodes           hiddenNodes();
    Nodes::iterator h_begin();
    Nodes::iterator h_end();
    int             h_size();

    Edges           edges();
    Edges::iterator e_begin();
    Edges::iterator e_end();
    int             e_size();
    Edge*           edge(int index);

    string          name();
    string          ref();

    P3D             translation();
    Quaternion      rotation();

    void            addNode(Node*);

    void            update();
    // could be a copy but not yet linked
    bool            isCopy();
    void            setIsCopy(bool);
    void            setTarget(string);

    bool operator == (const Module m);
    bool operator != (const Module m);

    bool removeNode(Node *n) throw (NMODEException);
    bool removeEdge(Edge *e);

    Edge* addEdge(Node *src,
                  Node *dst,
                  double weight) throw (NMODEException);

    bool modified();
    void setModified(bool); // for mutation operator
    bool nodeExists(string);

    void setMirrorAxes(bool, bool, bool);
    void setTranslation(P3D);
    void setRotation(P3D);
    MirrorAxes mirrorAxes();

    void copyAndApplyTransition(Module*);

    CfgMutation* mutation();
    void         setMutation(CfgMutation*);
    void         removeMutation();

  private:
    void         __applyMirror();
    void         __applyTranslation();

    string       _name;
    string       _ref;

    Quaternion   _rotation;
    P3D          _translation;

    MirrorAxes   _mirrorAxes;
    bool         _isCopy;
    bool         _modified;
    Edges        _copiedEdges;
    Nodes        _copiedNodes;

    Nodes        _nodes;
    Nodes        _sensor;
    Nodes        _actuator;
    Nodes        _connector;
    Nodes        _moduleInput;
    Nodes        _moduleOutput;
    Nodes        _hidden;
    Nodes        _tmpArrayOfNodes;
    Edges        _edges;
    CfgMutation* _mutation;
};

typedef vector<Module*> Modules;

#endif // __MODULE_H__
