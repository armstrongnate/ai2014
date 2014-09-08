#ifndef _UCFRINGE_H_
#define _UCFRINGE_H_

#include <queue>

namespace ai
{
  namespace Search
  {
    /* FRINGE
     * Implements a uniform-cost fringe using STL's vector and sort 
     */
    class UCFringe : public Fringe
    {
    public:
      virtual ~UCFringe();
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
#endif /* _UCFRINGE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
