#include <yars/configuration/xsd/graphviz/XsdGraphvizGenerator.h>

#include <yars/configuration/xsd/graphviz/graph/XsdGraphNodeInstance.h>

#include <yars/util/stl_macros.h>

#include <vector>
#include <iostream>

XsdGraphvizGenerator::XsdGraphvizGenerator()
{
  _graph = new XsdGraph();
}

void XsdGraphvizGenerator::generate(string parent, string name, bool leftToRight, int depth)
{
  _dot.str("");
  _dot << "digraph structs {"         << endl;
  if(leftToRight)
  {
    _dot << "  rankdir=LR;"             << endl;
    // _dot << "  layout=circo;"             << endl;
    // _dot << " ranksep=5;"<< endl << "  ratio=auto;"             << endl;
    // _dot << " outputMode=\"edgesfirst\";" << endl;

  }
  else
  {
    _dot << "  rankdir=TB;"             << endl;
  }
  //_dot << "  ranksep=\"equally\";"    << endl;
  _dot << "  node [shape=plaintext];" << endl;

  XsdGraphNodeInstance *node = _graph->get(parent, name);
  __generate(node, depth);

  _dot << "}" << endl;
}

void XsdGraphvizGenerator::__generate(XsdGraphNodeInstance *node, int depth)
{
  if(depth == 0) return;
  int d = depth - 1;
  _dot << " " << node->uniqueName() << " " << node->label() << endl;
  if(d != 0)
  {
    int index = 1;
    FOREACHP(XsdGraphNodeInstance*, i, node)
    {
      __generate(*i, d);
      _dot << node->uniqueName() << ":" << (*i)->port() << " -> " << (*i)->uniqueName() << 
        "[ label=\"" << (*i)->restrictions() << "\"]" << ";" << endl;
    }
  }
}
