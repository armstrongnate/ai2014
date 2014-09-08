#include "ai_search.h"

namespace ai
{
  namespace Search
    {
      DFFringe::~DFFringe()
      {
      }
      
      bool DFFringe::Insert(Node *node_in)
      {
	fringe.push(node_in);
	return true;
      }
      
      Node *DFFringe::Remove()
      {
	Node *tmp = fringe.top();
	fringe.pop();
	return tmp;
      }
      
      bool DFFringe::Empty() const
      {
	return fringe.empty();
      }

      size_t DFFringe::Size() const
      {
	return fringe.size();
      }
  }
}
