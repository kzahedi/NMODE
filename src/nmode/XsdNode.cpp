#include <nmode/XsdNode.h>

XsdNode::XsdNode(int nodeType)
{
  _nodeType = nodeType;
}
XsdNode::~XsdNode()
{

}

int XsdNode::nodeType()
{
  return _nodeType;
}

void XsdNode::setComment(string comment)
{
  _comment = comment;
}

string XsdNode::comment()
{
  return _comment;
}
