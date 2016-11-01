#include <yars/configuration/xsd/graphviz/graph/XsdRegularExpressionGraphNode.h>

#include <yars/util/stl_macros.h>

#include <yars/configuration/data/Data.h>

XsdRegularExpressionGraphNode::XsdRegularExpressionGraphNode(XsdRegularExpression *spec)
{
  _spec = spec;

  _oss << "<tr> <td bgcolor=\"" << SPECIFICATION_BGCOLOR << "\"> "       << spec->regExp() << " </td> </tr>";
  _oss << "<tr> <td bgcolor=\"" << SPECIFICATION_BGCOLOR << "\"> type: " << spec->type()   << " </td> </tr>";
  _type = "reg. exp.";
  _specification = _oss.str();
}

string XsdRegularExpressionGraphNode::customLabel(string label)
{
  _oss.str("");
  _oss << " [label=<";
  _oss << "<table bgcolor=\"" << REGEXP_BGCOLOR << "\" border=\"0\" cellborder=\"1\" cellspacing=\"0\" cellpadding=\"0\">";
  _oss << "<tr><td> " << label  << "</td></tr>"; // << "&nbsp;:&nbsp;" << _type << "</td></tr>";
  _oss << _specification;
  _oss << "</table>";
  _oss << ">];";
  return _oss.str();
}

string XsdRegularExpressionGraphNode::name()
{
  return _spec->name();
}

XsdRegularExpression* XsdRegularExpressionGraphNode::spec()
{
  return _spec;
}

string XsdRegularExpressionGraphNode::content()
{
  _oss.str("");
  _oss << "<tr> <td> "       << _spec->regExp() << " </td> </tr>";
  _oss << "<tr> <td> type: " << _spec->type()   << " </td> </tr>";
  return _oss.str();
}
