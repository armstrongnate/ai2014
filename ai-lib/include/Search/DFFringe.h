#ifndef _DFFRINGE_H_
#define _DFFRINGE_H_

#include <stack>

namespace ai
{
  namespace Search
    {
      /* FRINGE
       * Implements a depth-first fringe using STL's stack
       */
      class DFFringe : public Fringe
	{
	public:
	  virtual ~DFFringe();
	  virtual bool Insert(Node *node_in);
	  virtual Node *Remove();
	  virtual bool Empty() const;
	  virtual size_t Size() const;
	protected:
	  std::stack<Node *> fringe;
	private:
	};
    }
}



#endif /* _DFFRINGE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
