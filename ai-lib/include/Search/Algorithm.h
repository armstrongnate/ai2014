#ifndef _SEARCH_ALGORITHM_H_
#define _SEARCH_ALGORITHM_H_

namespace ai
{
  namespace Search
  {
    class Algorithm
    {
    public:
      enum AlgorithmType
        {
          T_NULL,
          T_Tree,
          T_Graph,
          T_MAX
        };
      
      Algorithm(Problem *problem_in, Fringe *fringe_in);
      virtual ~Algorithm();
      virtual bool Search() = 0;
      Solution &GetSolution();

      size_t GetNumberNodesGenerated() const;
      size_t GetMaxNodesStored() const;

      bool SetGenerationLimit(size_t limit);
      bool SetStoreLimit(size_t limit);
      
    protected:
      Problem *problem;
      Fringe  *fringe;
      Solution solution;

      Node *root;
      size_t number_nodes_generated;
      size_t max_nodes_stored;
      
      size_t generation_limit;
      size_t store_limit;
    private:
    };
  }
}

#endif /* _SEARCH_ALGORITHM_H_ */

/* Local Variables: */
/* mode:c++         */
/* End:             */
