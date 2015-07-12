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

    bool operator==(const Module m);
    bool operator!=(const Module m);

    void addNode(Node *neuron) throw (ENPException);
    string name();
    void   setName(string name);

    bool linked();
    void linkTo(Module *target);

    bool  removeEdge(Edge *e);
    Edge* addEdge(Node *src, Node *dst, double weight) throw (ENPException);

    void initialise(DataModule *module);

    Node*           node(int index);
    Nodes::iterator n_begin();
    Nodes::iterator n_end();
    int             n_size();
    int             s_size(); // number of sensor nodes
    int             a_size(); // number of actuator nodes
    int             h_size(); // number of hidden nodes

    Edges::iterator e_begin();
    Edges::iterator e_end();
    int             e_size();
    Edge*           edge(int index);

    vector<int>::iterator src_indices_begin();
    vector<int>::iterator src_indices_end();
    int                   src_indices_size();
    int                   src_index(int index);

    vector<int>::iterator dst_indices_begin();
    vector<int>::iterator dst_indices_end();
    int                   dst_indices_size();
    int                   dst_index(int index);

    bool            modified();
    void            setModified(bool m);

    friend std::ostream& operator<<(std::ostream& str, const Module& m)
    {
      str << "      <module name=\"" << m._name << "\">" << endl;
      for(Nodes::const_iterator n = m._nodes.begin(); n != m._nodes.end(); n++)
      {
        str << "        <node type=\"" << (*n)->type()
            << "\" label=\"" << (*n)->label() << "\">" << endl;
        str << "          <position x=\"" << (*n)->position().x
          << "\" y=\"" << (*n)->position().x
          << "\" z=\"" << (*n)->position().x
          << "\"/>" << endl;
        str << "          <transferfunction name=\"" << (*n)->transferfunction()
            << "\"/>" << endl;
        str << "          <bias value=\"" << (*n)->bias() << "\"/>" << endl;
        str << "        </node>" << endl;
      }
      for(Edges::const_iterator e = m._edges.begin(); e != m._edges.end(); e++)
      {
        str << "        <edge source=\"" << (*e)->source()->label()
          << "\" destination=\"" << (*e)->destination()->label() << "\" weight=\""
          << (*e)->weight()<< "\"/>" << endl;
      }
      str << "      </module>" << endl;
      return str;
    };

  private:
    Nodes   _nodes;
    Nodes   _sensors;
    Nodes   _actuators;
    Nodes   _input;
    Nodes   _output;
    Nodes   _hidden;
    Edges   _edges;
    string  _name;
    bool    _linked;
    bool    _modified;
    Module *_target;

    vector<int> _src_indices;
    vector<int> _dst_indices;
};

typedef vector<Module*> Modules;

#endif // __MODULE_H__

