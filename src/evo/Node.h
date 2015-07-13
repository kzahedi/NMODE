#ifndef __NODE_H__
#define __NODE_H__

#include <vector>
#include <string>
#include <ostream>

#include "base/P3D.h"
#include "base/ENPException.h"

#include "Edge.h"

#define NODE_TYPE_SENSOR   1001
#define NODE_TYPE_ACTUATOR 1002
#define NODE_TYPE_HIDDEN   1003
#define NODE_TYPE_INPUT    1004
#define NODE_TYPE_OUTPUT   1005

using namespace std;

class Node
{
  public:
    Node();
    ~Node();

    //Node(const Node);
    //Node operator=(const Node);
    bool operator==(const Node o);
    bool operator!=(const Node o);

    void setPosition(P3D position);
    void setType(string type) throw (ENPException);
    void setLabel(string label);
    void setTransferfunction(string tf);

    P3D    position();
    int    type();
    string stype();
    string label();
    string transferfunction();
    bool   contains(Edge *e);
    bool   contains(Node *n);


    Edges::iterator e_begin();
    Edges::iterator e_end();
    int             e_size();
    Edge*           edge(int index);

    void   setBias(double v);
    double bias();

    void addEdge(Edge *e);
    bool removeEdge(Edge *e);
    void removeEdge(Node *n);

    friend std::ostream& operator<<(std::ostream& str, const Node& n)
    {
      str << "        <node type=\"" << n._stype << "\" label=\"" << n._label << "\">" << endl;
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

    P3D    _position;
    int    _type;
    double _bias;
    string _stype;
    string _label;
    string _transferfunction;
    Edges  _in;
};

typedef vector<Node*> Nodes;

#endif // __NODE_H__

