#ifndef _CLOSEDLIST_H_
#define _CLOSEDLIST_H_

#include <vector>

namespace ai
{
  namespace Search
  {
    
    class ClosedList
    {
    public:
      
      ClosedList();
      
      void Clear();
      bool Contains(const Node * const node_in) const;
      bool Insert(Node * node_in);
      size_t Size() const;
      
    protected:
      
      std::vector<Node *> closed_list;
      
    private:
    };

  }
}
#endif /* _CLOSEDLIST_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
