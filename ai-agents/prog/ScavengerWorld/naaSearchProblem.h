#include "ai_search.h"
#include "naaModel.h"

namespace naa {
  class SearchProblem : public ai::Search::Problem {
    public:
      SearchProblem(ai::Search::State *initial_state_in, Model *model_in);
      virtual ~SearchProblem();

      virtual void Display() const;
      virtual bool GoalTest(const ai::Search::State * const state_in) const;
      virtual bool FindSuccessors(const ai::Search::State * const state_in,
        std::vector<ai::Search::ActionStatePair> &results_out) const;
      virtual double StepCost(const ai::Search::State  * const state1_in,
        const ai::Search::Action * const action_in,
        const ai::Search::State  * const state2_in) const;
    protected:
      Model *model;
    private:
  };
}
