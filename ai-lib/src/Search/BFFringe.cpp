#include "ai_search.h"

namespace ai
{
  namespace Search
  {

    BFFringe::~BFFringe()
    {
    }

    bool BFFringe::Insert(Node *node_in)
    {
      fringe.push(node_in);
      return true;
    }

    Node *BFFringe::Remove()
    {
      Node *tmp = fringe.front();
      fringe.pop();
      return tmp;
    }

    bool BFFringe::Empty() const
    {
      return fringe.empty();
    }
    
    size_t BFFringe::Size() const
    {
      return fringe.size();
    }

  }
}
