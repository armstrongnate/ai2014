#include "ai_search.h"

namespace ai
{
  namespace Search
    {

      DLFringe::DLFringe(int max_depth_in)
      {
	max_depth = max_depth_in;
      }
      
      DLFringe::~DLFringe()
      {
      }
      
      bool DLFringe::Insert(Node *node_in)
      {
	if(node_in->GetDepth() < max_depth)
	  {
	    fringe.push(node_in);
	    return true;
	  }
	return false;
      }
      
      Node *DLFringe::Remove()
      {
	Node *tmp = fringe.top();
	fringe.pop();
	return tmp;
      }
      
      bool DLFringe::Empty() const
      {
	return fringe.empty();
      }

      size_t DLFringe::Size() const
      {
	return fringe.size();
      }
  }
}


