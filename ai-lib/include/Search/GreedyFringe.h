#ifndef _GREEDYFRINGE_H_
#define _GREEDYFRINGE_H_

#include <queue>

namespace ai
{
  namespace Search
  {
    /* FRINGE
     * Implements an Greedy-Best-First fringe using STL's priority_queue
     */
    class GreedyFringe : public Fringe
    {
    public:
      virtual ~GreedyFringe();
      virtual bool Insert(Node *node_in);
      virtual Node *Remove();
      virtual bool Empty() const;
      virtual size_t Size() const;
	
    protected:
      
      struct NodePtr
      {
	NodePtr(Node *node_in);
	bool operator<(const NodePtr &rhs) const;
	Node *ptr;
      };
      
      std::priority_queue<NodePtr> fringe;
    private:
    };

  }
}

#endif /* _GREEDYFRINGE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
