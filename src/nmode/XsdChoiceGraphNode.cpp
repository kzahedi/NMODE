#include <nmode/XsdChoiceGraphNode.h>
#include <nmode/macros.h>

#include <iostream>

#define MAX(a,b) ((a>b)?a:b)

using namespace std;

XsdChoiceGraphNode::XsdChoiceGraphNode(XsdGraph* graph, XsdChoice *spec)
{
  _spec  = spec;
  _graph = graph;
}

string XsdChoiceGraphNode::customLabel(string label)
{
  _oss.str("");
  _oss << " [label=<";
  _oss << "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\" cellpadding=\"0\">";
  _oss << "<tr><td>";
  _oss << "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">";
  _oss << "<tr><td port=\"-1\" colspan=\"" << MAX(_spec->a_size(),1) << "\" bgcolor=\"" << ELEMENT_BGCOLOR << "\">"<< label << "</td></tr>";
  int portIndex = 1;
  stringstream s_label;
  stringstream s_optional;
  stringstream s_type;
  FOREACHF(XsdAttribute*, a, _spec, ->a_begin(), ->a_end())
  {
    s_label << "<td bgcolor=\"" << ATTRIBUTE_BGCOLOR << "\">"<< (*a)->name() << "</td>";
    if((*a)->required())
    {
      s_optional << "<td bgcolor=\"" << ATTRIBUTE_BGCOLOR << "\"> <font color=\"" << REQUIRED_COLOR << "\"> required </font> </td>";
    }
    else
    {
      s_optional << "<td bgcolor=\"" << ATTRIBUTE_BGCOLOR << "\"> <font color=\"" << OPTIONAL_COLOR << "\"> optional </font> </td>";
    }
    if(!hasDefinition((*a)->type()))
    {
      s_type << "<td port=\"" << portIndex++ << "\" bgcolor=\"" << ATTRIBUTE_BGCOLOR << "\" valign=\"top\">"<< (*a)->type() << "</td>";
    }
    else
    {
      XsdGraphNode *node      = __findNode((*a)->type());

      if(node != NULL)
      {
        s_type << "<td bgcolor=\"" << ATTRIBUTE_BGCOLOR << "\" valign=\"top\">";
        s_type << "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\" cellpadding=\"0\">";
        s_type << node->content();
        s_type << "</table>";
        s_type << "</td>";
      }
    }
  }
  if(s_label.str().length()    > 0) _oss << "<tr>" << s_label.str()    << "</tr>";
  if(s_optional.str().length() > 0) _oss << "<tr>" << s_optional.str() << "</tr>";
  if(s_type.str().length()     > 0) _oss << "<tr>" << s_type.str()     << "</tr>";
  _oss << "</table>";
  _oss << "</td>";
  _oss << "</tr>";
  _oss << "</table>";
  _oss << ">];";
  return _oss.str();
}

string XsdChoiceGraphNode::content()
{
  _oss.str("");
  _oss << "<tr> <td> choice </td> </tr>";
  return _oss.str();
}

string XsdChoiceGraphNode::name()
{
  return _spec->name();
}

XsdChoice* XsdChoiceGraphNode::spec()
{
  return _spec;
}

XsdGraphNode* XsdChoiceGraphNode::__findNode(string name)
{
  for(vector<XsdGraphNode*>::iterator n = _graph->n_begin(); n != _graph->n_end(); n++)
  {
    if((*n)->name() == name)
    {
      return (*n);
    }
  }
  return NULL;
}

