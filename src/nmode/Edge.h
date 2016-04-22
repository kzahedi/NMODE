#ifndef __NMODE_DATA_MODULE_EDGE_H__
#define __NMODE_DATA_MODULE_EDGE_H__

#include  <nmode/XsdParseNode.h>
#include <nmode/P3D.h>

#include <vector>

using namespace std;

# define TAG_MODULE_EDGE            (char*)"edge"
# define TAG_MODULE_EDGE_DEFINITION (char*)"module_edge_definition"

class Node;

class Edge : public XsdParseNode
{
  public:
    Edge(XsdParseNode *parent);
    ~Edge();

    //Edge(const Edge);
    //Edge operator=(const Edge);

    void add(ParseElement *element);
    static void createXsd(XsdSpecification *spec);

    string source();
    string destination();
    void setSourceLabel(string);
    void setDestinationLabel(string);

    double weight();
    void   setWeight(double);

    Node* sourceNode();
    void  setSourceNode(Node*);
    Node* destinationNode();
    void  setDestinationNode(Node*);

    bool operator==(const Edge o);
    bool operator!=(const Edge o);

  private:
    string _source;
    string _destination;
    double _weight;
    Node  *_sourceNode;
    Node  *_destinationNode;
};

typedef vector<Edge*> Edges;

#endif // __DATA_MODULE_EDGE_H__
