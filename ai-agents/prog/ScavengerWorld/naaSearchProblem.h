#include "ai_search.h"
#include "naaModel.h"

namespace naa {
  enum {
    SEARCH_MODE_GOAL,
    SEARCH_MODE_BASE,
    SEARCH_MODE_QUIT,
  };

  class SearchProblem : public ai::Search::Problem {
    public:
      SearchProblem(ai::Search::State *initial_state_in, Model *model_in, int mode_in);
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
      int mode;
    private:
  };
}
