#ifndef _BFFRINGE_H_
#define _BFFRINGE_H_

#include <queue>

namespace ai
{
  namespace Search
  {
    /* FRINGE
     * Implements a breadth-first fringe using STL's queue
     */
    class BFFringe : public Fringe
    {
    public:
      virtual ~BFFringe();
      virtual bool Insert(Node *node_in);
      virtual Node *Remove();
      virtual bool Empty() const;
      virtual size_t Size() const;
    protected:
      std::queue<Node *> fringe;
    private:
    };
  }
}

#endif /* _BFFRINGE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
