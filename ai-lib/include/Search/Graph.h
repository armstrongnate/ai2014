#ifndef _GRAPH_H_
#define _GRAPH_H_

namespace ai
{
  namespace Search
  {
    class Graph : public Algorithm
    {
    public:
      Graph(Problem *problem_in, Fringe *fringe_in);
      virtual ~Graph();
      virtual bool Search();

    protected:
      ClosedList closed;
    private:
    };
  }
}

#endif /* _GRAPH_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
