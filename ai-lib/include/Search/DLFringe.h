#ifndef _DLFRINGE_H_
#define _DLFRINGE_H_

#include <stack>

/* FRINGE
 * Implements a depth-limited fringe using STL's stack
 */
namespace ai
{
  namespace Search
    {
      class DLFringe : public Fringe
	{
	public:
	  DLFringe(int max_depth_in);
	  virtual ~DLFringe();
	  virtual bool Insert(Node *node_in);
	  virtual Node *Remove();
	  virtual bool Empty() const;
	  virtual size_t Size() const;
	protected:
	  std::stack<Node *> fringe;
	private:
	  int max_depth;
	};
    }
}

#endif /* _DLFRINGE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
