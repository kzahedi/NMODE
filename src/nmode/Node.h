#ifndef __NMODE_DATA_MODULE_NODE_H__
#define __NMODE_DATA_MODULE_NODE_H__

#include <nmode/XsdParseNode.h>

#include <nmode/NMODEException.h>

#include <nmode/Edge.h>
#include <nmode/P3D.h>

# define TAG_MODULE_NODE            (char*)"node"
# define TAG_MODULE_NODE_DEFINITION (char*)"module_node_definition"

# define TAG_ACTUATOR               (char*)"actuator"
# define TAG_SENSOR                 (char*)"sensor"
# define TAG_INPUT                  (char*)"input"
# define TAG_OUTPUT                 (char*)"output"
# define TAG_HIDDEN                 (char*)"hidden"
# define TAG_CONNECTOR              (char*)"connector"

# define TAG_TANH                   (char*)"tanh"
# define TAG_SIGM                   (char*)"sigm"
# define TAG_ID                     (char*)"id"

class Node : public XsdParseNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    Node(XsdParseNode *parent = NULL);

    /**
     * @brief Destructor.
     */
    virtual ~Node();

    bool operator==(const Node o);
    bool operator!=(const Node o);

    // bool contains(Edge *e);
    bool contains(Node *n);

    void add(ParseElement *element);

    static void createXsd(XsdSpecification *spec);

    void   setType(string) throw (NMODEException);
    string type();

    void   setLabel(string);
    string label();        // if label contains a '/' its a reference

    void   setBias(double b);
    double bias();


    P3D    position();
    void   setPosition(P3D);

    string transferfunction();
    void   setTransferfunction(string);

    string moduleName();
    void   setModuleName(string);

    string nodeName();
    void   setNodeName(string);

    Edges::iterator e_begin();
    Edges::iterator e_end();
    int                       e_size();
    Edge*           edge(int index);

    void addEdge(Edge *e);
    bool removeEdge(Edge *e);
    void removeEdge(Node *n);

    bool isSource();
    bool isDestination();
    void setIsSource(bool);
    void setIsDestination(bool);
    void setInactive(bool b);
    bool isInactive();

    Node* copy();

    friend std::ostream& operator<<(std::ostream& str, const Node& n)
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
    Edges  _in;
    P3D    _position;
    bool   _isDestination;
    bool   _isSource;
    bool   _inactive;
    double _bias;
    string _label;
    string _moduleName;
    string _nodeName;
    string _transferfunction;
    string _type;
};

typedef vector<Node*> Nodes;

#endif // ___DATA_MODULE_NODE_H__


