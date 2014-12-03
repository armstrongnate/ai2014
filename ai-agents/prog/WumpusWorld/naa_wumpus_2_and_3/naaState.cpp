//
//  naaState.cpp
//  WumpusWorld
//
//  Created by Nate Armstrong on 11/19/14.
//  Copyright (c) 2014 Nate Armstrong. All rights reserved.
//

#include <sstream>
#include <iostream>
#include <cmath>

#include "naaState.h"

namespace naa {

  State::State() {
    x = 0;
    y = 0;
  }

  State::State(const double x_in, const double y_in)
  : x(x_in), y(y_in) {}

  State::~State() {}

  void State::Display() const {}

  bool State::IsEqual(const ai::Search::State * const state_in) const {
    const State * const state = dynamic_cast<const State * const>(state_in);
    return ((std::fabs(x - state->x) < 0.5) &&
            (std::fabs(y - state->y) < 0.5) &&
            state->direction == direction);
  }

  std::string State::HashValue() const {
    std::stringstream ss;
    ss << "TODO";
    return ss.str();
  }

  State * State::TurnLeft() const {
    State * state = new State(x, y);
    switch (direction) {
      case DIRECTION_NORTH:
        state->direction = DIRECTION_WEST;
        break;
      case DIRECTION_EAST:
        state->direction = DIRECTION_NORTH;
        break;
      case DIRECTION_SOUTH:
        state->direction = DIRECTION_EAST;
        break;
      case DIRECTION_WEST:
        state->direction = DIRECTION_SOUTH;
    }
    return state;
  }

  State * State::TurnRight() const {
    State * state = new State(x, y);
    switch (direction) {
      case DIRECTION_NORTH:
        state->direction = DIRECTION_EAST;
        break;
      case DIRECTION_EAST:
        state->direction = DIRECTION_SOUTH;
        break;
      case DIRECTION_SOUTH:
        state->direction = DIRECTION_WEST;
        break;
      case DIRECTION_WEST:
        state->direction = DIRECTION_NORTH;
    }
    return state;
  }

}