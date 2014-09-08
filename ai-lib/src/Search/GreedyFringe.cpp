#include "ai_search.h"

namespace ai
{
  namespace Search
  {
    GreedyFringe::~GreedyFringe()
    {
    }

    bool GreedyFringe::Insert(Node *node_in)
    {
      NodePtr np(node_in);
      fringe.push(np);
      return true;
    }

    Node *GreedyFringe::Remove()
    {
      Node *tmp = fringe.top().ptr;
      fringe.pop();
      //double sum = tmp->GetPathCost() + tmp->GetHeuristic();
      //std::cout << "REMOVED " << tmp->GetPathCost() << " " << tmp->GetHeuristic() << " " << sum << std::endl;
      return tmp;
    }

    bool GreedyFringe::Empty() const
    {
      return fringe.empty();
    }

    size_t GreedyFringe::Size() const
    {
      return fringe.size();
    }

    GreedyFringe::NodePtr::NodePtr(Node *node_in)
    {
      ptr = node_in;
    }
    
    bool GreedyFringe::NodePtr::operator<(const NodePtr &rhs) const
    {
      return ((ptr->GetHeuristic()) > (rhs.ptr->GetHeuristic()));
    }
    
  }
}
