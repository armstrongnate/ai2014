#include "ai_search.h"

namespace ai
{
  namespace Search
  {
    UCFringe::~UCFringe()
    {
    }

    bool UCFringe::Insert(Node *node_in)
    {
      NodePtr np(node_in);
      fringe.push(np);
      return true;
    }

    Node *UCFringe::Remove()
    {
      Node *tmp = fringe.top().ptr;
      fringe.pop();
      //std::cout << "REMOVED " << tmp->GetPathCost() << std::endl;
      return tmp;
    }

    bool UCFringe::Empty() const
    {
      return fringe.empty();
    }

    size_t UCFringe::Size() const
    {
      return fringe.size();
    }

    UCFringe::NodePtr::NodePtr(Node *node_in)
    {
      ptr = node_in;
    }
    
    bool UCFringe::NodePtr::operator<(const NodePtr &rhs) const
    {
      return (ptr->GetPathCost() > rhs.ptr->GetPathCost());
    }
    
  }
}
