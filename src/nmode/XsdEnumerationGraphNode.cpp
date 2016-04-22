#include <nmode/XsdEnumerationGraphNode.h>

#include <nmode/macros.h>

XsdEnumerationGraphNode::XsdEnumerationGraphNode(XsdEnumeration *spec)
{
  _spec = spec;
  FORF(vector<string>, v, spec, v_begin(), v_end())
  {
    _oss << "<tr> <td bgcolor=\"" << SPECIFICATION_BGCOLOR << "\"> " << *v << " </td> </tr>";
  }
  _type = "enum";
  _specification = _oss.str();
}

string XsdEnumerationGraphNode::customLabel(string label)
{
  _oss.str("");
  _oss << " [label=<";
  _oss << "<table bgcolor=\"" << ENUM_BGCOLOR << "\" border=\"0\" cellborder=\"1\" cellspacing=\"0\" cellpadding=\"0\">";
  _oss << "<tr><td> " << label  << "</td></tr>";// << "&nbsp;:&nbsp;" << _type << "</td></tr>";
  _oss << _specification;
  _oss << "</table>";
  _oss << ">];";
  return _oss.str();
}


string XsdEnumerationGraphNode::name()
{
  return _spec->name();
}

XsdEnumeration* XsdEnumerationGraphNode::spec()
{
  return _spec;
}
