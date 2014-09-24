#include "naaSearchProblem.h"
#include "naaSearchState.h"
#include "naaSearchAction.h"
#include <iostream>

namespace naa {

    SearchProblem::SearchProblem(ai::Search::State *initial_state_in, Model *model_in)
      : ai::Search::Problem(initial_state_in),
        model(model_in) {}

    SearchProblem::~SearchProblem() {}

    void SearchProblem::Display() const {
      std::cout << "SearchProblem Display" << std::endl;
    }

    bool SearchProblem::GoalTest(const ai::Search::State * const state_in) const {
      Location location = model->GetGoalLocation();
      SearchState searchState(location.x, location.y, location.z, 0.0);
      return searchState.IsEqual(state_in);
    }

    bool SearchProblem::FindSuccessors(const ai::Search::State * const state_in,
      std::vector<ai::Search::ActionStatePair> &results_out) const {
      const SearchState * const s = dynamic_cast<const SearchState * const>(state_in);
      Cell cell = model->FindCell(s->GetX(), s->GetY());
      for (int i = ACTION_MOVE_NORTH; i < ACTION_MAX; i++) {
        SearchAction *action = new SearchAction(i);
        SearchState *state = new SearchState(s->GetX(), s->GetY(), s->GetZ(), s->GetCharge());
        int interface = I_UNKNOWN;
        bool safe = false;

        switch(i) {
          case ACTION_MOVE_NORTH:
            state->SetY(state->GetY() + 1000);
            interface = cell.border.north;
            break;
          case ACTION_MOVE_SOUTH:
            state->SetY(state->GetY() - 1000);
            interface = cell.border.south;
            break;
          case ACTION_MOVE_EAST:
            state->SetY(state->GetX() + 1000);
            interface = cell.border.east;
            break;
          case ACTION_MOVE_WEST:
            state->SetY(state->GetX() - 1000);
            interface = cell.border.west;
            break;
        }

        Cell c = model->FindCell(state->GetX(), state->GetY());
        if (c.IsValid() && (interface == I_PLAIN || interface == I_MUD)) {
          state->SetZ(c.location.z);
          ai::Search::ActionStatePair asp(state, action);
          results_out.push_back(asp);
          safe = true;
        }

        if (!safe) {
          delete state;
          delete action;
        }
      }

      return results_out.size() > 0;
    }

    double SearchProblem::StepCost(const ai::Search::State  * const state1_in,
      const ai::Search::Action * const action_in,
      const ai::Search::State  * const state2_in) const {
      return 1.0;
    }

}
