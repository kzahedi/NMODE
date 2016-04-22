#include <nmode/XsdParseNode.h>

XsdParseNode* XsdParseNode::current = NULL;

XsdParseNode::XsdParseNode(XsdParseNode *_parent)
{
  parent = _parent;
}

XsdParseNode::~XsdParseNode()
{
  // nothing to be done
  // DO NOT DELETE EITHER parent OR current
}
