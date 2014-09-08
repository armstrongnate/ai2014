#ifndef _SEARCH2010_PROBLEM_H_
#define _SEARCH2010_PROBLEM_H_

namespace ai
{
  namespace Search2010
  {
    class Problem
    {
    public:
      /* *initial_state_in is copied, the pointer is not remembered here.
       * We pass by pointer to allow for polymorphism.
       */
      Problem(const State * const initial_state_in);
      
      /* virtual to allow for destructor chaining */
      virtual ~Problem(); 

      /* allow algorithm to inspect initial state */
      const State * const GetInitialState() const;

      /* send problem representation to std::cout */
      virtual void   Display() const;

      /* */
      virtual bool   GoalTest(const State * const state_in) const = 0;
      virtual bool   FindSuccessors(const State * const state_in,
                                    std::vector<ActionStatePair>
                                    &results_out) const = 0;
      virtual double StepCost(const State  * const state1_in,
			      const Action * const action_in,
			      const State  * const state2_in) const = 0;
      virtual double Heuristic(const State  * const state_in) const;
      
    protected:
      
      State             *initial_state;
      
    private:
    };

  }
}

#endif /* _SEARCH2010_PROBLEM_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
