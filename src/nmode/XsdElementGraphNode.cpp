#include <nmode/XsdElementGraphNode.h>

#include <nmode/macros.h>

#include <iostream>

using namespace std;

XsdElementGraphNode::XsdElementGraphNode(XsdElement *spec)
{
  _spec = spec;
}

string XsdElementGraphNode::customLabel(string label)
{
  _oss.str("");
  _oss << " [label=<";
  _oss << "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\" cellpadding=\"0\">";
  _oss << "<tr><td>";
  _oss << "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">";
  _oss << "<tr><td colspan=\"2\" bgcolor=\"" << ELEMENT_BGCOLOR << "\">"<< label << "</td></tr>";
  if(_spec->type().length() > 0)
  {
    _oss << "<tr><td colspan=\"2\" bgcolor=\"" << ELEMENT_BGCOLOR << "\">"<< _spec->type() << "</td></tr>";
  }
  int attributeDefinitionIndex = 1;
  FORF(vector<XsdAttribute*>, a, _spec, a_begin(), a_end())
  {
    _oss << "<tr><td rowspan=\"2\" bgcolor=\"" << ATTRIBUTE_BGCOLOR << "\">"<< (*a)->name() << "</td>";
    if((*a)->required())
    {
      _oss << "<td bgcolor=\"" << ATTRIBUTE_BGCOLOR << "\"> <font color=\"" << REQUIRED_COLOR << "\"> required </font> </td>";
    }
    else
    {
      _oss << "<td bgcolor=\"" << ATTRIBUTE_BGCOLOR << "\"> <font color=\"" << OPTIONAL_COLOR << "\"> optional </font> </td>";
    }
    _oss << "</tr>";
    if(!hasDefinition((*a)->type()))
    {
      _oss << "<tr><td bgcolor=\"" << ATTRIBUTE_BGCOLOR << "\">"<< (*a)->type() << "</td></tr>";
    }
    else
    {
      _oss << "<tr><td bgcolor=\"" << ATTRIBUTE_BGCOLOR << "\"> see #" << attributeDefinitionIndex++ << " </td></tr>";
    }
  }

  _oss << "</table>";
  _oss << "</td>";

  int portIndex = 0;
  stringstream oss_2;
  FORF(vector<XsdAttribute*>, a, _spec, a_begin(), a_end())
  {
    if(hasDefinition((*a)->type()))
    {
      oss_2 << "<tr><td port=\"" << portIndex << "\" bgcolor=\"" << ATTRIBUTE_BGCOLOR << "\">#" << portIndex+1 << "</td></tr>";
      portIndex++;
    }
  }


  if(oss_2.str().length() > 0)
  {
    _oss << "<td><table border=\"0\" cellborder=\"1\" cellspacing=\"0\">";
    _oss << oss_2.str();
    _oss << "</table></td>";
  }

  _oss << "</tr>";
  _oss << "</table>";
  _oss << ">];";
  return _oss.str();
}

string XsdElementGraphNode::name()
{
  return _spec->name();
}

XsdElement* XsdElementGraphNode::spec()
{
  return _spec;
}

