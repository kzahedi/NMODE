#include <nmode/XsdIntervalGraphNode.h>

#include <nmode/macros.h>

XsdIntervalGraphNode::XsdIntervalGraphNode(XsdInterval *spec)
{
  _spec = spec;

  _type = "interval";
  _oss << "<tr> <td bgcolor=\"" << SPECIFICATION_BGCOLOR << "\"> min:  " << spec->minimum() << " </td> </tr>";
  _oss << "<tr> <td bgcolor=\"" << SPECIFICATION_BGCOLOR << "\"> max:  " << spec->maximum() << " </td> </tr>";
  _oss << "<tr> <td bgcolor=\"" << SPECIFICATION_BGCOLOR << "\"> type: " << spec->type() << " </td> </tr>";
  _specification = _oss.str();
}

string XsdIntervalGraphNode::customLabel(string label)
{
  _oss.str("");
  _oss << " [label=<";
  _oss << "<table bgcolor=\"" << INTERVAL_BGCOLOR << "\" border=\"0\" cellborder=\"1\" cellspacing=\"0\" cellpadding=\"0\">";
  _oss << "<tr><td> " << label  << "</td></tr>"; //<< "&nbsp;:&nbsp;" << _type << "</td></tr>";
  _oss << _specification;
  _oss << "</table>";
  _oss << ">];";
  return _oss.str();
}

string XsdIntervalGraphNode::name()
{
  return _spec->name();
}

XsdInterval* XsdIntervalGraphNode::spec()
{
  return _spec;
}
