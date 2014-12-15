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
      state->SetZ(cell.location.z);
      int interface = I_UNKNOWN;

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
      double stepCost = 1.0;
      switch (interface) {
        case I_MUD:
          stepCost += 10;
          break;
        case I_ROCKS:
        case I_PLAIN:
          break;
      }
      double min_charge = 1.0;
      bool passable = (state->GetCharge() - stepCost) > min_charge && (interface == I_PLAIN || interface == I_MUD);
      if (mode == SEARCH_MODE_BASE) {
        Cell nextCell = model->FindCell(state->GetX(), state->GetY());
        state->SetZ(nextCell.location.z);
        double dz = nextCell.location.z - cell.location.z;
        stepCost += dz * 0.001;
        state->SetCharge(state->GetCharge() - stepCost);
        passable = nextCell.Visited() && (state->GetCharge() > min_charge);
      }
      else {
        state->SetCharge(state->GetCharge() - stepCost - 1);
      }
      if (passable) {
        ai::Search::ActionStatePair asp(state, action);
        results_out.push_back(asp);
      }
      else {
        delete state;
        delete action;
      }
    }
    return true;
  }

  double SearchProblem::StepCost(const ai::Search::State  * const state1_in,
    const ai::Search::Action * const action_in,
    const ai::Search::State  * const state2_in) const {
    const SearchState * const state1 = dynamic_cast<const SearchState * const>(state1_in);
    const SearchState * const state2 = dynamic_cast<const SearchState * const>(state2_in);
    return state1->GetCharge() - state2->GetCharge();
  }

}
