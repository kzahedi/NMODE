#ifndef __YARS_XSD_GRAPHVIZ_GENERATOR_H__
#define __YARS_XSD_GRAPHVIZ_GENERATOR_H__

#include <yars/configuration/xsd/graphviz/graph/XsdGraph.h>

#include <sstream>

using namespace std;

class XsdGraphvizGenerator
{
  public:
    XsdGraphvizGenerator();

    void generate(string parent, string name, bool leftToRight, int depth);

    friend std::ostream& operator<<(std::ostream& str, XsdGraphvizGenerator& g)
    {
      str << g._dot.str() << endl;
      return str;
    };

  private:
    void __generate(XsdGraphNodeInstance *node, int depth);

    stringstream  _dot;
    XsdGraph     *_graph;
};

#endif // __YARS_XSD_GRAPHVIZ_GENERATOR_H__
