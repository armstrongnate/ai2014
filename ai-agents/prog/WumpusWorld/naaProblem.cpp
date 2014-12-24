//
//  naaProblem.cpp
//  WumpusWorld
//
//  Created by Nate Armstrong on 11/19/14.
//  Copyright (c) 2014 Nate Armstrong. All rights reserved.
//

#include "naaProblem.h"
#include "naaState.h"
#include "naaAction.h"

namespace naa {
  Problem::Problem(ai::Search::State *initial_state_in, bool visited[4][4], MyKnowledgeBase *knowledge)
  : ai::Search::Problem(initial_state_in), knowledge(knowledge) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        this->visited[i][j] = visited[i][j];
      }
    }
  }

  Problem::~Problem() {}

  void Problem::Display() const {}

  bool Problem::GoalTest(const ai::Search::State * const state_in) const {
    const State * const state = dynamic_cast<const State * const>(state_in);
    int x = state->x;
    int y = state->y;
    if (x < 0 || y < 0 || x > 3 || y > 3) {
      return false;
    }
    return !visited[x][y];
  }
  bool Problem::FindSuccessors(const ai::Search::State * const state_in,
                      std::vector<ai::Search::ActionStatePair> &results_out) const {
    const State * const s = dynamic_cast<const State * const>(state_in);
    if (s->x >= 0 && s->y >= 0 && s->x < 4 && s->y < 4) {
      State *state = new State(s->x, s->y);
      state->direction = s->direction;
      switch (s->direction) {
        case DIRECTION_NORTH:
          state->y += 1;
          break;
        case DIRECTION_EAST:
          state->x += 1;
          break;
        case DIRECTION_SOUTH:
          state->y -= 1;
          break;
        case DIRECTION_WEST:
          state->x -= 1;
          break;
      }
      if (knowledge->AskSafe(state)) {
        std::cout << "It is safe!" << std::endl;
        Action *action = new Action(FORWARD);
        ai::Search::ActionStatePair asp(state, action);
        results_out.push_back(asp);
      }
      else {
        std::cout << "It is NOT safe!" << std::endl;
        delete state;
      }
      results_out.push_back(ai::Search::ActionStatePair(s->TurnLeft(), new Action(TURN_LEFT)));
      results_out.push_back(ai::Search::ActionStatePair(s->TurnRight(), new Action(TURN_RIGHT)));
      std::cout << "Done with FindSuccessors" << std::endl;
    }

    return true;
  }
  double Problem::StepCost(const ai::Search::State  * const state1_in,
                          const ai::Search::Action * const action_in,
                          const ai::Search::State  * const state2_in) const {
    return 0.0;
  }
  double Problem::Heuristic(const ai::Search::State  * const state_in) const {
    return 1.0;
  }
}
