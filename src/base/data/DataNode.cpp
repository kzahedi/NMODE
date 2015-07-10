#include "DataNode.h"

DataNode*         DataNode::current = NULL;

DataNode::DataNode(DataNode *_parent)
{
  parent = _parent;
}

DataNode::~DataNode()
{
  // nothing to be done
  // DO NOT DELETE EITHER parent OR current
}
