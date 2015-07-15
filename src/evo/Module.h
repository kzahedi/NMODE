#ifndef __MODULE_H__
#define __MODULE_H__

#include "Node.h"
#include "base/data/DataModule.h"

class Module
{
  public:
    Module(string name);
    ~Module();

    //Module(const Module);
    //Module operator=(const Module);

    bool operator == (const Module m);
    bool operator != (const Module m);

    void                  addNode(Node *neuron) throw (ENPException);
    string                name();
    void                  setName(string name);

    bool                  linked();
    void                  linkTo(Module *target);

    bool                  removeNode(Node *n) throw (ENPException);
    bool                  removeEdge(Edge *e);
    Edge*                 addEdge(Node *src, Node *dst, double weight) throw (ENPException);

    void                  initialise(DataModule *module);

    Node*                 node(int index);
    Nodes::iterator       n_begin();
    Nodes::iterator       n_end();
    int                   n_size();
    int                   s_size(); // number of sensor nodes
    int                   a_size(); // number of actuator nodes
    Node*                 hiddenNode(int index);
    int                   h_size(); // number of hidden nodes

    Edges::iterator       e_begin();
    Edges::iterator       e_end();
    int                   e_size();
    Edge*                 edge(int index);

    bool                  modified();
    void                  setModified(bool m);
    int                   getNewNodeId();

  private:
    Nodes       _nodes;
    Nodes       _sensors;
    Nodes       _actuators;
    Nodes       _input;
    Nodes       _output;
    Nodes       _hidden;
    Edges       _edges;
    string      _name;
    bool        _linked;
    bool        _modified;
    Module     *_target;

    int         _globalId;
};

typedef vector<Module*> Modules;

#endif // __MODULE_H__

