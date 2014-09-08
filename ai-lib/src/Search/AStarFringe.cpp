#include "ai_search.h"

namespace ai
{
  namespace Search
  {
    AStarFringe::~AStarFringe()
    {
    }
    
    bool AStarFringe::Insert(Node *node_in)
    {
      NodePtr np(node_in);
      fringe.push(np);
      return true;
    }
    
    Node *AStarFringe::Remove()
    {
      Node *tmp = fringe.top().ptr;
      fringe.pop();
      //double sum = tmp->GetPathCost() + tmp->GetHeuristic();
      //std::cout << "REMOVED " << tmp->GetPathCost() << " " << tmp->GetHeuristic() << " " << sum << std::endl;
      return tmp;
    }
    
    bool AStarFringe::Empty() const
    {
      return fringe.empty();
    }

    size_t AStarFringe::Size() const
    {
      return fringe.size();
    }

    AStarFringe::NodePtr::NodePtr(Node *node_in)
    {
      ptr = node_in;
    }
    
    bool AStarFringe::NodePtr::operator<(const NodePtr &rhs) const
    {
      return ((ptr->GetPathCost() + ptr->GetHeuristic()) > (rhs.ptr->GetPathCost() + rhs.ptr->GetHeuristic()));
    }
    
  }
}
