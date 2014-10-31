#include "naaSearchProblem.h"
#include "naaSearchState.h"
#include "naaSearchAction.h"
#include <iostream>

namespace naa {

  SearchProblem::SearchProblem(ai::Search::State *initial_state_in, Model *model_in, int mode_in)
    : ai::Search::Problem(initial_state_in),
      model(model_in),
      mode(mode_in) {}

  SearchProblem::~SearchProblem() {}

  void SearchProblem::Display() const {
    std::cout << "SearchProblem Display" << std::endl;
  }

  bool SearchProblem::GoalTest(const ai::Search::State * const state_in) const {
    const SearchState * const s = dynamic_cast<const SearchState * const>(state_in);
    double x = s->GetX();
    double y = s->GetY();
    double z = s->GetZ();
    if (mode == SEARCH_MODE_SCAVENGE) {
      bool visited = model->FindCell(x, y).Visited();
      if (!visited) {
        SearchState *state = new SearchState(x, y, z, s->GetCharge());
        SearchProblem *problem = new SearchProblem(state, model, SEARCH_MODE_BASE);
        ai::Search::Graph *homeAlgo = new ai::Search::Graph(problem, new ai::Search::AStarFringe());
        bool canReturn = homeAlgo->Search();
        delete homeAlgo;
        return canReturn;
      }
      return false;
    }
    else if (mode == SEARCH_MODE_BASE) {
      SearchState searchState(0., 0., 0., 0.);
      bool isEqual = searchState.IsEqual(s);
      return isEqual;
    }
    return false;
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
          state->SetX(state->GetX() + 1000);
          interface = cell.border.east;
          break;
        case ACTION_MOVE_WEST:
          state->SetX(state->GetX() - 1000);
          interface = cell.border.west;
          break;
      }
      state->SetZ(cell.location.z);
      double min_charge = mode == SEARCH_MODE_SCAVENGE ? 80.0 : 1.0;
      bool passable = interface == I_PLAIN || interface == I_MUD;
      if (mode == SEARCH_MODE_BASE) {
        passable = model->FindCell(state->GetX(), state->GetY()).Visited();
      }
      if (state->GetCharge() > min_charge && passable) {
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
