#ifndef _ASTARFRINGE_H_
#define _ASTARFRINGE_H_

#include <queue>

namespace ai
{
  namespace Search
  {
    /* FRINGE
     * Implements an A* fringe using STL's priority_queue
     */
    class AStarFringe : public Fringe
    {
    public:
      virtual ~AStarFringe();
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

#endif /* _ASTARFRINGE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
