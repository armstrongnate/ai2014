#include "ai_search.h"

#if 0
/* FIXME:
 *  This is a terrible implementation of a ClosedList.
 *  It has O(N) lookup.  Should be implemented with a
 *  hash table or something else for O(1) lookup.
 */
namespace ai
{
  namespace Search
  {
    ClosedList::ClosedList()
    {
    }
    
    void ClosedList::Clear()
    {
      closed_list.clear();
    }
    
    bool ClosedList::Contains(const Node * const node_in) const
    {
      unsigned int i;
      
      State *s1 = 0;
      State *s2 = node_in->GetState();
      
      for(i = 0; i < closed_list.size(); i++)
	{
	  s1 = closed_list[i]->GetState();
	  if(s1->IsEqual(s2))
	    {
	      return true;
	    }
	}
      return false;
    }
    
    bool ClosedList::Insert(Node * node_in)
    {
      if(Contains(node_in))
	{
	  return false;
	}
      closed_list.push_back(node_in);
      return true;
    }
  }
}
#else
namespace ai
{
  namespace Search
  {
    ClosedList::ClosedList()
    {
    }
    
    void ClosedList::Clear()
    {
      closed_list.clear();
    }
    
    bool ClosedList::Contains(const Node * const node_in) const
    {
      unsigned int i;
      
      State *s1 = 0;
      State *s2 = node_in->GetState();
      
      for(i = 0; i < closed_list.size(); i++)
	{
	  s1 = closed_list[i]->GetState();
	  if(s1->IsEqual(s2))
	    {
	      return true;
	    }
	}
      return false;
    }
    
    bool ClosedList::Insert(Node * node_in)
    {
      if(Contains(node_in))
	{
	  return false;
	}
      closed_list.push_back(node_in);
      return true;
    }

    size_t ClosedList::Size() const
    {
      return closed_list.size();
    }
  }
}
#endif

