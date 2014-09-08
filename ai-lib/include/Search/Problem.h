#ifndef _SEARCH_PROBLEM_H_
#define _SEARCH_PROBLEM_H_
#include <vector>
namespace ai
{
  namespace Search
  {
    class Problem
    {
    public:
      Problem(State *initial_state_in);
      virtual ~Problem();
      
      State *GetInitialState();

      virtual void   Display() const;
      
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

#endif /* _PROBLEM_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
